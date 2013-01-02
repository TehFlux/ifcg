#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Altjira/GeoUtils test 12.")

width = 1000
height = 1000
inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'leaf02.svg'

svg0 = ag.SVG(inFile0, ag.SVG.TYPE_FILE)
svg0.translate(cg.Vector3(-500., -500., 0))
svg0.rotate(0.25 * math.pi, cg.AXIS_Z)

print("  SVG bounds: " + str(svg0.getBounds()))

print("All done!")
