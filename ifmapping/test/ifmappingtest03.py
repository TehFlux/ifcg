#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# IFMapping - Ionflux Mapping Library
# Copyright © 2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# ifmappingtest03.py          Test script.
# ==========================================================================
# 
# This file is part of IFMapping - Ionflux Mapping Library.
# 
# IFMapping - Ionflux Mapping Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later version.
# 
# IFMapping - Ionflux Mapping Library is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with IFMapping - Ionflux Mapping Library; if not, write to the 
# Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
# 02111-1307 USA
# 
# ==========================================================================
"""IFMapping test 03."""

import math, os
import IFMapping as im
import IFObjectBase as io
import Altjira as ai
import CGeoUtils as cg

# Generate some SVG styles.
numColors = 8
colors = []
c1 = ai.FloatColor()
c1.c0 = 0.5
c1.c1 = 1.
c1.c2 = 1.
c1.alpha = 1.
c1.space = ai.Color.SPACE_HSV
dh = 1. / numColors
for i in range(0, numColors):
    c2 = ai.FloatColor()
    ai.copy(c1, c2)
    ai.toRGB(c2)
    c3 = ai.ByteColor()
    ai.floatToByte(c2, c3)
    cSpec = "#%02x%02x%02x" % (c3.c0, c3.c1, c3.c2)
    colors += [cSpec]
    c1.c0 += dh
    ai.clamp(c2)
styles0 = []
styles = cg.SVGShapeStyleVector()
for c in colors:
    #print("  " + c
    s0 = cg.getSVGShapeStyle("none", 1., c)
    styles0 += [s0]
    styles.push_back(s0)

redBoxStyle = cg.getSVGShapeStyle("#ff0000", 0.75, "#000000")

def createBox(polygons, xPos, yPos, size):
    """Create a box polygon."""
    ps0 = cg.Polygon3Set()
    p0 = ps0.addPolygon()
    v0 = p0.addVertex()
    v1 = p0.addVertex()
    v2 = p0.addVertex()
    v3 = p0.addVertex()
    s = 0.5 * size
    v0.setCoords(cg.Vector3(-s, -s, 0.))
    v1.setCoords(cg.Vector3(s, -s, 0.))
    v2.setCoords(cg.Vector3(s, s, 0.))
    v3.setCoords(cg.Vector3(-s, s, 0.))
    ps0.center(cg.CENTER_ORIGIN, cg.Vector3(xPos, yPos, 0.))
    ps0.applyTransform()
    polygons.addPolygons(ps0)

def sampleCurves(curves, styles, width = 1000, height = 1000, steps = 100):
    """Sample mappings and create SVG plots."""
    ps0 = cg.Polygon3Set()
    d = 1. / (steps - 1)
    for i in range(0, curves.getNumMappings()):
        c = curves.getMapping(i)
        p0 = ps0.addPolygon()
        t = 0.
        for i in range(0, steps):
            v0 = p0.addVertex()
            p = c(t)
            v0.setX(p.getX() - 0.5 * width)
            v0.setY(0.5 * height - p.getY())
            t += d
    svg0 = ps0.getSVG(styles, "curve", cg.AXIS_Z, cg.SHAPE_TYPE_PATH, False)
    return svg0

def markPointsOnCurves(curves, xv, style, width = 1000, height = 1000, 
    boxSize = 10.):
    """Create SVG markers for the specified X coordinates."""
    ps0 = cg.Polygon3Set()
    for i in range(0, curves.getNumMappings()):
        c = curves.getMapping(i)
        for x in xv:
            p0 = c.evalCoord(x)
            createBox(ps0, x - 0.5 * width, 0.5 * height - p0.getY(), boxSize)
    svg0 = ps0.getSVG(cg.getSVGPolygonStyle(style), "mroot", cg.AXIS_Z)
    return svg0

inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'curve01.svg'
inFile1 = 'test' + os.path.sep + 'images' + os.path.sep + 'spline01.svg'
inFile2 = 'test' + os.path.sep + 'images' + os.path.sep + 'splines02.svg'
outFile0 = 'temp' + os.path.sep + 'curves01.svg'

width = 1000
height = 1000

print("Loading curve data from file...")
ms0 = im.PointMappingSet()
d0 = im.getAttrValue(inFile0, 'path', 'curve01', 'd')
print("  d = " + str(d0))
ps0 = im.PointSet()
im.extractSVGControlPoints(d0, ps0)
d1 = "  points:"
for i in range(0, ps0.getNumPoints()):
    p = ps0.getPoint(i)
    d1 += (" " + str(p))
print(d1)
c0 = im.BezierCurve.create()
ms0.addMapping(c0)
c0.setControlPoints(ps0)
print("  " + str(c0))

print("Loading spline data from file...")
d0 = im.getAttrValue(inFile1, 'path', 'spline01', 'd')
print("  d = " + str(d0))
c1 = im.BezierSpline.create()
ms0.addMapping(c1)
c1.initFromSVG(d0)
print("  " + str(c1))

print("Loading animated spline data from file...")
v0 = io.StringVector()
for i in range(1, 4):
    v0.push_back('spline%02d' % i)
c2 = im.AnimatedSpline()
im.getSVGBezierSplineFrames(inFile2, v0, c2)
print("  c2 = " + str(c2))
c3 = im.BezierSpline.create()
c4 = im.BezierSpline.create()
c5 = im.BezierSpline.create()
c6 = im.BezierSpline.create()
ms0.addMapping(c3)
ms0.addMapping(c4)
ms0.addMapping(c5)
ms0.addMapping(c6)
c2.getShape(0.2, c3)
c2.getShape(0.4, c4)
c2.getShape(0.6, c5)
c2.getShape(0.8, c6)

print("Sampling curves...")
xv = [1., 250., 500., 750., 999.]
svg0 = sampleCurves(ms0, styles, width, height)
svg1 = markPointsOnCurves(ms0, xv, redBoxStyle)
svg2 = cg.getSVGImage(svg0 + svg1, width, height, int(0.5 * width), 
    int(0.5 * height))
f = open(outFile0, 'w')
f.write(svg2)
f.close()

print("All tests completed!")
