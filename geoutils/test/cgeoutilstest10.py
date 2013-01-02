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
numColors = 10
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
    frameDir = 'temp' + os.path.sep + 'brushes' + os.path.sep + baseName
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

def scatterPolys(source, target, numTargetElements, 
    width, height, rScale, dScale, stdDevX, stdDevY, maxR):
    """Create a scattering of polygons.
    
    Scattering takes place in several steps. First, the polygons in the 
    source set are normalized to an uniform size. Then, a number of 
    scattered duplicates of randomly selected polygons from the source set are 
    created. Scattering consists of a translation to a randomly selected point 
    (using a normal distribution with the specified parameters) and two 
    scaling components. The first scaling component is random and the second 
    is proportional to the distance of the polygon to the origin. The 
    scattered polygons are collected in the target set."""
    print "  Scattering polygons..."
    print "    Normalizing polygons..."
    ps1 = cg.Polygon3Set()
    for i in xrange(0, source.getNumPolygons()):
        p0 = source.getPolygon(i)
        b0 = p0.getBounds()
        # Center on origin.
        m0 = cg.Matrix4.translate(b0.getCenter().flip())
        s = 1. / b0.getRadius().norm()
        # Scale to unit size.
        m1 = cg.Matrix4.scale(s, s, s)
        p1 = p0.duplicate()
        p1.transform(m1 * m0)
        ps1.addPolygon(p1)
    print "    Creating scattered duplicates..."
    numPolys = source.getNumPolygons()
    ps2 = cg.Polygon3Set()
    for i in xrange(0, numTargetElements):
        # Select a random polygon.
        k = numPolys
        while (k >= numPolys):
            k = int(im.getRandomDouble() * numPolys)
        p0 = ps1.getPolygon(k)
        # Create random translation.
        # Use the specified standard deviations (scaled down by one third to 
        # fit the interval [0, 1] more easily) in X and Y directions and the 
        # maximum radius to find a suitable translation vector.
        tx = 2.
        ty = 2.
        r0 = maxR + 1.
        while (r0 > maxR):
            tx = im.getRandomNorm(0., stdDevX * 1. / 3.)
            ty = im.getRandomNorm(0., stdDevY * 1. / 3.)
            r0 = cg.Vector2(tx, ty).norm()
            #print ("tx = " + str(tx) + ", ty = " + str(ty) + ", r0 = " 
            #   + str(r0))
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
        p1 = p0.duplicate()
        p1.transform(m0 * (m1 * m2))
        target.addPolygon(p1)

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

def createAngularScatterBrush(baseName, brushName, sourceFileName, 
    sourceBaseName, numSourceShapes, numTargetShapes, width, height, 
    cellWidth, cellHeight, padding, rRange, dRange, stdDevX, stdDevY, maxR, 
    styles):
    """Create angular scatter brush."""
    print "Creating angular scatter brush..."
    print "    Extracting polygon data from SVG file..."
    ps0 = cg.Polygon3Set()
    getPolygonsFromSVG(ps0, sourceBaseName, sourceFileName, numSourceShapes)
    ps1 = cg.Polygon3Set()
    scatterPolys(ps0, ps1, numTargetShapes, width, height, 
        rRange, dRange, stdDevX, stdDevY, maxR)
    renderPolys(ps1, 'temp' + os.path.sep + "brushes" + os.path.sep 
        + baseName + "_t.svg", width, height, styles)
    createBrushSheetAngular(baseName, ps1, 
        width, height, cellWidth, cellHeight, padding, styles)
    createBrushFrames(baseName, width, height, cellWidth, cellHeight)
    createGIH(baseName, brushName, 
        'temp' + os.path.sep + "brushes" + os.path.sep + baseName + ".gih", 
        width, height, cellWidth, cellHeight, "angular")

sourceFileName = ('test' + os.path.sep + 'images' + os.path.sep 
    + 'shapes02.svg')
im.initRandom(4)
createAngularScatterBrush('AScatter03', 'T08 A Scatter 03', 
    sourceFileName, 'shape', 1, 100, 1000, 1000, 100, 100, 0.01, 
    cg.Range(10., 30.), cg.Range(0.4, 1.), 1., 1., 1., styles)
im.initRandom(12)
createAngularScatterBrush('AScatter04', 'T09 A Scatter 04', 
    sourceFileName, 'shape', 1, 30, 1000, 1000, 100, 100, 0.01, 
    cg.Range(20., 30.), cg.Range(0.6, 1.), 1., 1., 1., styles)
im.initRandom(122)
createAngularScatterBrush('AScatter05', 'T10 A Scatter 05', 
    sourceFileName, 'shape', 1, 10, 1000, 1000, 100, 100, 0.01, 
    cg.Range(40., 60.), cg.Range(0.2, 1.), 1., 1., 1., styles)
im.initRandom(3)
createAngularScatterBrush('AScatter06', 'T11 A Scatter 06', 
    sourceFileName, 'shape', 1, 150, 1000, 1000, 100, 100, 0.01, 
    cg.Range(20., 70.), cg.Range(0.3, 1.), 1., 1., 1., styles)

im.disposeRandom()

print "All done!"
