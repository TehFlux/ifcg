#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiratest01.py          Test script.
# ==========================================================================
# 
# This file is part of Altjira - Ionflux' Image Processing Library.
# 
# Altjira - Ionflux' Image Processing Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later version.
# 
# Altjira - Ionflux' Image Processing Library is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Altjira - Ionflux' Image Processing Library; if not, write to 
# the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
# MA 02111-1307 USA
# 
# ==========================================================================
"""Altjira image test 01."""

import time
import Altjira as ai
import os

width = 1024
height = 1024
outputDir = 'temp'

img0 = ai.Image(width, height)

c0 = ai.Color(1., 0., 0., 1.)
bc0 = ai.ByteColor()
c0.getByteColor(bc0)
c1 = ai.Color(0., 1., 0., 1.)

#print "Fill test #1 (Python loop)..."
#t0 = time.time()
#for x in xrange(0, width):
#    for y in xrange(0, height):
#        img0.setPixel(x, y, bc0)
#t1 = time.time()
#img0.writeToFile('test01.png')
#print ("Done (" + str(width * height) +" pixels filled in " + str(t1 - t0) 
#    + " secs, " + str(width * height / (t1 - t0)) + " px/s)")

print("Fill test...")
t0 = time.time()
img0.fill(c1)
t1 = time.time()
img0.writeToFile(outputDir + os.path.sep + 'test02.png')
print("Done (" + str(width * height) +" pixels filled in " + str(t1 - t0) 
    + " secs, " + str(width * height / (t1 - t0)) + " px/s)")

print("Color space conversion...")
c2 = ai.Color(0.6, 0.3, 0.9, 1.)
print("c2 = " + c2.getHex())
fc0 = ai.FloatColor()
c2.getFloatColor(fc0)
print("fc0 (RGB #0) = " + ai.getString(fc0))
ai.toHSV(fc0)
print("fc0 (HSV #1) = " + ai.getString(fc0))
ai.toRGB(fc0)
print("fc0 (RGB #2) = " + ai.getString(fc0))
ai.toHSL(fc0)
print("fc0 (HSL #3) = " + ai.getString(fc0))
ai.toRGB(fc0)
print("fc0 (RGB #4) = " + ai.getString(fc0))

print("Copy test...")
t0 = time.time()
img1 = ai.Image(img0)
t1 = time.time()
img0.writeToFile(outputDir + os.path.sep + 'test03.png')
print("Done (image with " + str(img0.getWidth() * img0.getHeight()) 
    + " pixels copied in " + str(t1 - t0) + " secs, " 
    + str(img0.getWidth() * img0.getHeight() / (t1 - t0)) + " px/s)")

print("Region fill test...")
img0.fill(c0)
r0 = ai.ImageRect()
r0.x = 0
r0.y = 0
r0.width = 100
r0.height = 100
t0 = time.time()
img1.fill(img0, r0, 100, 100)
t1 = time.time()
img0.writeToFile(outputDir + os.path.sep + 'test04a.png')
img1.writeToFile(outputDir + os.path.sep + 'test04b.png')
print("Done (" + str(r0.width * r0.height) + " pixels filled in " 
    + str(t1 - t0) + " secs, " + str(r0.width * r0.height / (t1 - t0)) 
    + " px/s)")

print("All tests completed!")

