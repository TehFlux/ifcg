#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Altjira/GeoUtils test 11.")

width = 1000
height = 1000
inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'leaf02.svg'
outFile0 = 'temp' + os.path.sep + 'asvg01.png'

i0 = ag.Image(width, height)
print("  Rendering SVG...")
c0 = cg.Clock()
c0.start()
#d0 = open(inFile0, 'r').read()
#i0.renderSVG(d0)
i0.renderSVGFile(inFile0, -500, -500)
c0.stop()
print ("    SVG rendered in " + str(c0.getElapsedTime()) + " secs.")

print("  Writing image to file...")
i0.writeToFile(outFile0)

print("All done!")
