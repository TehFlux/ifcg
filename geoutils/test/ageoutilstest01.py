#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Testing Altjira/GeoUtils...")

width = 600
height = 600
outFile0 = 'temp' + os.path.sep + 'apolygons01.png'

print("  Creating polygon...")
ps0 = cg.Polygon3Set()
p0 = ps0.addPolygon()

print("  Creating vertices...")
verts = []
for i in range(0, 5):
    verts += [p0.addVertex()]
verts[0].setCoords(cg.Vector3(65., 285., 0.))
verts[1].setCoords(cg.Vector3(217., 154., 0.))
verts[2].setCoords(cg.Vector3(165., -51., 0.))
verts[3].setCoords(cg.Vector3(-65., -88., 0.))
verts[4].setCoords(cg.Vector3(-102., 140., 0.))
ps0.center()

i0 = ag.Image(width, height)
print("  Rendering polygons...")
c0 = cg.Clock()
c0.start()
i0.renderPolygons(ps0, None, cg.AXIS_Z)
c0.stop()
print ("    " + str(ps0.getNumPolygons()) + " polygons rendered in " 
    + str(c0.getElapsedTime()) + " secs (" + str(ps0.getNumPolygons() 
    / c0.getElapsedTime()) + ") polygons/sec).")

print("  Writing image to file...")
i0.writeToFile(outFile0)

print("All done!")
