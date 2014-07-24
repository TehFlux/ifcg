#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print "Testing Altjira/GeoUtils..."

baseName = 'Pattern02'
brushName = 'T30 Pattern 02'
spacing = 20
inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'shapes03.svg'
elementIDs = [ 'shape01' ]
baseSize = 0.65
# Number of shapes per pattern.
numDuplicates = 5
# Number of patterns per sequence.
numSeqPatterns = 100
# Number of sequences.
numSeqs = 1
# Scale range for distance based scaling.
scaleMin0 = 1.
scaleMax0 = 1.
# Scale range for offset.
scaleMin1 = 1.
scaleMax1 = 1.
# Scale range for elements.
scaleMin2 = 1.
scaleMax2 = 1.
rows = numSeqs
cols = numSeqPatterns
cellWidth = 100
cellHeight = 100
width = cellWidth * cols
height = cellHeight * rows
paddingX = 0.1
paddingY = 0.1
sx = 0.5 * cellWidth * (1. - 2. * paddingX)
sy = 0.5 * cellHeight * (1. - 2. * paddingY)

ranks = ai.GIHRankSpecVector()
rank0 = ai.createGIHRankSpec('angular', numSeqPatterns)
#rank1 = ai.createGIHRankSpec('angular', numSeqPatterns)
ranks.push_back(rank0)
#ranks.push_back(rank1)
placement = 'constant'
gbrType = ai.Image.TYPE_GBR_GRAYSCALE

pngSheetFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
    + baseName + ".png")
brushFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
    + baseName + ".gih")

im.initRandom(17134)

print "  Creating scatter LUT..."

lut0m0 = im.Linear.create()
lut0m0.setLower(-1.)
lut0m0.setUpper(1.)

lut0m1 = im.Constant.create()
lut0m1.setConstValue(0.)

lut0m2 = cg.Compose3.create()
lut0m2.setFuncs(lut0m1, lut0m0, lut0m1)

lut0 = cg.Lookup3.create()
lut0.setSource(lut0m2)
lut0.update(numDuplicates)

print "  Creating styles..."

colors = ai.ColorObjVector()
c0 = ai.createFloatColor(1., 0., 0., 1., ai.Color.SPACE_HSV)
#c1 = ai.createFloatColor(1., 0., 0.6, 1., ai.Color.SPACE_HSV)
#ai.createColors(colors, c0, c1, 1, 1, 1)
colors.push_back(ai.Color(c0))
numColors = colors.size()

styles = cg.SVGShapeStyleVector()
for i in xrange(0, numColors):
    c = colors[i]
    ch0 = c.getHex()
    #print ("    c%02d = " % i) + ch0
    styles.push_back(cg.getSVGShapeStyle(ch0, 1., "#000000", 1., 0.))

print "  Creating nodes..."

# Step 0: Load and transform the source shapes.

n0 = ag.LoadSVG.create()
n0.setFileName(inFile0)
for it in elementIDs:
    n0.addElementID(it)
n0.setID('n0')

n1 = cg.Center.create()
n1.setMethod(cg.CENTER_BOUNDS)
n1.setID('n1')

n2 = cg.Normalize.create()
n2.setID('n2')

n2a = cg.Rotate.create()
n2a.setAngle(math.pi)
n2a.setAxis(cg.AXIS_Z)
n2a.setID('n2a')

n3 = cg.Scale.create()
n3.setScale(cg.Vector3(baseSize, -baseSize, 1.))
n3.setID('n3')

print "    Creating graph: 'shape0'..."
nodes0 = [ n0, n1, n2, n2a, n3 ]
shape0 = cg.TransformGraph.create()
shape0.setID('shape0')
for it in nodes0:
    shape0.addNode(it)
shape0.chain()
shape0.setIO()

# Step 1: Create the pattern.

n4 = cg.Duplicate.create()
n4.setNumDuplicates(numDuplicates)
n4.setID('n4')

#n4am0 = im.Random.create()

#n4am1 = im.Lookup.create()
#n4am1.setSource(n4am0)
#n4am1.update(numDuplicates)

#r0 = cg.Range(0., 2. * math.pi)

#n4a = cg.Rotate.create()
#n4a.setIndexRange(r0)
#n4a.setIndexFunc(n4am1)
#n4a.setAxis(cg.AXIS_Z)
#n4a.setID('n4a')

n5m0 = im.Linear.create()
n5m0.setLower(scaleMax0)
n5m0.setUpper(scaleMin0)

n5m1 = cg.Compose3.create()
n5m1.setFuncsEqual(n5m0)

n5 = cg.Scatter.create()
n5.setOffsetFunc(lut0)
n5.setElementScaleDistanceFunc(n5m1)
n5.setOffsetIndexOffset(0.)
n5.setOffsetIndexScale(1.)
n5.setID('n5')

n5a = cg.Scale.create()
n5a.setScale(cg.Vector3(sx, sy, 1.))
n5a.setID('n5a')

n6 = cg.Wrap.create()
n6.setID('n6')

print "    Creating graph: 'pattern0'..."
nodes1 = [ n4, n5, n5a, n6 ]
pattern0 = cg.TransformGraph.create()
pattern0.setID('pattern0')
for it in nodes1:
    pattern0.addNode(it)
pattern0.chain()
pattern0.setIO()

# Step 2: Create pattern sequences using a batch node.

#pc0m0 = im.Linear.create()
#pc0m0.setLower(scaleMin1)
#pc0m0.setUpper(scaleMax1)

#pc0m0 = im.Piecewise.step(numSeqs, scaleMin1, scaleMax1)
#pc0m1 = im.Piecewise.step(numSeqs, scaleMin2, scaleMax2)

#pc0 = cg.ParamControl.create()
#pc0.setNode(n5)
#pc0.setParamID('offsetScaleFactor')
#pc0.setFunc(pc0m0)

#pc1 = cg.ParamControl.create()
#pc1.setNode(n5)
#pc1.setParamID('elementScaleFactor')
#pc1.setFunc(pc0m1)

n6a = cg.Batch.create()
n6a.setProcessor(pattern0)
#n6a.addControl(pc0)
#n6a.addControl(pc1)
n6a.setID('n6a')

n6b = cg.Merge.create()
n6b.setID('n6b')

n6cr0 = cg.Range(0., 2. * math.pi)
n6cm0 = im.Linear.create()
n6cm0.setLower(1.)
n6cm0.setUpper(0.)
#n6cm0 = im.Piecewise.sawtooth(numSeqs, 1., 0.)
n6cm0.setScale(float(numSeqs * numSeqPatterns - 1) 
    / (numSeqs * numSeqPatterns))

n6c = cg.Rotate.create()
n6c.setAxis(cg.AXIS_Z)
n6c.setAngle(-0.5 * math.pi)
n6c.setIndexRange(n6cr0)
n6c.setIndexFunc(n6cm0)

# Step 2: Create array and write to file.

n7 = cg.Array.create()
n7.setNumRows(rows)
n7.setNumColumns(cols)
n7.setCellWidth(cellWidth)
n7.setCellHeight(cellHeight)
n7.setID('n7')

img0 = ag.Image.create()
img0.createNewData(width, height)

n8 = ag.Render.create()
n8.setImage(img0)
n8.setAxis(cg.AXIS_Z)
n8.setBackgroundColor(ai.Color.WHITE)
n8.addStyles(styles)
n8.setID('8')

print "    Creating result graph..."

nodes2 = [ shape0, n6a, n6b, n6c, n7, n8 ]
g0 = cg.TransformGraph()
for it in nodes2:
    g0.addNode(it)
g0.connectFan(shape0, n6a, numSeqPatterns * numSeqs)
g0.connectRange(n6a, n6b, numSeqPatterns * numSeqs)
g0.chain(2, 5)
g0.setIO()

print "  Updating result graph..."
c0 = cg.Clock()
c0.start()
g0.update()
c0.stop()

print "  Creating GIH brush..."

c1 = cg.Clock()
c1.start()
img0.writeToFile(pngSheetFileName)
img0.writeGIH(brushFileName, cellWidth, cellHeight, ranks, placement, 
    gbrType, brushName, spacing)
c1.stop()

print "  Statistics:"
print "    Graph update time: " + str(c0.getElapsedTime()) + " secs"
print "    GIH creation time: " + str(c1.getElapsedTime()) + " secs"

print "All done!"
