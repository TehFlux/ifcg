#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2011 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiradrawtest04.py          Test script.
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
import IFMapping as im
import Altjira as ai
import AltjiraDraw as ad
import CGeoUtils as cg

outFile0 = 'temp' + os.path.sep + 'gradient03.png'
inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'sphere01.svg'

sourceSize = 1000
imageSize = 500
width = imageSize
height = imageSize
scale0 = 0.08

print("AltjiraDraw test 04")

d0 = ad.Drawable(width, height)
d0.fill(ai.Color.BLACK)

cb0 = ai.ColorBand.glow(ai.Color(0., 0., 1., 1.))
#print(str(cb0(0)) + ", " + str(cb0(1)))

f0 = im.InverseFalloff.create()
f0.setExponent(2.)
f1 = im.Rescale()
f1.setFunc(f0)
#print(str(f1(0)) + ", " + str(f1(1)))

g0 = ad.RadialGradient(0.5 * imageSize, 0.5 * imageSize, 
    scale0 * 0.5 * sourceSize, 
    0.5 * imageSize, 0.5 * imageSize, 0.5 * imageSize)
g0.setFromColorBand(cb0, f1, 20)
#print(str(g0))

print("  Testing gradients...")
c0 = cg.Clock()
c0.start()
d0.begin()

d0.save()
d0.arc(0.5 * imageSize, 0.5 * imageSize, 0.5 * imageSize)
d0.setSource(g0)
d0.fillPath()
d0.restore()

d0.save()
d0.scale(scale0, scale0)
# NOTE: Translation is relative to the transformed coordinate system within 
#       cairo, which makes matters a bit more complicated.
d0.translate(-0.5 * sourceSize + 250 / scale0, 
    -0.5 * sourceSize + 250 / scale0)
d0.drawSVGFile(inFile0, -250, -250)
d0.restore()

d0.finish()
c0.stop()

d0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("  Statistics:")
print("    Drawing time: " + str(c0.getElapsedTime()) + " secs")

print("All tests completed!")

