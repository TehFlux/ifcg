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

outFile0 = 'temp/mesh.xml'

print("GeoUtils test script: " + testName)

meshName01 = "cube01"

# Get XML factories to initialize the hierarchy.
xf0 = cg.MeshXMLFactory.upcast(cg.Mesh.getXMLObjectFactory())
xf1 = cg.Vector2.getXMLObjectFactory()
xf2 = cg.Vector3.getXMLObjectFactory()
xf3 = cg.Vector4.getXMLObjectFactory()
xf4 = cg.VectorSet.getXMLObjectFactory()
xf5 = cg.FaceData.getXMLObjectFactory()

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

print("Writing XML data to file '%s'..." % outFile0)
mesh01.writeToXMLFile(outFile0)

mesh02 = cg.Mesh.create()
mm.addLocalRef(mesh02)
xf0.initObject(xml0, mesh02)

print("  Mesh (from XML):")
print("    name = '%s'" % mesh02.getID())
print("    %s" % mesh02.getString())

print("Reading XML data from file '%s'..." % outFile0)
mesh02.clear()
mesh02.setID("<none>")
mesh02.loadFromXMLFile(outFile0)

print("  Mesh (from XML file):")
print("    name = '%s'" % mesh02.getID())
print("    %s" % mesh02.getString())

print("All done!")
