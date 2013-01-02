#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math, random, rsvg, cairo
import CGeoUtils as cg
import IFObjectBase
import Altjira as ai
import IFMapping as im

width = 1000
height = 1000
numCellsX = 10
numCellsY = 10
padding = 0.01
cellWidth = float(width) / numCellsX
cellHeight = float(height) / numCellsX
paddingAbsX = padding * cellWidth
paddingAbsY = padding * cellHeight

def createBrushFrames(polygons, baseName, svgFileName, pngFileName):
    """Create a brush sheet for an angle sensitive brush."""
    print "  Transforming polygons..."
    # Center on origin.
    ps1 = cg.Polygon3Set(polygons)
    ps1.center(cg.CENTER_BOUNDS)
    # Scale to cell size.
    r1 = ps1.getBounds()
    v1 = r1.getRadius()
    print "  v1 = " + str(v1)
    v1n = v1.norm()
    sx = (cellWidth - 2. * paddingAbsX) / (2. * v1n)
    sy = (cellHeight - 2. * paddingAbsY) / (2. * v1n)
    s0 = min(sx, sy)
    m1 = cg.Matrix4.scale(s0, -s0, s0)
    ps2 = cg.Polygon3Set(ps1)
    ps2.transform(m1)
    ps2.applyTransform()
    # Create rotated copies.
    ps3 = cg.Polygon3Set()
    dPhi = -2. * math.pi / (numCellsX * numCellsY)
    for i in xrange(0, numCellsX):
        for j in xrange(0, numCellsY):
            mt = cg.Matrix4.translate(
                -0.5 * width + 0.5 * cellWidth + i * cellWidth, 
                0.5 * height - 0.5 * cellHeight - j * cellHeight, 0.)
            mr = cg.Matrix4.rotate(dPhi * (j * numCellsX + i), cg.AXIS_Z)
            ps2t = cg.Polygon3Set(ps2)
            ps2t.transform(mt * mr)
            ps2t.applyTransform()
            ps3.addPolygons(ps2t)
    
    style0 = cg.getSVGPolygonStyle("#000000", 1, "#000000", 0)
    svg0 = ps3.getSVG(style0, "polygon", cg.AXIS_Z)
    svg1 = cg.getSVGImage(svg0, width, height, int(0.5 * width), 
        int(0.5 * height))
    f = open(svgFileName, 'w')
    f.write(svg1)
    f.close()
    # Render the svg file.
    print "  Rendering SVG..."
    s0 = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx0 = cairo.Context(s0)
    ctx0.set_source_rgba(1., 1., 1., 1.)
    ctx0.rectangle(0, 0, width, height)
    ctx0.fill()
    h0 = rsvg.Handle(None, svg1)
    ctx0.save()
    h0.render_cairo(ctx0)
    ctx0.restore()
    s0.write_to_png(pngFileName)
    # Create Brush frames.
    print "  Creating brush frames..."
    frameDir = 'temp' + os.path.sep + 'brushes' + os.path.sep + baseName
    if (not os.path.exists(frameDir)):
        os.mkdir(frameDir)
    img0 = ai.Image(pngFileName)
    r0 = ai.ImageRect()
    r0.width = int(cellWidth)
    r0.height = int(cellHeight)
    for i in xrange(0, numCellsX):
        for j in xrange(0, numCellsY):
            r0.x = int(i * cellWidth)
            r0.y = int(j * cellHeight)
            img1 = ai.Image(int(cellWidth), int(cellHeight))
            img1.fill(img0, r0)
            img1.writeToFile(frameDir + os.path.sep 
                + ("brf_%s_%04d.gbr" % (baseName, j * numCellsY + i)), 
                ai.Image.TYPE_GBR_GRAYSCALE, 
                "BrF_%s_%04d" % (baseName, j * numCellsY + i), 10, 
                ai.DESATURATION_BY_VALUE)

def createGIH(baseName, brushName, brushFileName):
    """Create GIMP GIH brush."""
    # Create GIH brush.
    print "  Creating GIH brush..."
    gih0 = (brushName + '\n' + str(numCellsX * numCellsY) 
        + "ncells:" + str(numCellsX * numCellsY) + " "
        + "cellwidth:" + str(int(cellWidth)) + " "
        + "cellheight:" + str(int(cellHeight)) + " "
        + "step:1 "
        + "dim:1 "
        + "cols:1 "
        + "rows:1 "
        + "placement:constant "
        + "rank0:" + str(numCellsX * numCellsY) + " "
        + "sel0:angular\n")
    f0 = open(brushFileName, 'w')
    f0.write(gih0)
    frameDir = 'temp' + os.path.sep + 'brushes' + os.path.sep + baseName
    for i in xrange(0, numCellsX * numCellsY):
        fn1 = frameDir + os.path.sep + ("brf_%s_%04d.gbr" % (baseName, i))
        f1 = open(fn1, 'r')
        f0.write(f1.read())
        f1.close()
    f0.close()

def scatterPolys(baseName, sourceFileName, numSourceElements, 
    numTargetElements, rScale, dScale, target):
    """Create a scattering of polygons."""
    print "  Extracting polygon data from SVG file..."
    elementIDs = IFObjectBase.StringVector()
    for i in xrange(1, numSourceElements + 1):
        elementIDs.push_back(baseName + ("%02d" % i))
    ps0 = cg.Polygon3Set()
    cg.getSVGPolygons(sourceFileName, elementIDs, ps0)
    
    print "  Transforming polygons..."
    ps1 = cg.Polygon3Set()
    for i in xrange(0, ps0.getNumPolygons()):
        p0 = ps0.getPolygon(i)
        b0 = p0.getBounds()
        # Center on origin.
        m0 = cg.Matrix4.translate(b0.getCenter().flip())
        s = 1. / b0.getRadius().norm()
        # Scale to unit size.
        m1 = cg.Matrix4.scale(s, s, s)
        p1 = cg.Polygon3(p0)
        p1.transform(m1 * m0)
        p1.thisown = 0
        ps1.addPolygon(p1)
    
    print "  Scattering polygons..."
    numPolys = ps0.getNumPolygons()
    ps2 = cg.Polygon3Set()
    for i in xrange(0, numTargetElements):
        # Select a random polygon.
        k = numPolys
        while (k >= numPolys):
            k = int(im.getRandomDouble() * numPolys)
        p0 = ps1.getPolygon(k)
        # Create random translation.
        tx = 2.
        ty = 2.
        while ((tx < -1.)
            or (tx > 1.)):
            tx = im.getRandomNorm(0., 1. / 3.)
        while ((ty < -1.)
            or (ty > 1.)):
            ty = im.getRandomNorm(0., 1. / 3.)
        r0 = cg.Vector2(tx, ty).norm()
        t0 = cg.Vector3(tx * 0.5 * width, ty * 0.5 * height, 0.)
        m0 = cg.Matrix4.translate(t0)
        # Create random rotation.
        m1 = cg.Matrix4.rotate(2. * math.pi * im.getRandomDouble(), cg.AXIS_Z)
        # Create random scale.
        s = (rScale.getValue(im.getRandomDouble()) 
            * dScale.clamp(dScale.getValue(1. - r0)))
        #print "  s = " + str(s)
        m2 = cg.Matrix4.scale(s, s, s)
        # Transform it.
        p1 = cg.Polygon3(p0)
        p1.transform(m0 * (m1 * m2))
        p1.thisown = 0
        target.addPolygon(p1)
        p1 = None

def renderPolys(polygons, outFile):
    """Render polygons."""
    print "  Rendering polygons..."
    style0 = cg.getSVGPolygonStyle()
    svg0 = polygons.getSVG(style0, "shape", cg.AXIS_Z)
    svg1 = cg.getSVGImage(svg0, width, height, int(0.5 * width), 
        int(0.5 * height))
    f = open(outFile, 'w')
    f.write(svg1)
    f.close()

im.initRandom(1)

#print "Scattering polygons #1..."
#ps2 = cg.Polygon3Set()
#scatterPolys('shape', 
#    'test' + os.path.sep +'images' + os.path.sep + 'shapes01.svg', 
#    5, 100, cg.Range(10., 80.), cg.Range(0.2, 1.), ps2)
#renderPolys(ps2, 'temp' + os.path.sep + "scatter01.svg")

#print "Creating GIH brush #1..."
#createBrushFrames(ps2, 'scatter01', 
#    'temp' + os.path.sep + "scatter01.svg", 
#    'temp' + os.path.sep + "scatter01.png")
#createGIH('scatter01', 'T06 Scatter 01', 
#    'temp' + os.path.sep + "scatter01.gih")

print "Scattering polygons #2..."
ps3 = cg.Polygon3Set()
scatterPolys('shape', 
    'test' + os.path.sep +'images' + os.path.sep + 'shapes02.svg', 
    1, 50, cg.Range(10., 30.), cg.Range(0.5, 1.), ps3)
renderPolys(ps3, 'temp' + os.path.sep + 'brushes' + os.path.sep 
    + "scatter02x.svg")

print "Creating GIH brush #2..."
createBrushFrames(ps3, 'scatter02', 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "scatter02.svg", 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "scatter02.png")
createGIH('scatter02', 'T07 Scatter 02', 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "scatter02.gih")

im.disposeRandom()

print "All done!"
