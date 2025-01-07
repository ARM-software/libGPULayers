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
A DrawableTrace is a container for a set of WorldDrawable objects that have
been grouped into one or more DrawableChannels.
'''

import copy


class DrawableTrace:
    '''
    A container for a series of world-space drawable channels.

    During construction of a trace, all DrawableChannel instances must be
    added to the trace before objects are added to the channels, allowing the
    trace to track world-space extents.

    Attributes:
        ws_bounds: The world-space bounding volume of the objects. May be None
            if no objects were added. Bounds are only synced when the channels
            are compiled, after all objects have been added.
        channels: A list of DrawableChannels in the trace, stored in layer to
            allow iteration during rendering.
        channel_map: A dict mapping channel name to DrawableChannel instance
        style: The style to use for the trace background and overlay labels.
            Channels and their objects have their own independent styles.
    '''

    def __init__(self, style):
        '''
        Create a new drawable trace.

        Args:
            style: visual style.
        '''
        self.ws_bounds = None
        self.channels = []
        self.channel_map = {}
        self.style = style

    def add_channel(self, channel):
        '''
        Add a new channel to the trace.

        Channels must be added before any objects are added to them.

        Args:
            channel: drawable channel to add.
        '''
        self.channels.append(channel)
        self.channel_map[channel.name] = channel

        # Keep channel list sorted in layer order
        self.channels.sort(key=lambda x: x.layer)

    def get_channel(self, channel_name):
        '''
        Get the channel with the given name.

        Args:
            channel_name: name of the channel channel to find.

        Returns:
            The drawable channel.

        Raises:
            KeyError: Channel was not found in this trace.
        '''
        return self.channel_map[channel_name]

    def __iter__(self):
        '''
        Generator which yields all channels in layer order.

        Channels in the same layer are returned in arbitrary order.

        Yields:
            Channels in layer order.
        '''
        yield from self.channels

    def each_channel(self, ch_filter=None):
        '''
        Generator which yields filtered channels from the trace in layer order.

        Channels in the same layer are returned in arbitrary order.

        Filter function takes each DrawableChannel, and must return True if the
        channel should be yielded by the generator, or False if it should be
        skipped.

        Args:
            ch_filter: channel filter function, or None if no filtering.

        Yields:
            Channels in layer order, subject to caller-defined filtering.
        '''
        for channel in self.channels:
            if not ch_filter or ch_filter(channel):
                yield channel

    def each_object(self, ch_filter=None, obj_filter=None, ws_range=None):
        '''
        Generator which yields filtered objects from the trace in layer order.

        Objects are returned channel-by-channel, in start time order within
        each channel. Channels in the same layer are iterated in arbitrary
        order.

        The channel filter function takes each DrawableChannel, and must return
        True if objects in the channel should be yielded by the generator, or
        False if they should be skipped.

        The object filter function takes each object in the channel, and must
        return True if the object should be yielded by the generator, or False
        if it should be skipped.

        Args:
            ch_filter: channel filter function, or None if no filtering.
            obj_filter: object filter function, or None if no filtering.
            ws_range: world-space extents withing which objects should be
                returned, or None if no filtering. Note that this is just an
                optimization hint, and objects outside of this range may be
                returned.

        Yields:
            Objects in by-channel by-time ordering, subject to filtering.
        '''
        for channel in self.each_channel(ch_filter):
            yield from channel.each_object(obj_filter, ws_range)

    def extend_bounds(self, rect):
        '''
        Extend the bounds of the this container.

        Args:
            rect: the new rectangle to include in the bounds.
        '''
        if self.ws_bounds is None:
            self.ws_bounds = copy.copy(rect)
        else:
            self.ws_bounds.extend_rect(rect)

    def get_clicked_object(self, ws_x, ws_y):
        '''
        Get the object at the specified world-space coordinate.

        Objects can only be selected if their parent channel is both visible
        and interactable.

        Args:
            ws_x: the world-space X coordinate.
            ws_y: the world-space Y coordinate

        Returns:
            The drawable object if clicked, or None if no intersection.
        '''
        def ch_filter(x):
            return x.interactable and x.visible

        for channel in self.each_channel(ch_filter=ch_filter):
            clicked_object = channel.get_clicked_object(ws_x, ws_y)
            if clicked_object:
                return clicked_object

        return None

    def get_boxed_objects(self, ws_x_min, ws_y_min, ws_x_max, ws_y_max,
                          ch_filter=None):
        '''
        Get the set of objects which are encapsulated by a bounding box.

        Objects can only be selected if their parent channel is both visible
        and interactable.

        The channel filter function takes each DrawableChannel, and must return
        True if objects in the channel should be yielded by the generator, or
        False if they should be skipped.

        # TODO: Make box a PrimRect

        Args:
            ws_x_min: the world-space X coordinate at the start of the box.
            ws_y_min: the world-space Y coordinate at the start of the box.
            ws_x_max: the world-space X coordinate at the end of the box.
            ws_y_max: the world-space Y coordinate at the end of the box.
            ch_filter: channel filter function, or None if no filtering.

        Returns:
            List of objects inside the box, or an empty list if no objects are
            inside the box.
        '''
        if ch_filter:
            def ch_filter2(x):
                return ch_filter(x) and x.interactable and x.visible
        else:
            def ch_filter2(x):
                return x.interactable and x.visible

        objects = []
        for channel in self.each_channel(ch_filter=ch_filter2):
            new_objects = channel.get_boxed_objects(ws_x_min, ws_y_min,
                                                    ws_x_max, ws_y_max)
            objects.extend(new_objects)

        return objects

    def draw(self, gc, vp, ch_filter=None, ws_range=None, labels=False):
        '''
        Draw this trace onto a Cairo canvas, using the given viewport.

        The channel filter function takes each DrawableChannel, and must return
        True if objects in the channel should be drawn. Channels that are
        not visible are always skipped, irrespective of the callee filter.

        Args:
            gc: Cairo graphics context.
            vp: visible viewport
            ch_filter: channel filter function, or None if no filtering.
            ws_range: world-space extents withing which objects should be
                returned, or None if no filtering. Note that this is just an
                optimization hint, and objects outside of this range may be
                returned.
            labels: are channel name labels enabled?
        '''
        if ch_filter:
            def ch_filter2(x):
                return ch_filter(x) and x.visible
        else:
            def ch_filter2(x):
                return x.visible

        # Draw the main channel data first for all channels
        for channel in self.each_channel(ch_filter2):
            vp.enable_coverage_culling(channel.coverage_cullable)
            channel.draw(gc, vp, ws_range)

        # Draw the labels on top
        if labels and self.style.bind_font(gc):
            def ch_filter3(x):
                return ch_filter2(x) and x.label_visible and x.ws_bounds

            for channel in self.each_channel(ch_filter3):
                x = vp.cs.min_x + 15
                y = vp.cs.min_y + channel.ws_bounds.min_y - 7
                gc.move_to(x, y)
                gc.show_text(channel.name)
