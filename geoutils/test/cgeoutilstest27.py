#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import CGeoUtils as cg
import Altjira as ai

print("Testing GeoUtils...")

xmlHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
outFile0 = 'temp' + os.path.sep + 'cube01.mesh'

print("  Creating cube mesh...")
g0 = cg.TransformableGroup()
m0 = cg.Mesh.cube()
m0.setID("cube0")
g0.addItem(m0)

print("    Faces:")
for i in range(0, m0.getNumFaces()):
    f0 = m0.getFace(i)
    print("    #" + str(i) + ": " + str(f0) + " (n = " + str(f0.getNormal()) 
        + ", b = " + str(f0.getBinormal()) + ", t = " + str(f0.getTangent()) 
        + ")")

print("  Writing XML to file '" + outFile0 + "'...")
xml0 = m0.getXML()
print("    m0.getXML(): " + xml0)
open(outFile0, 'w').write(xmlHeader + xml0)

print("  Reading mesh data from file '" + outFile0 + "'...")
m1 = cg.Mesh.create()
m1.setID("cube1")
g0.addItem(m1)
cg.getMesh(outFile0, "cube0", m1)

xml1 = m1.getXML()
print("    m1.getXML(): " + xml1)

print("All done!")
