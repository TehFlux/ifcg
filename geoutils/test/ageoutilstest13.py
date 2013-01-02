#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Altjira/GeoUtils test 13.")

width = 1000
height = 1000
inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'leaf02.svg'
outFile0 = 'temp' + os.path.sep + 'asvg02.png'

svg0 = ag.SVG(inFile0, ag.SVG.TYPE_FILE)
svg0.translate(cg.Vector3(-500., -500., 0))
svg0.rotate(0.25 * math.pi, cg.AXIS_Z)
svg0.scale(cg.Vector3(1.3, 1.3, 1.))
#svg0.translate(cg.Vector3(500., 500., 0))

i0 = ag.Image(width, height)
print("  Rendering SVG...")
c0 = cg.Clock()
c0.start()
i0.begin()
#i0.drawSVG(svg0, -500, -500)
i0.drawSVG(svg0)
i0.finish()
c0.stop()
print ("    SVG rendered in " + str(c0.getElapsedTime()) + " secs.")

print("  Writing image to file...")
i0.writeToFile(outFile0)

print("All done!")
