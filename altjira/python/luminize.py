#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# luminize.py          Composite luminance channel.
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

import time, sys
import Altjira as ai

if (len(sys.argv) < 4):
    print("Usage: luminize.py <infile> <lumfile> <outfile> [<amount>]")
    sys.exit(0)

inFile = sys.argv[1]
lumFile = sys.argv[2]
outFile = sys.argv[3]
if (len(sys.argv) > 4):
    amount = float(sys.argv[4])
else:
    amount = 1.

# Luminance blender.
bl0 = ai.BlendChannel()
bl0.setSrcChannel(ai.CH_LUMINANCE)
bl0.setDestChannel(ai.CH_LUMINANCE)
bl0.setSourceOpacity(amount)
bl0.setTargetOpacity(1. - amount)

# Saturation blender.
# Used so we get a valid saturation for high luminance areas.
bl1 = ai.BlendChannel()
bl1.setSrcChannel(ai.CH_SATURATION)
bl1.setDestChannel(ai.CH_SATURATION)
bl1.setSrcSpace(ai.Color.SPACE_HSV)
bl1.setDestSpace(ai.Color.SPACE_HSL)
bl1.setSourceOpacity(amount)
bl1.setTargetOpacity(1. - amount)

src = ai.Image(inFile)
sat = ai.Image(src)
lum = ai.Image(lumFile)
width = src.getWidth()
height = src.getHeight()

t0 = time.time()
src.composite(lum, bl0)
src.composite(sat, bl1)
t1 = time.time()
src.writeToFile(outFile, ai.Image.TYPE_PNG)

print("Luminized '" + inFile + "' using '" + lumFile 
    + "' as the source to '" + outFile + "' (amount = " + str(amount) 
    + ", " + str(width) + "x" + str(height) + " pixels filled in " 
    + str(t1 - t0) + " secs, " + str(width * height / (t1 - t0)) 
    + " px/s).")

