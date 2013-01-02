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
"""Altjira test 07."""

import time
import IFMapping as im
import Altjira as ai

inFile0 = 'test/images/sfgirl01.png'
inFile1 = 'test/images/colors01.png'
outFile0 = 'temp/channels01.png'
outFile1 = 'temp/channels02.png'
outFile2 = 'temp/channels03.png'
outFile3 = 'temp/channels04.png'
curveFile01 = 'test/curves/curve01.svg'

print("Loading images...")
i0 = ai.Image(inFile0)
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
ms0.addMapping(m1)

print("Copying luminance/saturation channels...")
t0 = time.time()
i1.setChannel(i0, ai.CH_LUMINANCE, ai.CH_LUMINANCE)
# Saturation in HSL may be inaccurate so take it from the HSV model.
i1.setChannel(i2, ai.CH_SATURATION, ai.CH_SATURATION, None, 
    ai.Color.SPACE_HSV, ai.Color.SPACE_HSL)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i1.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("Copying value channel...")
t0 = time.time()
i2.setChannel(i0, ai.CH_VALUE, ai.CH_VALUE)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i2.writeToFile(outFile1, ai.Image.TYPE_PNG)

print("Copying luminance channel (with mapping)...")
t0 = time.time()
i3.setChannel(i0, ai.CH_LUMINANCE, ai.CH_LUMINANCE, m1)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i3.writeToFile(outFile2, ai.Image.TYPE_PNG)

print("Copying hue channel...")
t0 = time.time()
i0.setChannel(i4, ai.CH_HUE, ai.CH_HUE, None, ai.Color.SPACE_HSL, 
    ai.Color.SPACE_HSL)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
i0.writeToFile(outFile3, ai.Image.TYPE_PNG)

print("All tests completed!")

