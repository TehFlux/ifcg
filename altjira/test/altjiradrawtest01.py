#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2024 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiradrawtest01.py          Test script.
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
"""AltjiraDraw test 01."""
import os, math
import Altjira as ai
import AltjiraDraw as ad
import CGeoUtils as cg

inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'sfgirl01.png'
outFile0 = 'temp' + os.path.sep + 'drawing01.png'

imageSize = 500
width = imageSize
height = imageSize

print("AltjiraDraw test 01")

d0 = ad.Drawable(width, height)
d0.fill(ai.Color.GRAY_60)

print("  Drawing shapes...")
c0 = cg.Clock()
c0.start()
d0.begin()

d0.translate(0.5 * width + 0.5, 0.5 * height + 0.5)
d0.arc(0., 0., 200.)
d0.setSourceColor(ai.Color.GREEN)
d0.fillPath()

d0.rectangle(-120., -100., 240., 200.)
d0.setSourceColor(ai.Color.GRAY_90)
d0.fillPath(True)
i0 = ai.Image(inFile0)

d0.save()
d0.scale(0.75, 0.75)
d0.rotate(0.234 * math.pi)
d0.addLocalRef(i0)
i0.thisown = False
d0.setSourceImage(i0, -0.5 * i0.getWidth(), -0.5 * i0.getHeight())
d0.fillPath(True)
d0.restore()

d0.setSourceColor(ai.Color.WHITE)
d0.stroke()

color0 = ai.Color(0., 0., 1., 0.6)
r0 = d0.getTextSize("Altjira draw test 01", "Liberation Sans bold", 40.)
d0.drawText(-0.5 * r0.width, -200, "Altjira draw test 01", 
    "Liberation Sans bold", 40., color0)

d0.finish()
c0.stop()

d0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("  Statistics:")
print("    Drawing time: " + str(c0.getElapsedTime()) + " secs")

print("All tests completed!")

