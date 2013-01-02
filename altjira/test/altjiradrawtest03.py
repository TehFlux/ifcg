#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2011 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiradrawtest03.py          Test script.
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
"""AltjiraDraw test 02."""
import time, os, math
import Altjira as ai
import AltjiraDraw as ad
import CGeoUtils as cg

outFile0 = 'temp' + os.path.sep + 'gradient02.png'

imageSize = 500
width = imageSize
height = imageSize

print("AltjiraDraw test 03")

d0 = ad.Drawable(width, height)
d0.fill(ai.Color.GRAY_60)

g0 = ad.LinearGradient(100, 100, imageSize - 100, imageSize - 100)
g0.addColorStop(0, ai.Color.BLUE)
g0.addColorStop(1, ai.Color.RED)

g1 = ad.RadialGradient(0.5 * imageSize, 0.5 * imageSize, 0, 
    0.5 * imageSize, 0.5 * imageSize, 0.5 * math.sqrt(2) * imageSize)
g1.addColorStop(0, ai.Color.BLACK)
g1.addColorStop(1, ai.Color.WHITE)

print("  Testing gradients...")
c0 = cg.Clock()
c0.start()
d0.begin()

d0.save()
d0.rectangle(0, 0, imageSize, imageSize)
d0.setSource(g1)
d0.fillPath()
d0.restore()

d0.save()
d0.rectangle(100, 100, imageSize - 200, imageSize - 200)
d0.setSource(g0)
d0.fillPath()
d0.restore()

d0.finish()
c0.stop()

d0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("  Statistics:")
print("    Drawing time: " + str(c0.getElapsedTime()) + " secs")

print("All tests completed!")

