#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print "Testing transform nodes..."
print "  Creating nodes..."

n0 = ag.LoadSVG('test/images/leaf01.svg')
n0.addElementID('leaf01')
n0.setID('n0')
n1 = cg.Center(cg.CENTER_BOUNDS)
n1.setID('n1')
n2 = cg.Normalize()
n2.setID('n2')
n3 = cg.Scale(cg.Vector3(600., -600., 1.))
n3.setID('n3')
n4 = cg.WriteSVG('temp/nodes01.svg', 'tleaf', cg.AXIS_Z, 
    cg.SHAPE_TYPE_PATH)
n4.setID('n4')

print "    n0: " + str(n0)
print "    n1: " + str(n1)
print "    n2: " + str(n2)
print "    n3: " + str(n3)
print "    n4: " + str(n4)

print "  Connecting nodes..."
c0 = cg.Connection(n0, n1)
c1 = cg.Connection(n1, n2)
c2 = cg.Connection(n2, n3)
c3 = cg.Connection(n3, n4)

print "    c0: " + str(c0)
print "    c1: " + str(c1)
print "    c2: " + str(c2)
print "    c3: " + str(c3)

print "  Updating drain node..."
n4.update()

print "  Disconnecting nodes..."
c0.disconnect()
c1.disconnect()
c2.disconnect()
c3.disconnect()

print "    c0: " + str(c0)
print "    c1: " + str(c1)
print "    c2: " + str(c2)
print "    c3: " + str(c3)

print "All done!"
