#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print "Testing transform graph..."

baseSize = 0.1
numClones = 100
width = 1000
height = 1000
paddingX = 0.05
paddingY = 0.05
sx = width * (1 - 2. * paddingX)
sy = height * (1 - 2. * paddingY)

im.initRandom(16)

# Generate some SVG styles.
numColors = 20
colors = []
vMin = 0.
vMax = 0.7
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

n0 = ag.LoadSVG.create()
n0.setFileName('test/images/leaf01.svg')
n0.addElementID('leaf01')
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

n5 = cg.Clone.create()
n5.setNumClones(numClones)
n5.setID('n5')

n6 = cg.Merge.create()
n6.setID('n6')

m0 = im.Random.create()
r1 = cg.Range(-2. * math.pi, 0)

n7 = cg.Rotate.create()
n7.setCenteringMethod(cg.CENTER_BARYCENTER)
n7.setIndexFunc(m0)
n7.setIndexRange(r1)
n7.setID('n7')

n8 = cg.Translate.create()
n8.setIndexFunc(lut0)
n8.setID('n8')

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

#for i in xrange(0, numClones):
#    v0 = m2t2(float(i) / (numClones - 1))
#    v1 = m2t2(float(i) / (numClones - 1))
#    print ("    %02d: " % i) + str(v0) + ", " + str(v1)

n9 = cg.Scale.create()
n9.setScale(cg.Vector3(1., 1., 1.))
n9.setCenteringMethod(cg.CENTER_BARYCENTER)
n9.setDistanceFunc(m1)
n9.setIndexFunc(m2)
n9.setID('n9')

n10 = cg.Scale.create()
n10.setScale(cg.Vector3(sx, sy, 1.))
n10.setID('n10')

n11 = cg.WriteSVG.create()
n11.setFileName('temp/nodes06.svg')
n11.setElementIDPrefix('tleaf')
n11.setAxis(cg.AXIS_Z)
n11.setShapeType(cg.SHAPE_TYPE_PATH)
n11.addStyles(styles)
n11.setID('n11')

nodes = [ n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11 ]
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

print "  Statistics:"
print "    Graph update time: " + str(c0.getElapsedTime()) + " secs"
for it in nodes:
    print ("    " + it.getID() + ".updateCounter = " 
        + str(it.getUpdateCounter()))

print "All done!"
