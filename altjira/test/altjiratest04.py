#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiratest04.py          Test script.
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
"""Altjira test 04."""

import time
import Altjira as ai

inFile0 = 'test/images/sfgirl01.png'
inFile1 = 'test/images/mask01.png'
outFile0 = 'temp/composite01.png'
outFile1 = 'temp/composite02.png'
outFile2 = 'temp/composite03.png'
outFile3 = 'temp/composite04.png'
outFile4 = 'temp/composite05.png'
outFile5 = 'temp/composite06.png'

print("Altjira test 04")
print("  Loading images...")
i0 = ai.Image(inFile0)
i1 = ai.Image(inFile1)
width = i0.getWidth()
height = i0.getHeight()
print("    i0.numChannels = " + str(i0.getNumChannels()))
print("    i1.numChannels = " + str(i0.getNumChannels()))
print("    width = " + str(width))
print("    height = " + str(height))

print("  Compositing images...")
print("    100% source opacity, 100% target opacity...")
ir0 = ai.Image(width, height)
ir0.fill(i0)
t0 = time.time()
ir0.composite(i1)
t1 = time.time()

print("      Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("    50% source opacity, 100% target opacity...")
b1 = ai.BlendSrcOver()
b1.setSourceOpacity(0.5)
ir0.fill(i0)
t0 = time.time()
ir0.composite(i1, b1)
t1 = time.time()
print("      Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile1, ai.Image.TYPE_PNG)

print("    50% source opacity, 50% target opacity...")
b1.setTargetOpacity(0.5)
ir0.fill(i0)
t0 = time.time()
ir0.composite(i1, b1)
t1 = time.time()
print("      Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile2, ai.Image.TYPE_PNG)

print("    100% source opacity, 100% target opacity (multiply)...")
b2 = ai.BlendMultiply()
ir0.fill(i0)
t0 = time.time()
ir0.composite(i1, b2)
t1 = time.time()
print("      Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile3, ai.Image.TYPE_PNG)

print("    100% source opacity, 100% target opacity (lighten)...")
b3 = ai.BlendLighten()
ir0.fill(i0)
t0 = time.time()
ir0.composite(i1, b3)
t1 = time.time()
print("      Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile4, ai.Image.TYPE_PNG)

print("    100% source opacity, 100% target opacity (darken)...")
b4 = ai.BlendDarken()
ir0.fill(i0)
t0 = time.time()
ir0.composite(i1, b4)
t1 = time.time()
print("      Done (" + str(width * height) +" pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s)")
ir0.writeToFile(outFile5, ai.Image.TYPE_PNG)

print("All tests completed!")
