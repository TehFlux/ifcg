#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Altjira/GeoUtils test 17.")

inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'heightmap05.png'
#inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'test01.png'
outFile0 = 'temp' + os.path.sep + 'normalmap05.png'
maxHeight = 20.

c0 = cg.Clock()
c0.start()

print ("  Testing Image::valueToNormal()...")

heightMap = ag.Image(inFile0)
normalMap = ag.Image(heightMap.getWidth(), heightMap.getHeight())

heightMap.valueToNormal(normalMap, maxHeight)

normalMap.writeToFile(outFile0)

c0.stop()
print ("  Done (elapsed time " + str(c0.getElapsedTime()) + " secs).")

print("All done!")
