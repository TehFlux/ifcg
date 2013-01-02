#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math, random, rsvg, cairo
import CGeoUtils as cg
import IFObjectBase
import Altjira as ai

width = 1000
height = 1000
numCellsX = 10
numCellsY = 10
padding = 0.05

cellWidth = float(width) / numCellsX
cellHeight = float(height) / numCellsX
paddingAbsX = padding * cellWidth
paddingAbsY = padding * cellHeight

def createBrush(sourceFileName, baseName, numElements, svgFileName, 
    pngFileName, brushName, brushFileName, removeFrames = True):
    """Create a brush sheet for an angle sensitive brush."""
    print "Extracting polygon data from SVG file..."
    elementIDs = IFObjectBase.StringVector()
    for i in xrange(1, numElements + 1):
        elementIDs.push_back(baseName + ("%02d" % i))
    ps0 = cg.Polygon3Set()
    cg.getSVGPolygons(sourceFileName, elementIDs, ps0)
    
    print "  Transforming polygons..."
    # Center on origin.
    ps1 = cg.Polygon3Set(ps0)
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
    frameDirCreated = False 
    if (not os.path.exists(frameDir)):
        os.mkdir(frameDir)
        frameDirCreated = True
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
                "BrF_%04d" % (j * numCellsY + i), 10, 
                ai.DESATURATION_BY_VALUE)
    # Create GIH brush.
    print "  Creating GIH brush..."
    gih0 = (brushName + '\n' + str(numCellsX * numCellsY) 
        + "ncells:" + str(numCellsX * numCellsY) + " "
        + "cellwidth:" + str(int(cellWidth)) + " "
        + "cellheight:" + str(int(cellHeight)) + " "
        + "step:" + str(numCellsX * numCellsY) + " "
        + "dim:1 "
        + "cols:" + str(numCellsX) + " "
        + "rows:" + str(numCellsY) + " "
        + "placement:constant "
        + "rank0:" + str(numCellsX * numCellsY) + " "
        + "sel0:angular\n")
    f0 = open(brushFileName, 'w')
    f0.write(gih0)
    for i in xrange(0, numCellsX * numCellsY):
        fn1 = frameDir + os.path.sep + ("brf_%s_%04d.gbr" % (baseName, i))
        f1 = open(fn1, 'r')
        f0.write(f1.read())
        f1.close()
        if (removeFrames):
            os.unlink(fn1)
    if (removeFrames 
        and frameDirCreated):
        os.rmdir(frameDir)
    f0.close()

createBrush('test/images/track01.svg', 'track', 2, 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "track01.svg", 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "track01.png", 
    'T01 Track', 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "track01.gih")
createBrush('test/images/chain01.svg', 'chain', 3, 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "chain01.svg", 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "chain01.png", 
    'T02 Chain', 
    'temp' + os.path.sep + 'brushes' + os.path.sep + "chain01.gih")

print "All done!"
