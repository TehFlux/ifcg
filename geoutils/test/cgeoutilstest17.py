#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math
import IFMapping as im
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print "Testing transform graph..."
print "  Creating nodes..."

rows = 5
cols = rows
n = rows * cols
width = 1000
height = 1000
paddingX = 0.1
paddingY = 0.1
sx = width / cols * (1 - 2. * paddingX)
sy = height / rows * (1 - 2. * paddingY)

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
n3.setScale(cg.Vector3(sx, -sy, 1.))
n3.setID('n3')

n4 = cg.Rotate.create()
n4.setAngle(0.25 * math.pi)
n4.setID('n4')

n5 = cg.Clone.create()
n5.setNumClones(n)
n5.setID('n5')

n6 = cg.Merge.create()
n6.setID('n6')

m0 = im.Linear.create()
m0.setLower(1.)
m0.setUpper(0.)

r0 = cg.Range(-2. * math.pi * (1. - 1. / n), 0)

n7 = cg.Rotate.create()
n7.setIndexFunc(m0)
n7.setIndexRange(r0)
n7.setID('n7')

n8 = cg.Array.create()
n8.setNumRows(rows)
n8.setNumColumns(cols)
n8.setCellWidth(width / cols)
n8.setCellHeight(height / rows)
n8.setID('n8')

n9 = cg.WriteSVG.create()
n9.setFileName('temp/nodes05.svg')
n9.setElementIDPrefix('tleaf')
n9.setAxis(cg.AXIS_Z)
n9.setShapeType(cg.SHAPE_TYPE_PATH)
n9.setID('n9')

nodes = [ n0, n1, n2, n3, n4, n5, n6, n7, n8, n9 ]
v0 = cg.TransformNodeVector()
for it in nodes:
    v0.push_back(it)

print "  Creating graph..."
g0 = cg.TransformGraph()
g0.addNodes(v0)

print "    Creating connections..."
g0.chain(0, 5)
for i in xrange(0, n):
    g0.connect(n5, n6, i)
g0.chain(6, 9)

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
