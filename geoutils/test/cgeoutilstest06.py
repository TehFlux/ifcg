#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math, random
import CGeoUtils as cg

width = 1000
height = 1000
numCellsX = 10
numCellsY = 10
padding = 0.05

cellWidth = float(width) / numCellsX
cellHeight = float(height) / numCellsX
paddingAbsX = padding * cellWidth
paddingAbsY = padding * cellHeight

print("Extracting path data from SVG file...")
d0 = cg.getAttrValue('test/images/arrow01.svg', 'path', 'arrow01', 'd')
print("  arrow01.d = " + d0)

vs0 = cg.Vertex3Set.create()
cg.extractSVGVertices(d0, vs0)

print("Creating polygon...")
p0 = cg.Polygon3(vs0)
print("  p0 = " + str(p0))
# Center on origin.
p0b = p0.getBounds()
v0 = p0b.getCenter()
m0 = cg.Matrix4.translate(v0.flip())
p1 = cg.Polygon3(p0)
p1.transform(m0)
# Scale to cell size.
v1 = p1.getBounds().getRadius()
print("  v1 = " + str(v1))
v1n = v1.norm()
sx = (cellWidth - 2. * paddingAbsX) / (2. * v1n)
sy = (cellHeight - 2. * paddingAbsY) / (2. * v1n)
s0 = min(sx, sy)
m1 = cg.Matrix4.scale(s0, -s0, s0)
p1.transform(m1)

ps0 = cg.Polygon3Set()
p1.thisown = 0
ps0.addPolygon(p1)
p1 = None

ps1 = cg.Polygon3Set()
dPhi = -2. * math.pi / (numCellsX * numCellsY)
for i in range(0, numCellsX):
    for j in range(0, numCellsY):
        mt = cg.Matrix4.translate(
            -0.5 * width + 0.5 * cellWidth + i * cellWidth, 
            0.5 * height - 0.5 * cellHeight - j * cellHeight, 0.)
        mr = cg.Matrix4.rotate(dPhi * (j * numCellsX + i), cg.AXIS_Z)
        ps0t = cg.Polygon3Set(ps0)
        ps0t.transform(mt * mr)
        ps0t.applyTransform()
        ps1.addPolygons(ps0t)

outFile = 'temp' + os.path.sep + "polygons06.svg"
style0 = cg.getSVGPolygonStyle("#000000", 1, "#000000", 0)
svg0 = ps1.getSVG(style0, "polygon", cg.AXIS_Z)
svg1 = cg.getSVGImage(svg0, width, height, int(0.5 * width), 
    int(0.5 * height))
print("Writing output to '%s'..." % outFile)
f = open(outFile, 'w')
f.write(svg1)
f.close()

print("All done!")
