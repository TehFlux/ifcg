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

outFile0 = 'temp/vectorset.xml'

print("GeoUtils test script: " + testName)

# Get XML factories to initialize the hierarchy.
xf0 = cg.Vector.getXMLObjectFactory()
xf1 = cg.Vector2.getXMLObjectFactory()
xf2 = cg.Vector3.getXMLObjectFactory()
xf3 = cg.Vector4.getXMLObjectFactory()
xf4 = cg.VectorSetXMLFactory.upcast(
    cg.VectorSet.getXMLObjectFactory())

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

print("Writing XML data to file '%s'..." % outFile0)
vs0.writeToXMLFile(outFile0)

vs1 = cg.VectorSet.create()
mm.addLocalRef(vs1)
xf4.initObject(xml0, vs1)

print("  Vector set (from XML):")
print("    name = '%s'" % vs1.getID())
for i in range(0, vs1.getNumVectors()):
    v0 = vs1.getVector(i)
    print("    %s" % (v0.getString()))

print("Reading XML data from file '%s'..." % outFile0)
vs1.clearVectors()
vs1.setID("<none>")
vs1.loadFromXMLFile(outFile0)

print("  Vector set (from XML file):")
print("    name = '%s'" % vs1.getID())
for i in range(0, vs1.getNumVectors()):
    v0 = vs1.getVector(i)
    print("    %s" % (v0.getString()))

print("All done!")
