# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024-2025 Arm Limited
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the 'Software'), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# -----------------------------------------------------------------------------
'''
This module contains a parser of a basic CSS-like style sheet that we use for
styling the user interface.

Unlike HTML, we have no standard implicit DOM that we can use to implement
style inheritance, so our CSS self-defines the parent-child hierarchical
relationships in the CSS itself. For example, in the node below we define
mtv-core as the parent style of the tlv-core style:

    [mtv-core] tlv-core {}

The style fields and defaults currently supported are:

  - fill-color: #01234567; (Default none)
  - line-color: #01234567; (Default none)
  - line-width: 1.5;       (Default 1.0)
  - line-dash: 2,4;        (Default none)
  - font-color: #01234567; (Default none)
  - font-face: name;       (Default Consolas,sans)
  - font-size: 11;         (Default 10)

Colors can be RGB or RGBA, but note that transparent colors are much more
expensive to render in Cairo. In addition, some parts of the tool may assume
objects use opaque colors to allow algorithmic culling.

NOTE: The defaults of all colors are 'none' so nothing will be visible on
screen unless a stylesheet explicitly sets a color.

TODO: Font-face does not actually perform a list search like real CSS, so it's
difficult to specify a fallback when a font isn't available for OS portability.
'''

import os
import re
from typing import Optional


import cairo


class CSSStylesheet(dict):
    '''
    A stylesheet that can be loaded from a CSS-like definition file.

    The basic file format consists of single line comments, and which use C
    style comments of the form::

        /* <comment here> */

    ... and rules which are of the form::

        [parent_node] node0, node1 {
            key: value;
            key: value;
        }

    The document object model (DOM) hierarchy for the cascading nature of the
    styles is encoded in the CSS file itself; the '[parent_node]' in square
    brackets describing the ancestor of each newly declared node.

    It is possible to declare empty nodes which define no styles, purely for
    the sake of structuring the DOM. These take the form:

        [parent_node] node0, node1 {}

    The current implementation does not implement a proper tokenizing parser,
    so is very sensitive to line layout. In particular the opening '{' must be
    on the same line as the node declarations, and the closing '}' must be on a
    new line (except for the empty DOM node).

    Supported keys are:

        - font-color: Format is # followed by 6 or 8 hex digits (lower case)
        - font-face: Format is a string
        - font-size: Format is a number
        - line-color: Format is # followed by 6 or 8 hex digits (lower case)
        - line-dash: Format is two integers comma separated (no space)
        - line-width: Format is a floating point number
        - fill-color: Format is # followed by 6 or 8 hex digits (lower case)

    CSS values are extracted using the indexed interface once a file is loaded:

        css[<NodeName>][<css-value]

    e.g.,

        color = css['body']['fill-color']

    Trying to access a node which does not exist will raise a KeyError.

    If a style node exists, all of the keys are guaranteed to return a value.
    Values are found by recursing towards the DOM root to find a value if the
    node does not provide the value itself. All nodes inherit from a default
    root node which defines a default value for all exposed style keys.

    Attributes:
        re_comment: Regex for matching comments.
        re_node_decl: Regex for matching node declarations.
        re_node_end_decl: Regex for matching the end of node declarations.
        re_color_decl: Regex for matching colors.
        re_dash_decl: Regex for matching dashes.
        re_float_decl: Regex for matching floats.
    '''

    re_comment = re.compile(r'/\*(.*?)\*/')

    re_node_decl = re.compile(
        r'''
          ^\s*                              # Start new line, ignore whitespace
          (?:\[                             # Parent node
              ([A-Za-z0-9_\-.]+)
          \]\s+)?\s*
          (
            (?:[A-Za-z0-9_\-.]+)            # One mandatory node name
            (?:,\s+(?:[A-Za-z0-9_\-.]+))*   # Zero or more optional node names
          )\s*
          {                                 # Start brace region
          (?:(})|\s*)                       # End brace or lots of space
          $                                 # End a line ignore whitespace
        ''',
        re.VERBOSE
    )

    re_node_end_decl = re.compile(r'^\s*}\s*$')

    re_color_decl = re.compile(
        r'''
          ^\s*                           # Start a new line ignore whitespace
          ((?:fill|line|font)-color):\s* # Mandatory name
          (\#[0-9a-f]{6} |               # RGB value of #012345
           \#[0-9a-f]{8} |               # RBGA value of #01234567
           none)                         # No color at all
          ;\s*                           # Closing ; immediately afterwards
          $
        ''',
        re.VERBOSE
    )

    re_dash_decl = re.compile(
        r'''
          ^\s*                           # Start a new line ignore whitespace
          (line-dash):\s*                # Mandatory name
          (none|(?:[0-9]+,[0-9]+))       # None or int list
          ;\s*                           # Closing ; immediately afterwards
          $
        ''',
        re.VERBOSE
    )

    re_float_decl = re.compile(
        r'''
          ^\s*                           # Start a new line ignore whitespace
          (line-width|font-size):\s*     # Mandatory name
          ([0-9]+(?:\.[0-9]+)?)          # Float
          ;\s*                           # Closing ; immediately afterwards
          $
        ''',
        re.VERBOSE
    )

    def __init__(
            self, css_file: Optional[str] = None,
            css_string: Optional[str] = None):
        '''
        Create a new stylesheet from either a file or a string. Only one of
        these two options can be used at a time!

        Args:
            css_file: Path to a CSS file, must be None if css_string set.
            css_string: CSS string, must be None if css_file set.

        Raises:
            ValueError: Parameter or parse errors are encountered.
        '''
        super().__init__()

        # If neither inputs are set then error
        if (css_file is None) and (css_string is None):
            raise ValueError('No input source specified')

        # If both inputs are set then error
        if (css_file is not None) and (css_string is not None):
            raise ValueError('Multiple input sources specified')

        # If we have a file input, load the string form of it
        if css_file:
            with open(css_file, 'r', encoding='utf-8') as handle:
                css_string = handle.read()

        self.parse_string(css_string, css_file)

    def parse_string(self, css_string: str, file_name: Optional[str]):
        '''
        Populate stylesheet from a CSS string.

        Args:
            css_string: The CSS data.
            file_name: File name if loaded from file.

        Raises:
            ValueError: Parse errors are encountered.
        '''
        self['<root>'] = CSSNode('<root>')

        line_no = 0
        lines = css_string.splitlines()

        # Parse line-wise
        try:
            current_nodes = []

            for line_no, line in enumerate(lines):
                # String out any comments and whitespace
                line = self.re_comment.sub('', line).strip()

                # Skip blank lines
                if not line:
                    continue

                # Handle node declarations
                if match := self.re_node_decl.match(line):
                    parent = match.group(1) if match.group(1) else '<root>'
                    nodes = [x.strip() for x in match.group(2).split(',')]
                    nodes = [self.get_node(x, parent) for x in nodes]
                    ending = match.group(3)
                    if not ending:
                        current_nodes = nodes
                    continue

                # ... and terminations
                if match := self.re_node_end_decl.match(line):
                    current_nodes = None
                    continue

                # Handle node field declarations for colors
                if match := self.re_color_decl.match(line):
                    key = match.group(1)
                    value = CSSColor(match.group(2))
                    for node in current_nodes:
                        node[key] = value
                    continue

                # Handle node field declarations for floats
                if match := self.re_float_decl.match(line):
                    key = match.group(1)
                    value = float(match.group(2))
                    for node in current_nodes:
                        node[key] = value
                    continue

                # Handle node field declarations for line dashes
                if match := self.re_dash_decl.match(line):
                    key = match.group(1)
                    value = CSSDash(match.group(2))
                    for node in current_nodes:
                        node[key] = value
                    continue

                # If we get here this line is an unknown so raise an error
                raise ValueError()

        # Generate a decent error message with file and line numbers
        except ValueError as exc:
            msg = '' if not file_name else f' in {file_name}'
            msg = f'CSS base syntax error: "{line}" @ line {line_no + 1}{msg}'
            raise ValueError(msg) from exc

        except KeyError as exc:
            msg = '' if not file_name else f' in {file_name}'
            msg = f'CSS parent syntax error: "{line}" @ line {line_no + 1}{msg}'
            raise ValueError(msg) from exc

    def get_node(self, name, parent='<root>', create=True):
        '''
        Fetch a CSS node, optionally creating it if it does not exist.

        If a node already exists the parent node name must match.

        Args:
            name: The node name.
            parent: The parent node name, or '<root>' to attach to root node.
                Set to None if we want to make a read-only fetch.
            create: True to create new nodes instead of raising an error.

        Raises:
            KeyError: Parent node does not exist.
            ValueError: Parent node mismatches.
        '''
        if parent:
            parent = self[parent]

        if (name not in self) and (parent is not None) and create:
            self[name] = CSSNode(name, parent)

        node = self[name]
        if parent and (parent != node.parent):
            raise ValueError()

        return node


class CSSColor(tuple):
    '''
    An RGBA color encoded as hex with a leading # character. The color may be
    RGB with 6 digits, RGBA with 8 digits, or 'none' if no color required.
    Generated colors are always 4 color components including an alpha channel.

    Color channels are always encoded using 2 lower-case hex digits each. W3C
    CSS shorthands that get expanded to a full color are not supported.

    NOTE: This class is really just a factory function for generating native
    tuples. Created instances will not be instances of CSSColor.
    '''

    def __new__(cls, color: str = 'none'):
        '''
        Create a new CSSColor tuple.

        Args:
            color: The color string, or "none" if no color required.
        '''
        if color == 'none':
            return None

        assert len(color) in [7, 9], f'Badly formed color string: "{color}"'
        assert color[0] == '#', f'Badly formed color string: "{color}"'

        r = float(int(color[1:3], 16)) / 255.0
        g = float(int(color[3:5], 16)) / 255.0
        b = float(int(color[5:7], 16)) / 255.0

        # Decode the alpha channel or force to opaque
        if len(color) == 9:
            a = float(int(color[7:9], 16)) / 255.0
        else:
            a = 1.0

        return (r, g, b, a)


class CSSFont(tuple):
    '''
    A Cairo font definition, storing a complete font specification in a single
    tuple (font face, slant, and weight).

    NOTE: This class is really just a factory function for generating native
    tuples. Created instances will not be instances of CSSFont.
    '''

    def __new__(cls, face: str = 'sans'):
        '''
        Create a new CSSFont tuple.

        Args:
            face: The font name.
        '''
        return (face, cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL)


class CSSDash(list):
    '''
    An Cairo dash definition, stored as a list of mark-space values or `none`
    if a solid line is desired.

    TODO: Do these have to be lists, or can we use tuples?

    NOTE: This class is really just a factory function for generating native
    lists. Created instances will not be instances of CSSFont.
    '''

    def __new__(cls, dash):
        '''
        Create a new CSSFont tuple.

        Args:
            dash: The dash specification.
        '''
        if dash == 'none':
            return []

        return [float(x) for x in dash.split(',')]


class CSSNode(dict):
    '''
    A single style node in the stylesheet graph hierarchy.

    Style properties in the node are accessed as dictionary lookups, e.g.:

        node['fill-color']

    Attributes:
        DEFAULT_FONT: The default font face name.
        DEFAULT_STYLES: The default values of all CSS styles.
        parent: The parent style name of this style in the DOM.
        name: The style name of this style in the DOM.
    '''

    if os.name == 'nt':
        DEFAULT_FONT = 'Consolas'
    else:
        DEFAULT_FONT = 'sans'

    DEFAULT_STYLES = {
        'fill-color': CSSColor('none'),
        'line-color': CSSColor('none'),
        'line-width': 1.0,
        'line-dash': CSSDash('none'),
        'font-color': CSSColor('none'),
        'font-face': CSSFont(DEFAULT_FONT),
        'font-size': 10
    }

    def __init__(self, name, parent=None):
        '''
        Create a new stylesheet style node.

        Parameters:
            name: The name of the style in the DOM.
            parent: The name of the parent style in the DOM.
                None if this is the '<root>' pseudo-style.
    '''
        super().__init__()
        self.parent = parent
        self.name = name

        assert (None is not parent) or (name == '<root>')

    def __getitem__(self, index):
        '''
        Get the value of a CSS property.

        TODO: Flatten at load-time for performance?

        Parameters:
            index: The name of the style property to fetch.
        '''
        try:
            return super().__getitem__(index)

        except KeyError:
            if None is not self.parent:
                return self.parent[index]

            return self.DEFAULT_STYLES[index]
