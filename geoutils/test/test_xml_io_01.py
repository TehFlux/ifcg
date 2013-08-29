#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""GeoUtils test script."""
import os
import IFObjectBase as ib
import IFMapping as im
import CGeoUtils as cg
import Altjira as ai
import geoutils as gu

testName = "XML I/O 01"

# memory management
mm = ib.IFObject()

print("GeoUtils test script: " + testName)

vs0 = cg.Vertex3Set.create()
vs0.setID("vs0")
v0 = vs0.addVertex()
v0.setCoords(1., 3., 5.)
v0 = vs0.addVertex()
v0.setCoords(2., -1., 4.)
v0 = vs0.addVertex()
v0.setCoords(-5., -3., 7.)

print("  Vertex set:")
for i in range(0, vs0.getNumVertices()):
    v0 = vs0.getVertex(i)
    print("    %s" % (v0.getString()))

xml0 = vs0.getXML0(2)

print("  XML:")

print(xml0)

vs1 = cg.Vertex3Set()
cg.getVertex3Set(xml0, vs1)

print("  Vertex set (from XML):")
for i in range(0, vs0.getNumVertices()):
    v0 = vs1.getVertex(i)
    print("    %s" % (v0.getString()))

print("All done!")
