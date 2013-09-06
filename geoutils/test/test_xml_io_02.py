#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""GeoUtils test script."""
import os
import IFObjectBase as ib
import IFMapping as im
import CGeoUtils as cg
import Altjira as ai
import geoutils as gu

testName = "XML I/O 02"

# memory management
mm = ib.IFObject()

print("GeoUtils test script: " + testName)

meshName01 = "cube01"

print("  Creating mesh '%s'..." % meshName01)

mesh01 = cg.Mesh.plane()
mesh01.setID(meshName01)
mm.addLocalRef(mesh01)

texCoords0 = [
    cg.Vector2.create(0., 0.), 
    cg.Vector2.create(1., 0.), 
    cg.Vector2.create(1., 1.), 
    cg.Vector2.create(0., 1.)
]
f0 = mesh01.getFace(0)
f0.addTexCoords(*texCoords0)

print("    %s" % mesh01.getString())

xml0 = mesh01.getXML0(2)

print("  XML:")

print(xml0)

mesh02 = cg.Mesh.create()
mm.addLocalRef(mesh02)
cg.getMesh(xml0, mesh02)

print("  Mesh (from XML):")
print("    name = '%s'" % mesh02.getID())
print("    %s" % mesh02.getString())

print("All done!")
