#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Altjira/GeoUtils test 15.")

width = 300
height = 300
inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'jetmage01.png'
outFile0 = 'temp' + os.path.sep + 'image01.png'
scale0 = 0.8

img0 = ag.Image.create()
img0.loadFromFile(inFile0)
w0 = img0.getWidth()
h0 = img0.getHeight()
img0.translate(cg.Vector3(-0.5 * w0, -0.5 * h0, 0))
img0.scale(cg.Vector3(scale0, scale0, 0))
img0.rotate(-0.25 * math.pi, cg.AXIS_Z)

i0 = ag.Image(width, height)
print("  Rendering image...")
c0 = cg.Clock()
c0.start()
i0.begin()
i0.drawImage(img0)
i0.finish()
c0.stop()
print ("    Image rendered in " + str(c0.getElapsedTime()) + " secs.")

print("  Writing image to file...")
i0.writeToFile(outFile0)

print("All done!")
