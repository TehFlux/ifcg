#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiratest03.py          Test script.
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
"""Altjira image test 03."""

import time
import Altjira as ai

print "Testing color blender..."
print "  Color:"
c0 = ai.Color.WHITE
c1 = ai.Color.GREEN
print "    c0 = " + str(c0)
print "    c1 = " + str(c1)
b0 = ai.BlendSrcOver(c0, c1)
print "    b0 = " + str(b0)
r0 = ai.Color()
b0(r0)
print ("    white over black, 100% source opacity, 100% target opacity: " 
    + str(r0))
b0.setSourceOpacity(0.5)
b0(r0)
print ("    white over black, 50% source opacity, 100% target opacity: " 
    + str(r0))
b0.setTargetOpacity(0.5)
b0(r0)
print ("    white over black, 50% source opacity, 50% target opacity: " 
    + str(r0))
print "  ByteColor:"
bc0 = ai.ByteColor()
bc0.space = ai.Color.SPACE_RGB
c0.getByteColor(bc0)
bc1 = ai.ByteColor()
bc1.space = ai.Color.SPACE_RGB
c1.getByteColor(bc1)
print "    bc0 = " + ai.getString(bc0)
print "    bc1 = " + ai.getString(bc1)
b0 = ai.BlendSrcOver()
br0 = ai.ByteColor()
b0.blend(br0, bc0, bc1)
print ("    white over black, 100% source opacity, 100% target opacity: " 
    + ai.getString(br0))
b0.blend(br0, bc0, bc1, 128, 255)
print ("    white over black, 50% source opacity, 100% target opacity: " 
    + ai.getString(br0))
b0.blend(br0, bc0, bc1, 128, 128)
print ("    white over black, 50% source opacity, 50% target opacity: " 
    + ai.getString(br0))

print "All tests completed!"
