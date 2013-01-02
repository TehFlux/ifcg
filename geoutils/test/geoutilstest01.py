#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Geoutils bounding box test."""
from geoutils import *

# Set up a simple bounding box hierarchy.
b00 = BoundingBox([-4., 0., 0.], [1.0, 1.0, 1.0], 'b00')
b01 = BoundingBox([-2., 0., 0.], [1.0, 1.0, 1.0], 'b01')
b02 = BoundingBox([2., 0., 0.], [1.0, 1.0, 1.0], 'b02')
b03 = BoundingBox([4., 0., 0.], [1.0, 1.0, 1.0], 'b03')

b10 = BoundingBox(itemID = 'b10')
b11 = BoundingBox(itemID = 'b11')

b20 = BoundingBox(itemID = 'b20')

b10.addItem(b00)
b10.addItem(b01)

b11.addItem(b02)
b11.addItem(b03)

b20.addItem(b10)
b20.addItem(b11)

i0 = BoxBoundsItem([-2., 0., 0.], [0.1, 0.1, 0.1])

bx = b20.getContainingLeaf(i0)
print "bx = " + str(bx) + ", bx.itemID = " + str(bx.itemID)

