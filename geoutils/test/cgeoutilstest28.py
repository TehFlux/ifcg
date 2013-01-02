#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import CGeoUtils as cg
import Altjira as ai

print("Testing GeoUtils...")

outFile0 = 'temp' + os.path.sep + 'cube03.svg'
cubeScale = 5.
imageScale = 700.
imageWidth = 1024
imageHeight = 768
numStyles = 6

print("  Creating styles...")

colors = ai.ColorVector()
c0 = ai.createFloatColor(0.3, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
c1 = ai.createFloatColor(0.8, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
ai.createColors(colors, c0, c1, numStyles, 1, 1)
numColors = colors.size()

styles = []
styleSource = cg.SVGShapeStyleVectorSource.create()

st0 = cg.getSVGShapeStyle("#707070", 0.7, "#000000", 1., 0.)
styleSource.addStyle(st0)
styleSource.addStyle(st0)
st1 = cg.getSVGShapeStyle("#707070", 0.0, "#707070", 1., 1.)
styleSource.addStyle(st1)
styleSource.addStyle(st1)

for i in range(0, numColors):
    c = colors[i]
    ch0 = c.getHex()
    print(("    c%02d = " % i) + ch0)
    s0 = cg.getSVGShapeStyle(ch0[:7], c.getAlpha(), "#000000", 1., 1.)
    styles += [s0]
    styleSource.addStyle(s0)

print("  Creating cube mesh...")
g0 = cg.TransformableGroup()
c0 = cg.Mesh.cube()
g0.addItem(c0)
c0.scale(cg.Vector3(cubeScale, cubeScale, cubeScale))
c0.applyTransform()

print("  Creating camera...")
cam0 = cg.Camera()
cam0.setOriginCam(10., -30., 0., 30.)
print(str(cam0))
V = cam0.getViewMatrix()
I = cg.Matrix4.scale(imageScale, imageScale, imageScale)

print(str(cg.Matrix3.rotate(90. * math.pi / 180., cg.AXIS_X)))

print("  Transforming mesh...")
c0.transformVI(V, I)
c0.applyTransform()
c0.removeBackfaces(cg.Vector3.E_Y.flip())

ps0 = cg.Polygon3Set()
c0.getPolygons(ps0)
ps0.sort(cg.Polygon3CompareAxis.create(cg.AXIS_Y))

ps1 = cg.Polygon3Set()
sq0 = cg.Polygon3.square()
sq0.scale(cg.Vector3(imageWidth, 1., 1.))
sq1 = cg.Polygon3.square()
sq1.scale(cg.Vector3(1., 1., imageHeight))
sq1.translate(cg.Vector3(0.5, 0., 0.))
ci0 = cg.Polygon3.circle(100)
ci0.scale(cg.Vector3(0.6 * imageWidth, 1., 0.6 * imageWidth))
ci1 = cg.Polygon3.circle(100)
ci1.scale(cg.Vector3(0.1 * imageWidth, 1., 0.1 * imageWidth))

ps1.addPolygon(sq0)
ps1.addPolygon(sq1)
ps1.addPolygon(ci0)
ps1.addPolygon(ci1)
ps1.addPolygons(ps0)

ip0 = cg.SVGImageProperties()
ip0.setFileName(outFile0)
ip0.setStyleSource(styleSource)
ip0.setWidth(imageWidth)
ip0.setHeight(imageHeight)
ip0.setOrigin(cg.Vector2(imageWidth / 2, imageHeight / 2))
ps1.writeSVG(ip0, "polygon", cg.AXIS_Y)

print("All done!")
