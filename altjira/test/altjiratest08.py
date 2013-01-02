#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiratest07.py          Test script.
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
"""Altjira test 08."""

import time
import IFMapping as im
import Altjira as ai

inFile0 = 'test/images/sfgirl01.png'
inFile1 = 'test/images/colors01.png'
outFile0 = 'temp/channels01a.png'
outFile1 = 'temp/channels02a.png'
outFile2 = 'temp/channels03a.png'
outFile3 = 'temp/channels04a.png'
outFile4 = 'temp/channels05.png'
curveFile01 = 'test/curves/curve01.svg'

print("Loading images...")
i0 = ai.Image(inFile0)
i0a = ai.Image(inFile0)
width = i0.getWidth()
height = i0.getHeight()
print("  width = " + str(width))
print("  height = " + str(height))
i1 = ai.Image(inFile1)
i2 = ai.Image(inFile1)
i3 = ai.Image(inFile1)
i4 = ai.Image(inFile1)

print("Loading curve data from file...")
ms0 = im.MappingSet()
cWidth = 1000
cHeight = 1000
pScale = cWidth
pOffset = 0.
fOffset = im.Point(0., 1., 0.)
fScale = im.Point(1. / cWidth, -1. / cHeight, 1.)
d0 = im.getAttrValue(curveFile01, 'path', 'spline01', 'd')
c0 = im.BezierSpline.create()
c0.initFromSVG(d0)
m0 = c0.createFunc(pScale, pOffset, fScale, fOffset)
# Create a LUT for a huge performance boost.
m1 = im.Lookup.create()
m1.setSource(m0)
m1.update(256)

print("Creating color blenders...")

bl0 = ai.BlendChannel()
bl0.setSrcChannel(ai.CH_LUMINANCE)
bl0.setDestChannel(ai.CH_LUMINANCE)

bl1 = ai.BlendChannel()
bl1.setSrcChannel(ai.CH_SATURATION)
bl1.setDestChannel(ai.CH_SATURATION)
bl1.setSrcSpace(ai.Color.SPACE_HSV)
bl1.setDestSpace(ai.Color.SPACE_HSL)

bl2 = ai.BlendChannel()
bl2.setSrcChannel(ai.CH_VALUE)
bl2.setDestChannel(ai.CH_VALUE)

bl3 = ai.BlendChannel()
bl3.setSrcChannel(ai.CH_LUMINANCE)
bl3.setDestChannel(ai.CH_LUMINANCE)
bl3.setSrcFunc(m1)

bl4 = ai.BlendChannel()
bl4.setSrcChannel(ai.CH_HUE)
bl4.setDestChannel(ai.CH_HUE)
bl4.setSrcSpace(ai.Color.SPACE_HSL)
bl4.setDestSpace(ai.Color.SPACE_HSL)

bl5 = ai.BlendChannel()
bl5.setSrcChannel(ai.CH_LUMINANCE)
bl5.setDestChannel(ai.CH_LUMINANCE)
bl5.setSrcFunc(m1)
bl5.setSourceOpacity(0.8)
bl5.setTargetOpacity(0.2)

print("Compositing luminance/saturation channels...")
t0 = time.time()
i1.composite(i0, bl0)
i1.composite(i2, bl1)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i1.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("Compositing value channel...")
t0 = time.time()
i2.composite(i0, bl2)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i2.writeToFile(outFile1, ai.Image.TYPE_PNG)

print("Compositing luminance channel (with mapping)...")
t0 = time.time()
i3.composite(i0, bl3)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i3.writeToFile(outFile2, ai.Image.TYPE_PNG)

print("Compositing hue channel...")
t0 = time.time()
i0a.composite(i4, bl4)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i0a.writeToFile(outFile3, ai.Image.TYPE_PNG)

print("Compositing luminance channel (with mapping, using opacity)...")
t0 = time.time()
i4.composite(i0, bl5)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i4.writeToFile(outFile4, ai.Image.TYPE_PNG)

print("All tests completed!")

