#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# ifgimpbrushtools.py          GIMP brush tools.
# ==========================================================================
# 
# This file is part of GeoUtils - Ionflux' Geometry Library.
# 
# GeoUtils - Ionflux' Geometry Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later version.
# 
# GeoUtils - Ionflux' Geometry Library is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GeoUtils - Ionflux' Geometry Library; if not, write to the 
# Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
# 02111-1307 USA
# 
# ==========================================================================
"""GIMP brush tools.

This module provides functions to help with the creation of GIMP brushes."""

import cairo, rsvg, os
import Altjira as ai

def renderSVG(svgData, width, height, pngFileName):
    """Render SVG data to a PNG file."""
    s0 = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx0 = cairo.Context(s0)
    ctx0.set_source_rgba(1., 1., 1., 1.)
    ctx0.rectangle(0, 0, width, height)
    ctx0.fill()
    h0 = rsvg.Handle(None, svgData)
    ctx0.save()
    h0.render_cairo(ctx0)
    ctx0.restore()
    s0.write_to_png(pngFileName)

def createBrushFrames(baseName, svgSheetFileName, pngSheetFileName, 
    frameDir, width, height, cellWidth, cellHeight, spacing):
    """Create brush frames from an SVG brush sheet."""
    #print "[createBrushFrames] DEBUG: Creating brush frames..."
    numCellsX = int(width / cellWidth)
    numCellsY = int(height / cellHeight)
    # Read data from the SVG brush sheet.
    f = open(svgSheetFileName, 'r')
    svg0 = f.read()
    f.close()
    # Render the svg file.
    #print "[createBrushFrames] DEBUG: Rendering SVG brush sheet..."
    renderSVG(svg0, width, height, pngSheetFileName)
    # Create Brush frames.
    #print "[createBrushFrames] DEBUG: Creating brush frames..."
    if (not os.path.exists(frameDir)):
        os.mkdir(frameDir)
    img0 = ai.Image(pngSheetFileName)
    r0 = ai.ImageRect()
    r0.width = int(cellWidth)
    r0.height = int(cellHeight)
    for i in xrange(0, numCellsX):
        for j in xrange(0, numCellsY):
            r0.x = int(i * cellWidth)
            r0.y = int(j * cellHeight)
            img1 = ai.Image(int(cellWidth), int(cellHeight))
            img1.fill(img0, r0)
            img1.writeToFile(frameDir + os.path.sep 
                + ("brf_%s_%04d.gbr" % (baseName, j * numCellsX + i)), 
                ai.Image.TYPE_GBR_GRAYSCALE, 
                "BrF_%s_%04d" % (baseName, j * numCellsY + i), spacing, 
                ai.DESATURATION_BY_VALUE)

def createGIH(baseName, frameDir, brushName, brushFileName, 
    width, height, cellWidth, cellHeight, placement, ranks):
    """Create GIMP GIH brush.
    
    This creates a one-dimensional GIMP GIH brush from the frames indicated 
    by the base name."""
    # Create GIH brush.
    #print "[createGIH] DEBUG: Creating GIH brush..."
    numCellsX = int(width / cellWidth)
    numCellsY = int(height / cellHeight)
    gih0 = (brushName + '\n' + str(numCellsX * numCellsY) + " "
        + "ncells:" + str(numCellsX * numCellsY) + " "
        + "cellwidth:" + str(int(cellWidth)) + " "
        + "cellheight:" + str(int(cellHeight)) + " "
        + "step:1 "
        + ("dim:%d " % len(ranks))
        + "cols:1 "
        + "rows:1 "
        + "placement:" + placement)
    for i in xrange(0, len(ranks)):
        r0 = ranks[i]
        gih0 += " rank%d:%d sel%d:%s" % (i, r0[1], i, r0[0])
    #print "[createGIH] DEBUG: Header:\n" + gih0
    gih0 += '\n'
    f0 = open(brushFileName, 'w')
    f0.write(gih0)
    for i in xrange(0, numCellsX * numCellsY):
        fn1 = frameDir + os.path.sep + ("brf_%s_%04d.gbr" % (baseName, i))
        f1 = open(fn1, 'r')
        f0.write(f1.read())
        f1.close()
    f0.close()

