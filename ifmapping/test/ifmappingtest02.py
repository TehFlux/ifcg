#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# IFMapping - Ionflux Mapping Library
# Copyright © 2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# ifmappingtest02.py          Test script.
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
"""IFMapping test 02."""

import math, os
import IFMapping as im
import IFObjectBase as io
import Altjira as ai
import CGeoUtils as cg

# Generate some SVG styles.
numColors = 15
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

def findRoots(mapping, rootFinder, xMin = 0., xMax = 1.):
    """Find roots within the specified interval."""
    rootFinder.setFunc(mapping)
    rv0 = im.RangeVector()
    rootFinder.findStartIntervals(rv0)
    result = []
    roots = set()
    for i in range(0, rv0.size()):
        r0 = rv0[i]
        print("      Finding root for interval [" + str(r0.lower) + ", " 
            + str(r0.upper) + "]...")
        try:
            x0 = rootFinder(r0.lower, r0.upper)
            if (not x0 in roots):
                result += [mapping.sample(x0)]
                roots.add(x0)
        except (RuntimeError, e):
            print("      WARNING: Could not find root for " 
                + str(mapping) + ": " + str(e))
    return result

def findRootsSVG(mappings, rootFinder, style, width = 1000, height = 1000, 
    xMin = 0., xMax = 1., yMin = -0.5, yMax = 0.5, boxSize = 10.):
    """Find roots for the specified mappings and create SVG markers."""
    ps0 = cg.Polygon3Set()
    for i in range(0, mappings.getNumMappings()):
        m = mappings.getMapping(i)
        print("    Finding roots for mapping " + str(m) + "...")
        samples = findRoots(m, rootFinder, xMin, xMax)
        if (len(samples) == 0):
            print("      ?? No roots found.")
        else:
            for s in samples:
                print("        -> " + str(s.x) + ", " + str(s.y))
                bx = width * (s.x - 0.5)
                by = height * ((s.y - yMin) / (yMax - yMin) - 0.5)
                createBox(ps0, bx, by, boxSize)
    svg0 = ps0.getSVG(cg.getSVGPolygonStyle(style), "mroot", cg.AXIS_Z)
    return svg0

def sampleMappings(mappings, styles, width = 1000, height = 1000, 
    steps = 100, yMin = -0.5, yMax = 0.5):
    """Sample mappings and create SVG plots."""
    ps0 = cg.Polygon3Set()
    d = 1. / (steps - 1)
    for i in range(0, mappings.getNumMappings()):
        m = mappings.getMapping(i)
        p0 = ps0.addPolygon()
        x = 0.
        for i in range(0, steps):
            v0 = p0.addVertex()
            v0.setX(width * (x - 0.5))
            v0.setY(height * ((m(x) - yMin) / (yMax - yMin) - 0.5))
            x += d
    svg0 = ps0.getSVG(styles, "mapping", cg.AXIS_Z, cg.SHAPE_TYPE_PATH, False)
    return svg0

def testRootFinder(rootFinder, mappings, outFile, boxStyle, svg0 = "", 
    width = 1000, height = 1000):
    """Test a root finder."""
    print("  Looking for roots (with " + str(rootFinder) + ")...")
    svg1 = findRootsSVG(mappings, rootFinder, boxStyle, width, height)
    svg2 = cg.getSVGImage(svg0 + svg1, width, height, int(0.5 * width), 
        int(0.5 * height))
    f = open(outFile, 'w')
    f.write(svg2)
    f.close()

print("Creating mappings...")
ms0 = im.MappingSet()
print("  Constant...")
m1 = im.Constant.create()
m1.setConstValue(0.5005)
print("  Linear...")
m0 = im.Linear.create()
print("  Cubic...")
m2 = im.Cubic.create()
print("  Inverse falloff (rescaled)...")
m3t = im.InverseFalloff.create()
m3t.setExponent(2.)
m3 = im.Rescale.create()
m3.setFunc(m3t)
print("  Power...")
m4 = im.Power.create()
m4.setExponent(2)
print("  Exp (rescaled)...")
m5t = im.Exp.create()
m5 = im.Rescale.create()
m5.setFunc(m5t)
print("  Polynomial (rescaled)...")
v0 = io.DoubleVector()
v0.push_back(0.)
v0.push_back(0.)
v0.push_back(-1.)
v0.push_back(.05)
m6t = im.Polynomial.create()
m6t.addCoefficients(v0)
m6t.setScale(40)
m6t.setOffset(-13.5)
#print("    m6t.getNumCoefficients = " + str(m6t.getNumCoefficients())
v1 = io.DoubleVector()
for i in range(0, 101):
    v1.push_back(float(i) / 100.)
m6 = im.Rescale.create()
m6.addArgs(v1)
m6.setFunc(m6t)
print("  Chain, Multiply, LinearCombination (rescaled)...")
m7t0 = im.Constant.create()
m7t0.setConstValue(1.)
m7t1 = im.Power.create()
m7t1.setExponent(1)
p0 = im.Piece.create()
p0.setMapping(m7t0)
p0.setParam(-3.)
p1 = im.Piece.create()
p1.setMapping(m7t1)
p1.setParam(6.)
m7t2 = im.LinearCombination.create()
m7t2.addPiece(p0)
m7t2.addPiece(p1)
m7t3 = im.Power.create()
m7t3.setExponent(2)
m7t3.setFunc(m7t2)
m7t4 = im.Constant.create()
m7t4.setConstValue(-1.)
m7t5 = im.Multiply.create()
m7t5.addFunc(m7t3)
m7t5.addFunc(m7t4)
m7t6 = im.Exp.create()
m7t6.setFunc(m7t5)
m7 = im.Rescale.create()
m7.addArgs(v1)
m7.setFunc(m7t6)
print("  Sin (rescaled)...")
m8t = im.Sin.create()
m8t.setScale(2. * math.pi)
m8 = im.Rescale.create()
m8.addArgs(v1)
m8.setFunc(m8t)
print("  Cos (rescaled)...")
m9t = im.Cos.create()
m9t.setScale(2. * math.pi)
m9 = im.Rescale.create()
m9.addArgs(v1)
m9.setFunc(m9t)
print("  Tan (rescaled)...")
m10t = im.Tan.create()
m10t.setScale(0.8 * math.pi)
m10t.setOffset(-0.4 * math.pi)
m10 = im.Rescale.create()
m10.addArgs(v1)
m10.setFunc(m10t)
print("  ArcSin (rescaled)...")
m11t = im.ArcSin.create()
m11t.setScale(2.)
m11t.setOffset(-1.)
m11 = im.Rescale.create()
m11.addArgs(v1)
m11.setFunc(m11t)
print("  ArcCos (rescaled)...")
m12t = im.ArcCos.create()
m12t.setScale(2.)
m12t.setOffset(-1.)
m12 = im.Rescale.create()
m12.addArgs(v1)
m12.setFunc(m12t)
print("  ArcTan (rescaled)...")
m13t = im.ArcTan.create()
m13t.setScale(20.)
m13t.setOffset(-10.)
m13 = im.Rescale.create()
m13.addArgs(v1)
m13.setFunc(m13t)

mappings = [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13]

print("Rescaling mapping values...")
for m in mappings:
    l0 = im.Linear.create()
    l0.setLower(-0.5)
    l0.setUpper(0.5)
    l0.setFunc(m)
    ms0.addMapping(l0)

width = 1000
height = 1000
svg0 = sampleMappings(ms0, styles, width, height)

print("Testing root finders...")
rf0 = im.BisectionRootFinder()
rf1 = im.SecantRootFinder()
rf2 = im.DekkerRootFinder()
rf3 = im.BrentLinearRootFinder()

testRootFinder(rf0, ms0, 'temp' + os.path.sep + 'rootfinder01.svg', 
    redBoxStyle, svg0, width, height)
testRootFinder(rf1, ms0, 'temp' + os.path.sep + 'rootfinder02.svg', 
    redBoxStyle, svg0, width, height)
testRootFinder(rf2, ms0, 'temp' + os.path.sep + 'rootfinder03.svg', 
    redBoxStyle, svg0, width, height)
testRootFinder(rf3, ms0, 'temp' + os.path.sep + 'rootfinder04.svg', 
    redBoxStyle, svg0, width, height)

print("All tests completed!")

