#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009-2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# altjiratest09.py          Test script.
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
"""Altjira test 09."""

import time, os, math
import Altjira as ai
import CGeoUtils as cg
import AltjiraGeoUtils as ag

inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'square01.svg'
elementID = 'square01'
outFile0 = 'temp/colorband01.png'
numColors = 100
cellWidth = 20
cellHeight = 20
paddingX = 0.0
paddingY = 0.0

numCols = int(math.ceil(math.sqrt(numColors)))
numRows = int(math.ceil(float(numColors) / numCols))
width = numCols * cellWidth
height = numRows * cellHeight
sx = cellWidth * (1. - 2 * paddingX) * math.sqrt(2.)
sy = cellHeight * (1. - 2 * paddingY) * math.sqrt(2.)

print("Creating color band...")

cb0 = ai.ColorBand.rainbow()
#cb0 = ai.ColorBand.flame()
#cb0 = ai.ColorBand.ice()
#cb0 = ai.ColorBand.terrain()
print("  number of color stops: " + str(cb0.getNumColorStops()))

print("Sampling color band...")

colors = ai.ColorObjVector()

t0 = time.time()
for i in range(0, numColors):
    c0 = ai.Color()
    cb0.eval(float(i) / (numColors - 1), c0)
    colors.push_back(c0)
    #print("  " + str(c0))
t1 = time.time()

print("Done (" + str(numColors) +" colors created in " 
    + str(t1 - t0) + " secs, " + str(float(numColors) / (t1 - t0)) 
    + " colors/s)")

# Create SVG styles.
print("Creating SVG styles...")
styles0 = []
styles = cg.SVGShapeStyleVector()
for i in range(0, numColors):
    c = colors[i]
    s0 = cg.getSVGShapeStyle(c.getHex(), c.getAlpha(), "#000000", 1., 0.)
    styles0 += [s0]
    styles.push_back(s0)

# Create nodes.
print("Creating nodes...")

# Step 0: Setup the base shape.

n0 = ag.LoadSVG.create()
n0.setFileName(inFile0)
n0.addElementID(elementID)

n1 = cg.Center.create()
n1.setMethod(cg.CENTER_BOUNDS)

n2 = cg.Normalize.create()

n3 = cg.Scale.create()
n3.setScale(cg.Vector3(sx, sy, 1.))

# Step 1: Create duplicates.

n4 = cg.Duplicate.create()
n4.setNumDuplicates(numColors)

# Step 2: Create the array.

n5 = cg.Array.create()
n5.setNumRows(numRows)
n5.setNumColumns(numCols)
n5.setCellWidth(cellWidth)
n5.setCellHeight(cellHeight)

# Step 3: Write the output file.

n6 = ag.WritePNG.create()
n6.setBackgroundColor(ai.Color.GRAY_60)
n6.setWidth(width)
n6.setHeight(height)
n6.setFileName(outFile0)
n6.setAxis(cg.AXIS_Z)
n6.addStyles(styles)

print("Creating graph...")

g0 = cg.TransformGraph()
# Add the color band so it gets cleaned up.
g0.addLocalRef(cb0)
g0.addNode(n0)
g0.addNode(n1)
g0.addNode(n2)
g0.addNode(n3)
g0.addNode(n4)
g0.addNode(n5)
g0.addNode(n6)
g0.chain()
g0.setIO()

print("Updating graph...")
c0 = cg.Clock()
c0.start()
g0.update()
c0.stop()

print("Statistics:")
print("  Graph update time: " + str(c0.getElapsedTime()) + " secs")

print("All tests completed!")

