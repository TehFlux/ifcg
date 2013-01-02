#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print "Testing Altjira/GeoUtils..."

# General parameters and settings.

baseName = 'AScatter10'
brushName = 'T27 A Scatter 10'
spacing = 1
baseSize = 0.15
# Base shape scaling range.
scaleMin = 0.333
scaleMax = 1.0
# Pattern scaling range.
scaleMin2 = 0.8
scaleMax2 = 1.0
# The number of clones of the base shape for the pattern.
numClones = 30
# Number of scaling steps.
scaleSteps = 10
# Number of rotation steps.
rotateSteps = 100
rows = scaleSteps
cols = rotateSteps
numCells = rows * cols
cellWidth = 100
cellHeight = 100
width = cols * cellWidth
height = rows * cellHeight
paddingX = 0.05
paddingY = 0.05

ranks = ai.GIHRankSpecVector()
rank0 = ai.createGIHRankSpec('pressure', scaleSteps)
rank1 = ai.createGIHRankSpec('angular', rotateSteps)
ranks.push_back(rank0)
ranks.push_back(rank1)
placement = 'constant'
gbrType = ai.Image.TYPE_GBR_GRAYSCALE

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

nodes0 = [ n0, n1, n2, n3 ]
v0 = cg.TransformNodeVector()
for it in nodes0:
    v0.push_back(it)

print "  Creating graph: 'shape0'..."
shape0 = cg.TransformGraph.create()
shape0.setID('shape0')
shape0.addNodes(v0)
shape0.chain()
shape0.setIO()

# Part 2: Create scaled duplicates.

n4 = cg.Duplicate.create()
n4.setNumDuplicates(scaleSteps)
n4.setID('n4')

m2t0 = im.Linear.create()
m2t0.setLower(scaleMin)
m2t0.setUpper(scaleMax)

m2 = cg.Compose3.create()
m2.setFuncX0(m2t0)
m2.setFuncX1(m2t0)
m2.setFuncX2(m2t0)

n5 = cg.Scale.create()
n5.setScale(cg.Vector3(1., 1., 1.))
n5.setCenteringMethod(cg.CENTER_BARYCENTER)
n5.setIndexFunc(m2)
n5.setID('n5')

n6 = cg.Explode.create()
n6.setID('n6')

nodes1 = [ n4, n5, n6 ]
v1 = cg.TransformNodeVector()
for it in nodes1:
    v1.push_back(it)

print "  Creating graph: 'scale0'..."
scale0 = cg.TransformGraph.create()
scale0.setID('scale0')
scale0.addNodes(v1)
scale0.chain()
scale0.setIO()

# Part 3: Creating the pattern.
# Part 3a: Duplicate the source shape.

n7 = cg.Duplicate.create()
n7.setNumDuplicates(numClones)
n7.setID('n7')

# Part 3b: Scatter the duplicates.

n8 = cg.Translate.create()
n8.setIndexFunc(lut0)
n8.setID('n8')

# Part 3c: Create radial and some random scaling.

m3t0 = im.Linear.create()
m3t0.setLower(1.0)
m3t0.setUpper(0.05)

m3 = cg.Compose3.create()
m3.setFuncX0(m3t0)
m3.setFuncX1(m3t0)
m3.setFuncX2(m3t0)

m4t0 = im.Random.create()

m4t1 = im.Linear.create()
m4t1.setFunc(m4t0)
m4t1.setLower(0.5)
m4t1.setUpper(1.0)

m4t2 = im.Lookup.create()
m4t2.setSource(m4t1)
m4t2.update(numClones)

m4 = cg.Compose3.create()
m4.setFuncX0(m4t2)
m4.setFuncX1(m4t2)
m4.setFuncX2(m4t2)

n9 = cg.Scale.create()
n9.setScale(cg.Vector3(1., 1., 1.))
n9.setCenteringMethod(cg.CENTER_BARYCENTER)
n9.setDistanceFunc(m3)
n9.setIndexFunc(m4)
n9.setID('n9')

# Part 3d: Scale to cell size.

n10 = cg.Scale.create()
n10.setScale(cg.Vector3(sx, sy, 1.))
n10.setID('n10')
#n10.enableDebugMode()

# Create a transform graph for creating the pattern.

nodes2 = [ n7, n8, n9, n10 ]
v2 = cg.TransformNodeVector()
for it in nodes2:
    v2.push_back(it)

print "  Creating graph: 'pattern0'..."
pattern0 = cg.TransformGraph.create()
pattern0.setID('pattern0')
pattern0.addNodes(v2)
pattern0.chain()
pattern0.setIO()

# Part 4: Wrap, clone and rotate the pattern.

n11 = cg.Wrap.create()
n11.setID('n11')

n12 = cg.Duplicate.create()
n12.setNumDuplicates(rotateSteps)
n12.setID('n12')

m5 = im.Linear.create()
m5.setLower(1.)
m5.setUpper(0.)

r0 = cg.Range(-2. * math.pi * (1. - 1. / rotateSteps), 0)

n13 = cg.Rotate.create()
n13.setIndexFunc(m5)
n13.setIndexRange(r0)
n13.setID('n13')

nodes3 = [ n11, n12, n13 ]
v3 = cg.TransformNodeVector()
for it in nodes3:
    v3.push_back(it)

print "  Creating graph: 'rotate0'..."
rotate0 = cg.TransformGraph.create()
rotate0.setID('rotate0')
rotate0.addNodes(v3)
rotate0.chain()
rotate0.setIO()

# Part 5: Batch process the scaled duplicates to create rotated patterns.

n13a = cg.Wrap.create()
n13a.setID('n13a')

nodes4 = [ pattern0, rotate0, n13a ]
v4 = cg.TransformNodeVector()
for it in nodes4:
    v4.push_back(it)

print "  Creating graph: 'batch0'..."
batch0 = cg.TransformGraph.create()
batch0.setID('batch0')
batch0.addNodes(v4)
batch0.chain()
batch0.setIO()

n14 = cg.Batch.create()
n14.setProcessor(batch0)
n14.setID('n14')
#n14.enableDebugMode()

n15 = cg.Merge.create()
n15.setID('n15')
#n15.enableDebugMode()

# Part 6: Add some additional (pattern) scaling to each of the (base shape) 
#         scale steps.
m6t0 = im.Linear.create()
m6t0.setLower(scaleMin2)
m6t0.setUpper(scaleMax2)

m6 = cg.Compose3.create()
m6.setFuncX0(m6t0)
m6.setFuncX1(m6t0)
m6.setFuncX2(m6t0)

n15a = cg.Scale.create()
n15a.setScale(cg.Vector3(1., 1., 1.))
n15a.setCenteringMethod(cg.CENTER_BOUNDS)
n15a.setIndexFunc(m6)
n15a.setID('n15a')
#n15a.enableDebugMode()

n15b0 = cg.Explode.create()
n15b0.setID('n15b0')
#n15b0.enableDebugMode()

n15b1 = cg.Unwrap.create()
n15b1.setID('n15b1')

n15b2 = cg.Explode.create()
n15b2.setID('n15b2')

nodes4a = [ n15b1, n15b2 ]
v4a = cg.TransformNodeVector()
for it in nodes4a:
    v4a.push_back(it)

print "  Creating graph: 'batch1'..."
batch1 = cg.TransformGraph.create()
batch1.setID('batch1')
batch1.addNodes(v4a)
batch1.chain()
batch1.setIO()

n15c = cg.Batch.create()
n15c.setProcessor(batch1)
n15c.setID('n15c')
#n15c.enableDebugMode()

n15d = cg.Merge.create()
n15d.setID('n15d')

nodes4b = [ n15a, n15b0, batch1, n15c, n15d ]
v4b = cg.TransformNodeVector()
for it in nodes4b:
    v4b.push_back(it)

print "  Creating graph: 'batch1'..."
batch2 = cg.TransformGraph.create()
batch2.setID('batch2')
batch2.addNodes(v4b)
# The scale node outputs one group containing the scaleSteps> rotation 
# groups as elements.
batch2.connect(n15a, n15b0)
# Connect the <scaleSteps> rotation groupd created by the explode node 
# to the batch node.
batch2.connectRange(n15b0, n15c, scaleSteps)
# The batch node explodes each of the rotation groups to yield the 
# collection of transformed patterns, which are then merged for further 
# processing.
batch2.connectRange(n15c, n15d, scaleSteps * rotateSteps)
batch2.setIO()

# Part 7: Create the array.

n16 = cg.Array.create()
n16.setNumRows(rows)
n16.setNumColumns(cols)
n16.setCellWidth(cellWidth)
n16.setCellHeight(cellHeight)
n16.setID('n16')
#n16.enableDebugMode()

# Part 7: Render to an image.

img0 = ag.Image.create()
img0.createNewData(width, height)

n17 = ag.Render.create()
n17.setImage(img0)
n17.setAxis(cg.AXIS_Z)
n17.setBackgroundColor(ai.Color.WHITE)
n17.addStyles(styles)
n17.setID('n17')

nodes5 = [ shape0, scale0, batch0, batch2, n14, n15, batch1, n16 ]
v5 = cg.TransformNodeVector()
for it in nodes5:
    v5.push_back(it)

print "  Creating result graph..."
g0 = cg.TransformGraph()
g0.addNodes(v5)
g0.addNode(n17)
# Prepare the scaled base shapes.
g0.connect(shape0, scale0)
# Batch process the <scaleSteps> scaled base shapes to create rotated 
# patterns.
g0.connectRange(scale0, n14, scaleSteps)
# Merge <scaleSteps> rotated patterns from the batch processing into 
# one group.
g0.connectRange(n14, n15, scaleSteps)
# Scale the elements of each rotation group, then explode the groups with 
# another batch processing node.
g0.connect(n15, batch2)
# Pass the merged result into the array node.
g0.connect(batch2, n16)
g0.connect(n16, n17)
g0.setIO()

#print "    " + str(g0)
#print "    Nodes:"
#for i in xrange(0, g0.getNumNodes()):
#    print "      " + str(g0.getNode(i))
#print "    Connections:"
#for i in xrange(0, g0.getNumConnections()):
#    print "      " + str(g0.getConnection(i))

print "  Updating result graph..."
c0 = cg.Clock()
c0.start()
g0.update()
c0.stop()

print "  Creating GIH brush..."

c1 = cg.Clock()
c1.start()
img0.writeGIH(brushFileName, cellWidth, cellHeight, ranks, placement, 
    gbrType, brushName, spacing)

#gb.createBrushFrames(baseName, svgSheetFileName, pngSheetFileName, 
#    frameDir, width, height, cellWidth, cellHeight, spacing)

c1.stop()

#c2 = cg.Clock()
#c2.start()
#gb.createGIH(baseName, frameDir, brushName, brushFileName, 
#    width, height, cellWidth, cellHeight, 'constant', ranks)
#c2.stop()

print "  Statistics:"
for it in (nodes0 + nodes1 + nodes2 + nodes3 + nodes4 + nodes5):
    print ("    " + it.getID() + ".updateCounter = " 
        + str(it.getUpdateCounter()))
print "    Graph update time:           " + str(c0.getElapsedTime()) + " secs"
#print "    Brush frame rendering time:  " + str(c1.getElapsedTime()) + " secs"
print "    GIH creation time:           " + str(c1.getElapsedTime()) + " secs"

print "All done!"
