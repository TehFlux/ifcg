#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2024 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiradrawtest02.py          Test script.
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
"""AltjiraDraw test 02."""
import os
import Altjira as ai
import AltjiraDraw as ad
import CGeoUtils as cg

inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'leaf01.svg'
outFile0 = 'temp' + os.path.sep + 'drawing02.png'

sourceSize = 1000
imageSize = 500
width = imageSize
height = imageSize
scale0 = imageSize / sourceSize

print("AltjiraDraw test 02")

d0 = ad.Drawable(width, height)
d0.fill(ai.Color.GRAY_60)

print("  Drawing SVG...")
c0 = cg.Clock()
c0.start()
d0.begin()

d0.save()
d0.scale(scale0, scale0)
d0.translate(-0.5 * imageSize, -0.5 * imageSize)
d0.drawSVGFile(inFile0)
d0.restore()

d0.finish()
c0.stop()

d0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("  Statistics:")
print("    Drawing time: " + str(c0.getElapsedTime()) + " secs")

print("All tests completed!")

