#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiratest06.py          Test script.
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
"""Altjira test 06."""

import time
import Altjira as ai

inFile0 = 'test/images/sfgirl01.png'
outFile0 = 'temp/blur01.png'
outFile1 = 'temp/blur02.png'
blurRadius0 = 20
blurRadius1 = 20

print("Loading image...")
i0 = ai.Image(inFile0)
width = i0.getWidth()
height = i0.getHeight()
print("  width = " + str(width))
print("  height = " + str(height))

m0 = ai.Matrix(blurRadius0, blurRadius0)
m1 = ai.Matrix(blurRadius1, blurRadius1)
m0.setGaussian()
m1.setInversePower(2., 0.00001)
ir0 = ai.Image(width, height)
ir0.fill(ai.Color.WHITE)

print("Blurring image (gaussian blur)...")
t0 = time.time()
ir0.convolveFill(i0, m0)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("Blurring image (inverse power blur)...")
t0 = time.time()
ir0.convolveFill(i0, m1)
t1 = time.time()
print("    Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile1, ai.Image.TYPE_PNG)

print("All tests completed!")

