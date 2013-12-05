#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""GeoUtils test script."""
import os
import IFObjectBase as ib
import IFMapping as im
import CGeoUtils as cg
import Altjira as ai
import geoutils as gu

testName = "XML I/O 03"

# memory management
mm = ib.IFObject()

print("GeoUtils test script: " + testName)

# Get XML factories to initialize the hierarchy.
xf0 = cg.Vector.getXMLFactory()
xf1 = cg.Vector2.getXMLFactory()
xf2 = cg.Vector3.getXMLFactory()
xf3 = cg.Vector4.getXMLFactory()
xf4 = cg.VectorSetXMLFactory.upcast(cg.VectorSet.getXMLFactory())

vs0 = cg.VectorSet.create()
vs0.setID("vs0")
vs0.addVector(cg.Vector2.create(1., 3.))
vs0.addVector(cg.Vector3.create(2., -1., 4.))
vs0.addVector(cg.Vector4.create(-5., -3., 7., -1.))

print("  Vector set (%s):" % vs0.getID())
for i in range(0, vs0.getNumVectors()):
    v0 = vs0.getVector(i)
    print("    %s" % (v0.getString()))

xml0 = vs0.getXML0(2)

print("  XML:")

print(xml0)

vs1 = cg.VectorSet()
mm.addLocalRef(vs1)
xf4.initObject(xml0, vs1)

print("  Vector set (from XML):")
print("    name = '%s'" % vs1.getID())
for i in range(0, vs0.getNumVectors()):
    v0 = vs1.getVector(i)
    print("    %s" % (v0.getString()))

print("All done!")
