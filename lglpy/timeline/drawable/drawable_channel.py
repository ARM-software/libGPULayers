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
A DrawableChannel is a container for a sequence of time-ordered WorldDrawable
objects that can be rendered as a swimlane of some form as part of a
DrawableTrace.
'''

import bisect

from lglpy.timeline.drawable.primitive_rectangle import PrimitiveRectangle
from lglpy.timeline.drawable.world_drawable import WorldDrawableLine


class DrawableChannel:
    '''
    A container for world-space objects in a single swimlane.

    The container is optimized to ensure fast rendering, aiming to quickly cull
    unused or occluded objects, in particular for channels containing a
    sequence of opaque objects. There are two forms of culling scheme
    implemented.

    The first culling scheme is a simple bounding box cull which reduces the
    per-object iteration to those that are within the active viewport region.

    The second culling scheme is a pixel coverage cull scheme which can be used
    by channels that are rendering opaque boxes. For these channels we know
    that we only need a single object to cover each pixel in the swimlane.
    After rendering an object we can compute the lowest world-space coordinate
    that can intersect the next pixel that we want to draw, and then bisect a
    sorted list of objects in the swimlane to find the first object equal to or
    higher than that coordinate. This scheme results in a rendering complexity
    of:

        O((pixels/2) * log2(objects/2))

    ... which gives good performance, even when software rendering channels
    containing a million objects using Python!

    To support this culling mechanism, objects in a channel must be stored in
    a sorted fashion during rendering. To ensure fast builds, objects are
    initially appended to the channel without any sorting. The channel must
    then be compiled before rendering, to ensure correct ordering.

    Attributes:
        name: name of this channel.
        trace: parent trace this channel belongs to.
        ws_bounds: world-space bounds of this channel.
        layer: rendering drawing z-order. Layers rendered from low-to-high.
        visible: is this channel visible?
        label_visible: is this channel's label visible?
        interactable: are objects in this this channel interactable?
        coverage_cullable: are objects in this channel coverage cullable?
        objects: sorted array of objects, stored by start time
        objects_x_min: sorted array of object start times
        objects_x_max: sorted array of object end times, sorted by start time
        compiled: flag indicating that the channel has been compiled
    '''

    def __init__(self, name, trace, layer, coverage_cullable=False,
                 interactable=False):
        '''
        Create a new channel instance.

        Args:
            name: name of this channel.
            trace: parent trace this channel belongs to.
            layer: rendering drawing z-order. Layers rendered from low-to-high.
                visible: is this channel visible?
            coverage_cullable: are objects in this channel coverage cullable?
            interactable: are objects in this this channel interactable?
        '''
        self.name = name
        self.trace = trace
        self.layer = layer
        self.ws_bounds = None

        self.coverage_cullable = coverage_cullable
        self.interactable = interactable
        self.visible = True
        self.label_visible = True

        if None is not trace:
            trace.add_channel(self)

        self.objects = []
        self.objects_x_min = []
        self.objects_x_max = []

        # Objects are added unsorted and must be "compiled" before rendering
        self.compiled = False

    def add_object(self, drawable):
        '''
        Add a new world-drawable object to this channel.

        To allow fast construction of a trace from a large data set, objects
        are simply appended to the object list without attempting to sort into
        time-order. Channels must compiled after objects have been added before
        they can be used for rendering operations.

        Args:
            drawable: the world-drawable object to add to the channel.
        '''
        self.objects.append(drawable)
        self.compiled = False

    def compile(self):
        '''
        Compile into sorted drawables ready for optimized rendering.
        '''
        # Don't compile if we are already compiled ...
        if self.compiled:
            return

        self.compiled = True

        # If we have no objects, then don't do anything at all ...
        if not self.objects:
            return

        # Sort, and build the flat bisect index arrays
        self.objects.sort(key=lambda x: x.ws.min_x)
        self.objects_x_min = [x.ws.min_x for x in self.objects]
        self.objects_x_max = [x.ws.max_x for x in self.objects]

        # Update the channel world-space bounds
        min_x = self.objects_x_min[0]
        x_dim = self.objects_x_max[-1] - min_x
        min_y = self.objects[0].ws.min_y
        y_dim = self.objects[0].ws.max_y - min_y

        self.ws_bounds = PrimitiveRectangle((min_x, min_y), (x_dim, y_dim))

        # Update the parent trace world-space bounds
        if self.trace:
            self.trace.extend_bounds(self.ws_bounds)

    def __iter__(self):
        '''
        Generator which yields all objects in list order. After compilation
        list order is object start time order.

        Yields:
            Objects in list order.
        '''
        yield from self.objects

    def __len__(self):
        '''
        Number of objects in this channel.

        Returns:
            The number of objects stored.
        '''
        return len(self.objects)

    def each_object(self, obj_filter=None, ws_range=None):
        '''
        Generator which yields filtered objects from the channel in list order.
        After compilation list order is object start time order.

        The object filter function takes each object in the channel, and must
        return True if the object should be yielded by the generator, or False
        if it should be skipped.

        Args:
            obj_filter: object filter function, or None if no filtering.
            ws_range: world-space extents withing which objects should be
                returned, or None if no filtering. Note that this is just an
                optimization hint, and objects outside of this range may be
                returned.

        Yields:
            Objects in list order, subject to filtering.
        '''
        assert self.compiled

        if ws_range:
            start_index = bisect.bisect(self.objects_x_min, ws_range[0])
            end_index = bisect.bisect(self.objects_x_min, ws_range[1]) + 1
        else:
            start_index = 0
            end_index = len(self.objects)

        for i in range(start_index, end_index):
            user_object = self.objects[i]
            if (obj_filter is None) or obj_filter(user_object):
                yield user_object

    def get_clicked_object(self, ws_x, ws_y):
        '''
        Get the object at the specified world-space coordinate.

        Objects can only be selected if their parent channel is both visible
        and interactable.

        Args:
            ws_x: the world-space X coordinate.
            ws_y: the world-space Y coordinate.

        Returns:
            The drawable object if clicked, or None if no intersection.
        '''
        assert self.compiled

        # If the channel doesn't support interacting then fail early ...
        if not self.interactable or not self.visible:
            return None

        # If the click is outside of the channel bounds, then fail early ...
        if (not self.ws_bounds) or (not self.ws_bounds.is_hit_by(ws_x, ws_y)):
            return None

        # Find the object using bisect - we only have to check x, as the
        # channel would have failed if outside of y ...
        index = bisect.bisect(self.objects_x_max, ws_x)

        # Insert after last object means the click missed
        if index < len(self.objects):
            user_object = self.objects[index]
            if user_object.ws.is_hit_by(ws_x, ws_y):
                return user_object

        return None

    def get_boxed_objects(self, ws_x_min, ws_y_min, ws_x_max, ws_y_max):
        '''
        Get objects which are completely encapsulated by the bounding box.

        Args:
            ws_x_min: world-space X coordinate at the start of the box.
            ws_y_min: world-space Y coordinate at the start of the box.
            ws_x_max: world-space X coordinate at the end of the box.
            ws_y_max: world-space Y coordinate at the end of the box.

        # TODO: Make box a PrimRect

        Returns:
            List of intersecting objects, or empty list if no intersections.
        '''
        assert self.compiled

        # If the channel doesn't support interacting then fail early ...
        if not self.interactable or not self.visible:
            return []

        # If the drag is outside of the channel bounds, then fail early ...
        pos = (ws_x_min, ws_y_min)
        dim = (ws_x_max - ws_x_min, ws_y_max - ws_y_min)
        bbox = PrimitiveRectangle(pos, dim)
        if not self.ws_bounds or not self.ws_bounds.intersects(bbox):
            return []

        # Drop the entire channel if the drag does not enclose the full height
        # of the channel (drag has to totally enclose an object to succeed)
        if (self.ws_bounds.min_y < ws_y_min) or \
           (self.ws_bounds.max_y > ws_y_max):
            return []

        # Do a fast selection using bisect to pick the ranges ...
        # Note: This works for our use because solid interactable objects
        # don't overlap. Works well enough for current usage, but beware!
        start_index = bisect.bisect(self.objects_x_min, ws_x_min)
        end_index = bisect.bisect(self.objects_x_max, ws_x_max)
        if start_index >= end_index:
            return []

        return self.objects[start_index:end_index]

    def draw(self, gc, vp, ws_range=None):
        '''
        Draw this channel onto a Cairo canvas, using the given viewport.

        Args:
            gc: Cairo graphics context.
            vp: visible viewport
            ws_range: world-space extents withing which objects should be
                returned, or None if no filtering. Note that this is just an
                optimization hint, and objects outside of this range may be
                drawn.
        '''
        del ws_range  # unused

        # Lowest object we need is the last one to cover first WS value
        start_index = bisect.bisect_left(self.objects_x_max, vp.ws.min_x)

        # Highest object we need is the first one to cover the last WS value
        end_index = bisect.bisect_right(self.objects_x_min, vp.ws.max_x)
        end_index = min(end_index, len(self.objects) - 1)

        # Start with the minimum object
        index = start_index

        # If we can't do culling then just iterate all objects in range
        if not self.coverage_cullable:
            while index <= end_index:
                user_object = self.objects[index]
                user_object.draw(gc, vp)
                index += 1

        # If we can do culling then insert bisect jumps as needed
        else:
            bisect_left = bisect.bisect_left
            while index <= end_index:
                user_object = self.objects[index]
                user_object.draw(gc, vp)

                # Lowest object we need is the first object to cover next WS
                next_ws = vp.coverage_cull_next_ws_x
                index = bisect_left(self.objects_x_max, next_ws, index + 1)
