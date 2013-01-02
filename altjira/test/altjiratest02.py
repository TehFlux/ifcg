#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiratest02.py          Test script.
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
"""Altjira image test 02."""

import Altjira as ai

inFile = 'test/images/arrow01.png'

print "Creating GIMP brush from file '" + inFile + "'..."
i0 = ai.Image(inFile)
print "  numChannels = " + str(i0.getNumChannels())
p0 = ai.ByteColor()
p0.space = ai.Color.SPACE_HSV
i0.getPixel(0, 0, p0)
print "  p0 = " + str(p0.c0) + ", " + str(p0.c1) + ", " + str(p0.c2)
#print str(p0)
i0.writeToFile('temp/arrow01.gbr', ai.Image.TYPE_GBR_GRAYSCALE, 
    'GIMP Brush', 10, ai.DESATURATION_BY_VALUE)
i0.writeToFile('temp/arrow01.png', ai.Image.TYPE_PNG)

print "All tests completed!"
