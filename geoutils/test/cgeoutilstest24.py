#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Testing GeoUtils...")

inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'shapes02.svg'
outFile0 = 'temp' + os.path.sep + 'scatter03.svg'
elementID = 'shape01'
stdDev = 0.6
baseSize = 0.2
numDuplicates = 36
# Scale range for distance based scaling.
scaleMin0 = 0.5
scaleMax0 = 1.
offsetScaleFactor = 0.9
width = 1000
height = 1000
paddingX = 0.01
paddingY = 0.01
sx = 0.5 * width * (1. - 2. * paddingX)
sy = 0.5 * height * (1. - 2. * paddingY)
numCircles = 4
centeringMethod = cg.CENTER_BOUNDS

im.initRandom(17148)

print("  Creating scatter LUT...")

# Create a pattern of concentric circles.
vecs0 = []
vecs1 = cg.Vector3Vector()
dupsPerCircle = int(numDuplicates / numCircles)
for i in range(0, numCircles):
    r = (1. / numCircles) * (i + 1)
    phi = 0.
    dPhi = 2. * math.pi / dupsPerCircle
    for i in range(0, dupsPerCircle):
        v0 = cg.Vector3(r * math.sin(phi), r * math.cos(phi), 0.)
        vecs0 += [v0]
        vecs1.push_back(v0)
        phi += dPhi

lut0 = cg.Lookup3.create()
lut0.addEntries(vecs1, numDuplicates)
vecs1.clear()
vecs0 = None

#lut0 = cg.Scatter.createLUT(numDuplicates, 
#    cg.Vector3(stdDev, stdDev, stdDev), cg.Vector3.ZERO, sphere0)

print("  Creating styles...")

colors = ai.ColorObjVector()
c0 = ai.createFloatColor(1., 0., 0., 1., ai.Color.SPACE_HSV)
c1 = ai.createFloatColor(1., 0., 0.6, 1., ai.Color.SPACE_HSV)
ai.createColors(colors, c0, c1, 1, 1, 10)
numColors = colors.size()

styles0 = []
styles = cg.SVGShapeStyleVector()
for i in range(0, numColors):
    c = colors[i]
    ch0 = c.getHex()
    print(("    c%02d = " % i) + ch0)
    s0 = cg.getSVGShapeStyle(ch0[:7], 1., "#000000", 1., 0.)
    styles0 += [s0]
    styles.push_back(s0)

print("  Creating nodes...")

# Step 0: Load and transform the source shape.

n0 = ag.LoadSVG.create()
n0.setFileName(inFile0)
n0.addElementID(elementID)
n0.setID('n0')

n1 = cg.Center.create()
n1.setMethod(centeringMethod)
n1.setID('n1')

n2 = cg.Normalize.create()
n2.setID('n2')

n3 = cg.Scale.create()
n3.setScale(cg.Vector3(baseSize, -baseSize, 1.))
n3.setID('n3')

print("    Creating graph: 'shape0'...")
nodes0 = [ n0, n1, n2, n3 ]
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

n5m0 = im.Linear.create()
n5m0.setLower(scaleMax0)
n5m0.setUpper(scaleMin0)

n5m1 = cg.Compose3.create()
n5m1.setFuncsEqual(n5m0)

n5 = cg.Scatter.create()
n5.setOffsetFunc(lut0)
n5.setOffsetScaleFactor(offsetScaleFactor)
n5.setElementScaleDistanceFunc(n5m1)
n5.setCenteringMethod(centeringMethod)
n5.setID('n5')

n6 = cg.Wrap.create()
n6.setID('n6')

print("    Creating graph: 'pattern0'...")
nodes1 = [ n4, n5, n6 ]
pattern0 = cg.TransformGraph.create()
pattern0.setID('pattern0')
for it in nodes1:
    pattern0.addNode(it)
pattern0.chain()
pattern0.setIO()

# Step 2: Scale to target size and write to file.

n7 = cg.Scale.create()
n7.setScale(cg.Vector3(sx, sy, 1.))
#n7.setCenteringMethod(centeringMethod)
n7.setID('n7')

n8 = cg.WriteSVG.create()
n8.setWidth(width)
n8.setHeight(height)
n8.setFileName(outFile0)
n8.setAxis(cg.AXIS_Z)
n8.addStyles(styles)
n8.setID('n8')

print("    Creating result graph...")

nodes2 = [ shape0, pattern0, n7, n8 ]
g0 = cg.TransformGraph()
for it in nodes2:
    g0.addNode(it)
g0.chain()
g0.setIO()

print("  Updating result graph...")
c0 = cg.Clock()
c0.start()
g0.update()
c0.stop()

print("  Statistics:")
print("    Graph update time: " + str(c0.getElapsedTime()) + " secs")

print("All done!")
