#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math, random, rsvg, cairo
import CGeoUtils as cg
import IFObjectBase
import Altjira as ai
import IFMapping as im

#width = 1000
#height = 1000
#numCellsX = 10
#numCellsY = 10
#padding = 0.01
#cellWidth = float(width) / numCellsX
#cellHeight = float(height) / numCellsX

# Generate some SVG styles.
numColors = 1
colors = []
c1 = ai.FloatColor()
c1.c0 = 0.
c1.c1 = 0.
c1.c2 = 0.
c1.alpha = 1.
c1.space = ai.Color.SPACE_HSV
dv = 1. / numColors
for i in xrange(0, numColors):
    c2 = ai.FloatColor()
    c2.c0 = c1.c0
    c2.c1 = c1.c1
    c2.c2 = c1.c2
    c2.alpha = c1.alpha
    c2.space = ai.Color.SPACE_HSV
    ai.toRGB(c2)
    c3 = ai.ByteColor()
    ai.floatToByte(c2, c3)
    cSpec = "#%02x%02x%02x" % (c3.c0, c3.c1, c3.c2)
    colors += [cSpec]
    c1.c2 += dv
styles = cg.SVGShapeStyleVector()
for c in colors:
    #print "  " + c
    styles.push_back(cg.getSVGShapeStyle(c, 1., "#000000", 1., 0.))

def rescalePolys(source, target, width, height, padding):
    """Rescale set of polygons to specified size."""
    # Center on origin.
    ps1 = cg.Polygon3Set(source)
    ps1.center(cg.CENTER_BOUNDS)
    # Scale to cell size.
    r1 = ps1.getBounds()
    v1 = r1.getRadius()
    #print "  v1 = " + str(v1)
    paddingAbsX = padding * width
    paddingAbsY = padding * height
    v1n = v1.norm()
    sx = (width - 2. * paddingAbsX) / (2. * v1n)
    sy = (height - 2. * paddingAbsY) / (2. * v1n)
    s0 = min(sx, sy)
    m1 = cg.Matrix4.scale(s0, -s0, s0)
    ps1.transform(m1)
    ps1.applyTransform()
    target.addPolygons(ps1)

def renderSVG(svgData, width, height, pngFileName):
    """Render SVG data to a PNG file."""
    s0 = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx0 = cairo.Context(s0)
    ctx0.set_source_rgba(1., 1., 1., 1.)
    ctx0.rectangle(0, 0, width, height)
    ctx0.fill()
    h0 = rsvg.Handle(None, svgData)
    ctx0.save()
    h0.render_cairo(ctx0)
    ctx0.restore()
    s0.write_to_png(pngFileName)

def createBrushSheetAngular(baseName, polygons, width, height, cellWidth,  
    cellHeight, padding, styles):
    """Create an SVG brush sheet for an angle sensitive brush."""
    ps0 = cg.Polygon3Set()
    rescalePolys(polygons, ps0, cellWidth, cellHeight, padding)
    svgSheetFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
        + baseName + ".svg")
    numCellsX = int(width / cellWidth)
    numCellsY = int(height / cellHeight)
    ps1 = cg.Polygon3Set()
    dPhi = -2. * math.pi / (numCellsX * numCellsY)
    for i in xrange(0, numCellsX):
        for j in xrange(0, numCellsY):
            mt = cg.Matrix4.translate(
                -0.5 * width + 0.5 * cellWidth + i * cellWidth, 
                0.5 * height - 0.5 * cellHeight - j * cellHeight, 0.)
            mr = cg.Matrix4.rotate(dPhi * (j * numCellsX + i), cg.AXIS_Z)
            ps0t = cg.Polygon3Set(ps0)
            ps0t.transform(mt * mr)
            ps0t.applyTransform()
            ps1.addPolygons(ps0t)
    svg0 = ps1.getSVG(styles, "polygon", cg.AXIS_Z)
    svg1 = cg.getSVGImage(svg0, width, height, int(0.5 * width), 
        int(0.5 * height))
    f = open(svgSheetFileName, 'w')
    f.write(svg1)
    f.close()

def createBrushFrames(baseName, width, height, cellWidth, cellHeight):
    """Create brush frames from an SVG brush sheet."""
    print "  Creating brush frames..."
    svgSheetFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
        + baseName + ".svg")
    pngSheetFileName = ('temp' + os.path.sep + 'brushes' + os.path.sep 
        + baseName + ".png")
    numCellsX = int(width / cellWidth)
    numCellsY = int(height / cellHeight)
    # Read data from the SVG brush sheet.
    f = open(svgSheetFileName, 'r')
    svg0 = f.read()
    f.close()
    # Render the svg file.
    print "    Rendering SVG brush sheet..."
    renderSVG(svg0, width, height, pngSheetFileName)
    # Create Brush frames.
    print "    Creating brush frames..."
    frameDir = 'temp' + os.path.sep + "brushes" + os.path.sep + baseName
    if (not os.path.exists(frameDir)):
        os.mkdir(frameDir)
    img0 = ai.Image(pngSheetFileName)
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

def createGIH(baseName, brushName, brushFileName, width, height, 
    cellWidth, cellHeight, selectionMode):
    """Create GIMP GIH brush.
    
    This creates a one-dimensional GIMP GIH brush from the frames indicated 
    by the base name."""
    # Create GIH brush.
    print "  Creating GIH brush..."
    frameDir = 'temp' + os.path.sep + "brushes" + os.path.sep + baseName
    numCellsX = int(width / cellWidth)
    numCellsY = int(height / cellHeight)
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
        + "sel0:" + selectionMode + "\n")
    f0 = open(brushFileName, 'w')
    f0.write(gih0)
    for i in xrange(0, numCellsX * numCellsY):
        fn1 = frameDir + os.path.sep + ("brf_%s_%04d.gbr" % (baseName, i))
        f1 = open(fn1, 'r')
        f0.write(f1.read())
        f1.close()
    f0.close()

def renderPolys(polygons, outFile, width, height, styles):
    """Render polygons."""
    print "  Rendering polygons..."
    style0 = cg.getSVGPolygonStyle()
    svg0 = polygons.getSVG(styles, "shape", cg.AXIS_Z)
    svg1 = cg.getSVGImage(svg0, width, height, int(0.5 * width), 
        int(0.5 * height))
    f = open(outFile, 'w')
    f.write(svg1)
    f.close()

def getPolygonsFromSVG(target, baseName, sourceFileName, numElements):
    """Get polygons from an SVG image."""
    elementIDs = IFObjectBase.StringVector()
    for i in xrange(1, numElements + 1):
        elementIDs.push_back(baseName + ("%02d" % i))
    cg.getSVGPolygons(sourceFileName, elementIDs, target)

def createAngularBrush(baseName, brushName, sourceFileName, 
    sourceBaseName, width, height, cellWidth, cellHeight, padding, styles):
    """Create random scatter brush."""
    print "Creating random scatter brush..."
    print "    Extracting polygon data from SVG file..."
    ps0 = cg.Polygon3Set()
    getPolygonsFromSVG(ps0, sourceBaseName, sourceFileName, 1)
    createBrushSheetAngular(baseName, ps0, width, height, cellWidth, 
        cellHeight, padding, styles)
    createBrushFrames(baseName, width, height, cellWidth, cellHeight)
    createGIH(baseName, brushName, 
        'temp' + os.path.sep + "brushes" + os.path.sep + baseName + ".gih", 
        width, height, cellWidth, cellHeight, "angular")

sourceFileName = ('test' + os.path.sep + 'images' + os.path.sep 
    + 'track02.svg')
createAngularBrush('Track01', 'T15 Track 01', sourceFileName, 
    'track', 1000, 1000, 100, 100, 0.01, styles)
sourceFileName = ('test' + os.path.sep + 'images' + os.path.sep 
    + 'track03.svg')
createAngularBrush('Track02', 'T16 Track 02', sourceFileName, 
    'track', 1000, 1000, 100, 100, 0.01, styles)
sourceFileName = ('test' + os.path.sep + 'images' + os.path.sep 
    + 'track04.svg')
createAngularBrush('Track03', 'T17 Track 03', sourceFileName, 
    'track', 1000, 1000, 100, 100, 0.01, styles)
createAngularBrush('Track04', 'T18 Track 04', sourceFileName, 
    'track', 2000, 2000, 200, 200, 0.01, styles)
createAngularBrush('Track05', 'T19 Track 05', sourceFileName, 
    'track', 5000, 5000, 500, 500, 0.01, styles)
sourceFileName = ('test' + os.path.sep + 'images' + os.path.sep 
    + 'track05.svg')
createAngularBrush('Track06', 'T20 Track 06', sourceFileName, 
    'track', 2000, 2000, 200, 200, 0.01, styles)
createAngularBrush('Track07', 'T21 Track 07', sourceFileName, 
    'track', 5000, 5000, 500, 500, 0.01, styles)
sourceFileName = ('test' + os.path.sep + 'images' + os.path.sep 
    + 'track06.svg')
createAngularBrush('Track08', 'T22 Track 08', sourceFileName, 
    'track', 2000, 2000, 200, 200, 0.01, styles)
createAngularBrush('Track09', 'T23 Track 09', sourceFileName, 
    'track', 5000, 5000, 500, 500, 0.01, styles)

print "All done!"
