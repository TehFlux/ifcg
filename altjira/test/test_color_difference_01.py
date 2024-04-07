#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2024 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# test_color_difference.py          Test script.
# ==========================================================================
# 
# This file is part of Altjira - Ionflux' Image Processing Library.
# 
# Altjira - Ionflux' Image Processing Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 3 of the License, or (at your option) any later version.
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

import Altjira as ai
import IFMapping as im

inFile0 = 'test/images/chart_01.png'
outFile0 = 'temp/color_difference_01.png'
curveFile01 = 'test/curves/curve03.svg'

print("Loading image...")

i0 = ai.Image(inFile0)
width = i0.getWidth()
height = i0.getHeight()
print("  width = " + str(width))
print("  height = " + str(height))

# Create mapping
ms0 = im.MappingSet()

# invert value
m2 = im.Linear.create()
m2.setLower(1.)
m2.setUpper(0.)

print("Loading curve data from file...")

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
m1.setFunc(m2)
ms0.addMapping(m1)

print("Calculating color difference...")

targetImage = ai.Image(width, height)

refColor = ai.Color()
refColor.setFromHex("#32ca5b")

#c0 = ai.Color(ai.Color.BLUE)
#print(str(c0.getMeanSquaredError(refColor)))

i0.getColorDifference(refColor, targetImage, m1)

print("Writing result to image file: " + outFile0)

targetImage.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("All tests completed!")
