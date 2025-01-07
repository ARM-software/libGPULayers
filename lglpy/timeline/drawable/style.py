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
This module contains hierarchy of classes that can be used to define a set of
related visual styles for rendering drawable objects on a Cairo canvas. The
three classes in the hierarchy are:

  - StyleSetLibrary
  - StyleSet
  - Style

A Style instance defines the render state for a visual style used in rendering.
Styles can be used standalone, and do not need to be used as a part of a
bundled StyleSet.

A StyleSet defines a set of variants for a single style, allowing a single
object to have a different look depending on render state. The variants that
are currently supported are:

  - highlight
  - normal
  - fade
  - hide

The 'normal' variant is mandatory, but the others are optional. If a variant is
missing the library will perform search towards normal. For example, if there
is no 'hide' style, then the set will attempt to return 'fade', and if that
does not exist will return 'normal'.

A StyleSetLibrary is a collection of StyleSet instances, which can be looked
up by name. Libraries are read-only and designed to be shared by multiple
user interface components.
'''

from lglpy.timeline.drawable.drawable import FONT


class Style:
    '''
    A style defining a set of color, line, font styles to use when rendering.

    Attributes:
        variant: the variant name of this style.
        style_set: parent style set for this style, may be None.
        font: font to use for text labels.
        font_size: font size to use for text labels.
        font_color: color to use for text labels.
        fill_color: color to use for object fill.
        line_width: width of lines, in pixels.
        line_color: color to use for lines.
        line_dash: dash style for lines.
    '''

    __slots__ = (
        'variant', 'style_set', 'font', 'font_color', 'font_size',
        'fill_color', 'line_color', 'line_width', 'line_dash'
    )

    def __init__(self, variant=None):
        '''
        Create a new style instance, assigning defaults if needed.

        Note that all colors are initialized to None, so no objects will be
        visible unless a color is assigned.

        Args:
            variant: variant name of this style. If in a StyleSet this must
                be one of the standard variant names.
        '''
        # If we have a variant check it is valid
        if None is not variant:
            assert variant in StyleSet.VARIANTS

        self.variant = variant
        self.style_set = None

        self.font = FONT
        self.font_color = None
        self.font_size = 10.0

        self.fill_color = None

        self.line_color = None
        self.line_width = 1.0
        self.line_dash = []

    @classmethod
    def css_factory(cls, css_style, variant=None):
        '''
        Create and return a new `Style` object from a CSS node.

        All settings will be populated, using the CSS cascade/root settings if
        the given style does not define them.

        Args:
            css_style: CSS node to source settings from.
            variant: variant name of this style. If used in a StyleSet this
                must be one of the standard variant names.

        Returns:
            Returns the new constructed style object.
        '''
        style = cls(variant)
        style.load_from_css(css_style)
        return style

    def load_from_css(self, css_style):
        '''
        Populate this style from a CSS node.

        Args:
            css_style: CSS node to source settings from.
        '''
        self.font = css_style['font-face']
        self.font_color = css_style['font-color']
        self.font_size = css_style['font-size']

        self.fill_color = css_style['fill-color']

        self.line_color = css_style['line-color']
        self.line_width = css_style['line-width']
        self.line_dash = css_style['line-dash']

    def bind_font(self, gc):
        '''
        Bind all Cairo render state needed for rendering labels.

        Args:
            gc: Cairo graphics context.

        Returns: bool
            True if this style has a visible font, False otherwise.
        '''
        if not self.font_color:
            return False

        gc.set_source_rgba(*self.font_color)
        gc.select_font_face(*self.font)
        gc.set_font_size(self.font_size)
        return True

    def bind_line(self, gc):
        '''
        Bind all Cairo render state needed for rendering lines.

        Args:
            gc: Cairo graphics context.

        Returns: bool
            True if this style has a visible line, False otherwise.
        '''
        if not self.line_color:
            return False

        gc.set_source_rgba(*self.line_color)
        gc.set_line_width(self.line_width)
        gc.set_dash(self.line_dash)
        return True

    def bind_fill(self, gc):
        '''
        Bind all Cairo render state for rendering fills.

        Args:
            gc: Cairo graphics context.

        Returns: bool
            True if this style has a visible fill, False otherwise.
        '''
        if not self.fill_color:
            return False

        gc.set_source_rgba(*self.fill_color)
        return True


class StyleSet(dict):
    '''
    A set of related styles for a drawable object.

    Four style variants are currently allowed:

    - highlight: style used to draw attention
    - normal: style used by default
    - fade: style used to recess into the background
    - hide: style used to severely recess in to the background, or totally hide

    The normal variant is mandatory, the others are all optional. Attempting to
    select a variant which is missing will result in the next variant closer to
    normal being selected. For example, if you attempt to select the hide
    variant the search order will be: hide, fade, normal.

    Attributes:
        VARIANTS: list of variants and their search order.
        name: name of this style set.
    '''

    VARIANTS = {
        'highlight': ['highlight', 'normal'],
        'normal': ['normal'],
        'fade': ['fade', 'normal'],
        'hide': ['hide', 'fade', 'normal'],
    }

    def __init__(self, name):
        '''
        Create a new style set.

        Args:
            name: name of this style set.
        '''
        super().__init__()
        self.name = name

    def validate(self):
        '''
        Check that this style set is valid.

        Raises:
            AssertionError: Style set is missing mandatory 'normal' style.
        '''
        assert 'normal' in self

    def add_style(self, variant, style):
        '''
        Add a new variant style to this set.

        It is an error to add the same variant more than once, and it is also
        invalid to add a Style instance to more than one set.

        Args:
            variant: name of the variant to store.
            style: style variant to store.
        '''
        assert variant not in self
        assert variant in self.VARIANTS
        assert None is style.style_set

        self[variant] = style
        style.style_set = self

    def get_style(self, variant):
        '''
        Return the style matching the named variant.

        Args:
            variant: name of the variant to fetch.
        '''
        search_order = self.VARIANTS[variant]
        for search_variant in search_order:
            if search_variant in self:
                return self[search_variant]

        # Every search includes 'normal' which is mandatory, so should not fail
        assert False, f'Style set {self.name} missing "normal" variant'


class StyleSetLibrary(dict):
    '''
    A set of related style sets.
    '''

    def add_style_set(self, style_set):
        '''
        Add a new style set to the library.

        Style names must be unique.

        Args:
            style_set: the style set to add to the library
        '''
        assert style_set.name not in self
        self[style_set.name] = style_set

    def get_style_set(self, name):
        '''
        Get a style set from the library.

        Args:
            name: name of the style set.

        Returns:
            The style set if present.

        Raises:
            KeyError: Named style set does not exist.
        '''
        return self[name]

    def get_style(self, name, variant='normal'):
        '''
        Get a style from the library.

        Args:
            name: name of the style set.
            variant: name of the style variant.

        Returns:
            The style for named set and variant.

        Raises:
            KeyError: Named style set does not exist.
        '''
        return self[name].get_style(variant)

    def __str__(self):
        '''
        Return a debug string representation of this class.
        '''
        return str(sorted(self.keys()))
