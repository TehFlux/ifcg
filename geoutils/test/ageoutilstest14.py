#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Altjira/GeoUtils test 14.")

width = 600
height = 600
inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'leaf02.svg'
outFile0 = 'temp' + os.path.sep + 'asvg03.png'

svg0 = ag.SVG(inFile0, ag.SVG.TYPE_FILE)
#svg0.translate(cg.Vector3(-500., -500., 0))
#svg0.rotate(0.25 * math.pi, cg.AXIS_Z)
#svg0.scale(cg.Vector3(1.3, 1.3, 1.))
#svg0.translate(cg.Vector3(500., 500., 0))

print("  Creating transform graph...")
n10 = ag.LoadSVG.create()
n10.setFileName(inFile0)
n10.setID('n10')

n12 = cg.Center.create()
n12.setID('n12')

n14 = cg.Normalize.create()
n14.setID('n14')

n16 = cg.Scale.create()
# The total scale factor to fill the image is sqrt(2) ^ 2 = 2, since 
# Normalize uses the radius (diagonal) and we rotate by pi / 4.
n16.setScaleFactor(600. * 2.)
n16.setID('n16')

n18 = cg.Rotate.create()
n18.setAxis(cg.AXIS_Z)
n18.setAngle(0.25 * math.pi)
n18.setID('n18')

img0 = ag.Image.create()
img0.createNewData(width, height)

n20 = ag.Render.create()
n20.setImage(img0)
n20.setAxis(cg.AXIS_Z)
n20.setID('n20')

nodes = [ n10, n12, n14, n16, n18, n20 ]

g0 = cg.TransformGraph()
for it in nodes:
    g0.addNode(it)
g0.chain()
g0.setIO()

print("  Rendering SVG...")
c0 = cg.Clock()
c0.start()
g0.update()
c0.stop()
print ("    SVG rendered in " + str(c0.getElapsedTime()) + " secs.")

print("  Writing image to file...")
img0.writeToFile(outFile0)

print("All done!")
