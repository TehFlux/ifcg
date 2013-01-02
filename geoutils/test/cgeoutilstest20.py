#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import AltjiraGeoUtils as ag
import ifgimpbrushtools as gb

print "Testing transform graph..."

# General parameters and settings.

baseName = 'AScatter07'
brushName = 'T24 A Scatter 07'
spacing = 1
baseSize = 0.1
rows = 10
cols = rows
numCells = rows * cols
numClones = 20
width = 1000
height = 1000
paddingX = 0.05
paddingY = 0.05
ranks = [
    [ 'angular', numCells ]
]

cellWidth = width / cols
cellHeight = height / rows
sx = cellWidth * (1 - 2. * paddingX)
sy = cellHeight * (1 - 2. * paddingY)
svgSheetFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
    + baseName + ".svg")
pngSheetFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
    + baseName + ".png")
frameDir = ('temp' + os.path.sep + 'brushes' + os.path.sep + baseName)
brushFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
    + baseName + ".gih")

im.initRandom(16)

# Generate some SVG styles.

numColors = 10
colors = []
vMin = 0.
vMax = 0.6
dv = (vMax - vMin) / numColors
c1 = ai.FloatColor()
c1.c0 = 0.
c1.c1 = 0.
c1.c2 = vMin
c1.alpha = 1.
c1.space = ai.Color.SPACE_HSV
for i in xrange(0, numColors):
    c2 = ai.FloatColor()
    c2.c0 = c1.c0
    c2.c1 = c1.c1
    c2.c2 = c1.c2
    c2.alpha = c1.alpha
    c2.space = ai.Color.SPACE_HSV
    ai.toRGB(c2)
    c3 = ai.ByteColor()
    ai.floatToByte(c2, c3)
    cSpec = "#%02x%02x%02x" % (c3.c0, c3.c1, c3.c2)
    colors += [cSpec]
    c1.c2 += dv
styles = cg.SVGShapeStyleVector()
for c in colors:
    #print "  " + c
    styles.push_back(cg.getSVGShapeStyle(c, 1., "#000000", 1., 0.))

print "  Creating scatter LUT..."

# Create a LUT containing random translation vectors used for 
# scattering later.

m0t0 = im.RandomNorm.create()
m0t0.setStdDev(0.4)
m0t1 = im.Constant.create()
m0t1.setConstValue(0.)
m0 = cg.Compose3.create()
m0.setFuncX0(m0t0)
m0.setFuncX1(m0t0)
m0.setFuncX2(m0t1)
r0 = cg.Range(0., 0.5)
m1 = cg.AcceptLength3.create()
m1.setSource(m0)
m1.setLengthRange(r0)

lut0 = cg.Lookup3.create()
lut0.setSource(m1)
lut0.update(numClones)

for i in xrange(0, numClones):
    v0 = lut0(float(i) / (numClones - 1))
    print ("    %02d: " % i) + str(v0) + ", " + str(v0.norm())

print "  Creating nodes..."

# Part 1: Loading and transforming the source shape.

n0 = ag.LoadSVG.create()
n0.setFileName('test/images/shapes02.svg')
n0.addElementID('shape01')
n0.setID('n0')

n1 = cg.Center.create()
n1.setMethod(cg.CENTER_BOUNDS)
n1.setID('n1')

n2 = cg.Normalize.create()
n2.setID('n2')

n3 = cg.Scale.create()
n3.setScale(cg.Vector3(baseSize, -baseSize, 1.))
n3.setID('n3')

n4 = cg.Rotate.create()
n4.setAngle(0.25 * math.pi)
n4.setID('n4')

# Part 2: Cloning the source shape.

n5 = cg.Clone.create()
n5.setNumClones(numClones)
n5.setID('n5')

n6 = cg.Merge.create()
n6.setID('n6')

# Part 3: Scatter the clones.

n7 = cg.Translate.create()
n7.setIndexFunc(lut0)
n7.setID('n7')

# Part 4: Create radial and some random scaling.

m1t0 = im.Linear.create()
m1t0.setLower(1.0)
m1t0.setUpper(0.05)

m1 = cg.Compose3.create()
m1.setFuncX0(m1t0)
m1.setFuncX1(m1t0)
m1.setFuncX2(m1t0)

m2t0 = im.Random.create()

m2t1 = im.Linear.create()
m2t1.setFunc(m2t0)
m2t1.setLower(0.5)
m2t1.setUpper(1.0)

m2t2 = im.Lookup.create()
m2t2.setSource(m2t1)
m2t2.update(numClones)

m2 = cg.Compose3.create()
m2.setFuncX0(m2t2)
m2.setFuncX1(m2t2)
m2.setFuncX2(m2t2)

n8 = cg.Scale.create()
n8.setScale(cg.Vector3(1., 1., 1.))
n8.setCenteringMethod(cg.CENTER_BARYCENTER)
n8.setDistanceFunc(m1)
n8.setIndexFunc(m2)
n8.setID('n8')

# Part 5: Scale to cell size.

n9 = cg.Scale.create()
n9.setScale(cg.Vector3(sx, sy, 1.))
n9.setID('n9')

# Part 6: Wrap, clone and rotate the pattern.

n10 = cg.Wrap.create()
n10.setID('n10')

n11 = cg.Clone.create()
n11.setNumClones(numCells)
n11.setID('n11')

n12 = cg.Merge.create()
n12.setID('n12')

m3 = im.Linear.create()
m3.setLower(1.)
m3.setUpper(0.)

r0 = cg.Range(-2. * math.pi * (1. - 1. / numCells), 0)

n13 = cg.Rotate.create()
n13.setIndexFunc(m3)
n13.setIndexRange(r0)
n13.setID('n13')

# Part 7: Create the array.

n14 = cg.Array.create()
n14.setNumRows(rows)
n14.setNumColumns(cols)
n14.setCellWidth(width / cols)
n14.setCellHeight(height / rows)
n14.setID('n14')

# Part 8: Write the output file.

n15 = cg.WriteSVG.create()
n15.setFileName(svgSheetFileName)
n15.setElementIDPrefix('tshape')
n15.setAxis(cg.AXIS_Z)
n15.setShapeType(cg.SHAPE_TYPE_PATH)
n15.addStyles(styles)
n15.setID('n15')

nodes = [ n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, 
    n14, n15 ]
v0 = cg.TransformNodeVector()
for it in nodes:
    v0.push_back(it)

print "  Creating graph..."
g0 = cg.TransformGraph()
g0.addNodes(v0)

print "    Creating connections..."
g0.chain(0, 5)
for i in xrange(0, numClones):
    g0.connect(n5, n6, i)
g0.chain(6, 11)
for i in xrange(0, numCells):
    g0.connect(n11, n12, i)
g0.chain(12, 15)

print "    Setting I/O nodes..."
g0.setIO()

print "    " + str(g0)
print "    Nodes:"
for i in xrange(0, g0.getNumNodes()):
    print "      " + str(g0.getNode(i))
print "    Connections:"
for i in xrange(0, g0.getNumConnections()):
    print "      " + str(g0.getConnection(i))

print "    Updating graph..."
c0 = cg.Clock()
c0.start()
g0.update()
c0.stop()

print "  Creating GIH brush..."

c1 = cg.Clock()
c1.start()
gb.createBrushFrames(baseName, svgSheetFileName, pngSheetFileName, 
    frameDir, width, height, cellWidth, cellHeight, spacing)
c1.stop()
c2 = cg.Clock()
c2.start()
gb.createGIH(baseName, frameDir, brushName, brushFileName, 
    width, height, cellWidth, cellHeight, 'constant', ranks)
c2.stop()

print "  Statistics:"
for it in nodes:
    print ("    " + it.getID() + ".updateCounter = " 
        + str(it.getUpdateCounter()))
print "    Graph update time:           " + str(c0.getElapsedTime()) + " secs"
print "    Brush frame rendering time:  " + str(c1.getElapsedTime()) + " secs"
print "    GIH creation time:           " + str(c2.getElapsedTime()) + " secs"

print "All done!"
