#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os
import CGeoUtils as cg

print "Creating polygon..."
ps0 = cg.Polygon3Set()
p0 = ps0.addPolygon()

print "Creating vertices..."
verts = []
for i in xrange(0, 5):
    verts += [p0.addVertex()]
verts[0].setCoords(cg.Vector3(65., 285., 0.))
verts[1].setCoords(cg.Vector3(217., 154., 0.))
verts[2].setCoords(cg.Vector3(165., -51., 0.))
verts[3].setCoords(cg.Vector3(-65., -88., 0.))
verts[4].setCoords(cg.Vector3(-102., 140., 0.))

print str(p0)

style0 = cg.getSVGPolygonStyle("none")

print "Creating SVG file..."
svg0 = p0.getSVG(cg.SVG_DEFAULT_POLY_STYLE, "polygon01", cg.AXIS_Z)
svg1 = p0.getSVG(cg.SVG_DEFAULT_POLY_STYLE, "polygon01", cg.AXIS_Z, 
    cg.SHAPE_TYPE_PATH)
svg2 = p0.getSVG(style0, "polygon01", cg.AXIS_Z, cg.SHAPE_TYPE_PATH, False)
print "  polygon:     " + str(svg0)
print "  path:        " + str(svg1)
print "  path (open): " + str(svg2)
ps0.writeSVG('temp' + os.path.sep + "polygons0101.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "polygon", cg.AXIS_Z)
ps0.writeSVG('temp' + os.path.sep + "polygons0102.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "polygon", cg.AXIS_Z, cg.SHAPE_TYPE_PATH)
ps0.writeSVG('temp' + os.path.sep + "polygons0103.svg", 
    style0, "polygon", cg.AXIS_Z, cg.SHAPE_TYPE_PATH, False)

print "All done!"
