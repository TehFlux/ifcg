#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print "Testing transform graph..."
print "  Creating nodes..."

n0 = ag.LoadSVG.create()
n0.setFileName('test/images/leaf01.svg')
n0.addElementID('leaf01')

n1 = cg.Center.create()
n1.setMethod(cg.CENTER_BOUNDS)

n2 = cg.Normalize.create()

n3 = cg.Scale.create()
n3.setScale(cg.Vector3(600., -600., 1.))

n4 = cg.Rotate.create()
n4.setAngle(0.25 * math.pi)

n5 = cg.WriteSVG.create()
n5.setFileName('temp/nodes02.svg')
n5.setElementIDPrefix('tleaf')
n5.setAxis(cg.AXIS_Z)
n5.setShapeType(cg.SHAPE_TYPE_PATH)

nodes = [ n0, n1, n2, n3, n4, n5 ]
v0 = cg.TransformNodeVector()
i = 0
for it in nodes:
    it.setID("n%02d" % i)
    v0.push_back(it)
    i += 1

print "  Creating graph..."
g0 = cg.TransformGraph()
g0.addNodes(v0)
g0.chain()
g0.setIO()
g0.update()

print "    " + str(g0)
print "    Nodes:"
for i in xrange(0, g0.getNumNodes()):
    print "      " + str(g0.getNode(i))
print "    Connections:"
for i in xrange(0, g0.getNumConnections()):
    print "      " + str(g0.getConnection(i))

print "All done!"
