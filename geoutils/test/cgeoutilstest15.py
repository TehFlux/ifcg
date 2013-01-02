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
n0.setID('n0')

n1 = cg.Center.create()
n1.setMethod(cg.CENTER_BOUNDS)
n1.setID('n1')

n2 = cg.Normalize.create()
n2.setID('n2')

n3 = cg.Scale.create()
n3.setScale(cg.Vector3(300., -300., 1.))
n3.setID('n3')

n4 = cg.Rotate.create()
n4.setAngle(0.25 * math.pi)
n4.setID('n4')

n5 = cg.Clone.create()
n5.setNumClones(5)
n5.setID('n5')
#n5.enableDebugMode()

n6a = cg.Rotate.create()
n6a.setAngle(-0.75 * math.pi)
n6a.setID('n6a')

n6b = cg.Rotate.create()
n6b.setAngle(-0.25 * math.pi)
n6b.setID('n6b')

n6c = cg.Rotate.create()
n6c.setAngle(0.25 * math.pi)
n6c.setID('n6c')

n6d = cg.Rotate.create()
n6d.setAngle(0.75 * math.pi)
n6d.setID('n6d')

n7a = cg.Translate.create()
n7a.setOffset(cg.Vector3(300., -300., 0.))
n7a.setID('n7a')

n7b = cg.Translate.create()
n7b.setOffset(cg.Vector3(300., 300., 0.))
n7b.setID('n7b')

n7c = cg.Translate.create()
n7c.setOffset(cg.Vector3(-300., 300., 0.))
n7c.setID('n7c')

n7d = cg.Translate.create()
n7d.setOffset(cg.Vector3(-300., -300., 0.))
n7d.setID('n7d')

n7e = cg.Cache.create()
n7e.setID('n7e')

n8 = cg.Merge.create()
n8.setID('n8')
#n8.enableDebugMode()

n9 = cg.WriteSVG.create()
n9.setFileName('temp/nodes03.svg')
n9.setElementIDPrefix('tleaf')
n9.setAxis(cg.AXIS_Z)
n9.setShapeType(cg.SHAPE_TYPE_PATH)
n9.setID('n9')

nodes = [ n0, n1, n2, n3, n4, n5, n6a, n6b, n6c, n6d, 
    n7a, n7b, n7c, n7d, n7e, n8, n9 ]
v0 = cg.TransformNodeVector()
for it in nodes:
    v0.push_back(it)

print "  Creating graph..."
g0 = cg.TransformGraph()
g0.addNodes(v0)

print "    Creating connections..."
g0.chain(0, 5)
g0.connect(n5, n6a, 0)
g0.connect(n5, n6b, 1)
g0.connect(n5, n6c, 2)
g0.connect(n5, n6d, 3)
g0.connect(n6a, n7a)
g0.connect(n6b, n7b)
g0.connect(n6c, n7c)
g0.connect(n6d, n7d)
g0.connect(n7a, n8)
g0.connect(n7b, n8)
g0.connect(n7c, n8)
g0.connect(n7d, n8)
g0.connect(n5, n7e, 4)
g0.connect(n7e, n8)
g0.connect(n8, n9)

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
g0.update()

print "All done!"
