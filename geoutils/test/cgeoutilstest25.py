#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import CGeoUtils as cg

print("Testing GeoUtils...")

outFile0 = 'temp' + os.path.sep + 'cube01.svg'

print("  Creating cube mesh...")
c0 = cg.Mesh.cube()
ps0 = cg.Polygon3Set()
c0.getPolygons(ps0)

print("  Transforming mesh...")
ps0.scale(cg.Vector3(400., 400., 400.))
ps0.rotate(0.3 * math.pi, cg.AXIS_Y)
ps0.rotate(0.3 * math.pi, cg.AXIS_X)
ps0.applyTransform()

print("  Writing result to '" + outFile0 + "'...")
ps0.writeSVG(outFile0, cg.SVG_DEFAULT_POLY_STYLE, "polygon", cg.AXIS_Z)

print("All done!")
