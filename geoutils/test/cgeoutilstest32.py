#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import CGeoUtils as cg
import Altjira as ai

print("Testing GeoUtils...")

outFile0 = 'temp' + os.path.sep + 'bbox01.svg'
outFile1 = 'temp' + os.path.sep + 'bbox01.bbox'
outFile2 = 'temp' + os.path.sep + 'bbox01a.bbox'
imageWidth = 1024
imageHeight = 768
imageScale = imageWidth
numStyles = 20

# Same vertices as in test01.js
vertices = [
    [ 0.607415641887, 0.718705489141, -0.225119709644 ],
    [ 0.875825333637, -0.0573853653933, 0.202470894686 ],
    [ 0.0622396542542, 0.833795337589, -0.594071825809 ],
    [ 0.0978927338215, -0.938852215553, -0.978846042241 ],
    [ 0.0728408015356, -0.00997117308592, 0.775148271791 ],
    [ -0.698258593952, -0.548446195445, -0.938418659592 ],
    [ -0.963365750832, -0.300554008166, -0.00954516618162 ],
    [ -0.23397952826, -0.632782192171, 0.314228963344 ],
    [ -0.0362186111467, -0.881106809054, 0.196295037355 ],
    [ -0.494240109345, -0.637551388716, -0.504403922825 ],
    [ 0.567796144827, 0.891323063435, 0.646969860611 ],
    [ 0.398703185601, 0.221126849291, 0.563951443381 ],
    [ -0.230592732479, 0.207860506282, 0.550936374027 ],
    [ -0.0203087267027, 0.828140936686, -0.0113749638823 ],
    [ -0.12589991174, 0.39163333572, -0.967737855772 ],
    [ -0.896956271477, 0.501435268487, 0.881099725261 ],
    [ 0.919674754078, 0.768222708852, -0.325443420918 ],
    [ 0.96884639734, -0.111784368895, 0.708906705091 ],
    [ 0.993587035364, -0.974822676713, -0.562923045724 ],
    [ 0.116054844554, -0.423830262697, -0.321361680489 ]
]

def getBoxStyle(box, styles, step = 7):
    """Get style for a bounding box."""
    level = box.getLevel()
    return styles[(level * step) % len(styles)]

def getBoxPolygons(box, ps0):
    """Get polygons for a box."""
    g0 = cg.TransformableGroup()
    c0 = cg.Mesh.cube()
    g0.addItem(c0)
    # Mesh has radius vector (0.5, 0.5, 0.5), so scale it by twice the box 
    # radius vector.
    c0.scale(box.getRVec() * 2.)
    c0.translate(box.getCenter())
    c0.applyTransform()
    c0.getPolygons(ps0)
    c0 = None
    g0 = None

def setItemIDs(box):
    """Set item IDs for bounding boxes."""
    items = cg.BoundingBoxSet()
    box.getBoundingBoxes(items)
    i = 0
    for it in items:
        it.setItemID("bbox%03d" % i)
        i += 1

def addBoxPolygonsAndStyles(box, styles0, src0, ps0, level = None):
    """Recursively add box polygons and styles."""
    items = cg.BoundingBoxSet()
    box.getBoundingBoxes(items)
    for it in items:
        if ((level is None) 
            or (level == it.getLevel())):
            ps0x = cg.Polygon3Set()
            getBoxPolygons(it, ps0x)
            s0 = getBoxStyle(it, styles0)
            for i in range(0, ps0x.getNumPolygons()):
                src0.addStyle(s0)
            ps0.addPolygons(ps0x)

def getVertexPolygon(v0, ps0, scale = 0.02):
    """Get polygon for a vertex."""
    c0 = cg.Polygon3.circle()
    c0.scale(cg.Vector3(scale, scale, scale))
    c0.translate(cg.Vector3(v0.getX(), v0.getY(), v0.getZ()))
    ps0.addPolygon(c0)

def getVertexStyle(v0, styles, zMin = -1., zMax = 1.):
    """Get style for a vertex."""
    z = v0.getY()
    return styles[int((z - zMin) / (zMax - zMin) * (len(styles) - 1))]

print("  Creating styles...")

colors = ai.ColorObjVector()
c0 = ai.createFloatColor(0.0, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
c1 = ai.createFloatColor(0.8, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
ai.createColors(colors, c0, c1, numStyles, 1, 1)
numColors = colors.size()

styles = []
styles2 = []
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
    #print(("    c%02d = " % i) + ch0)
    s0 = cg.getSVGShapeStyle("none", 0., ch0[:7], c.getAlpha(), 1.)
    s1 = cg.getSVGShapeStyle(ch0[:7], c.getAlpha(), "#000000", 0., 0.)
    styles += [s0]
    styles2 += [s1]
    ## Add styles later.
    #styleSource.addStyle(s0)

print("  Creating bounding box...")
bb0 = cg.BoundingBox()
print(str(bb0))

print("  Creating vertices...")
vs0 = cg.Vertex3Set()
for v in vertices:
    vs0.addVertex(cg.Vertex3.create(v[0], v[1], v[2]))
# Additional vertices to make the box (double) unit size.
vs0.addVertex(cg.Vertex3.create(1., 1., 1.))
vs0.addVertex(cg.Vertex3.create(-1., -1., -1.))

for i in range(0, vs0.getNumVertices()):
    v0 = vs0.getVertex(i)
    bi0 = cg.BoxBoundsItem.create()
    bi0.setItemID("vertex%02d" % (i + 1))
    bi0.setCenter(v0.getVector())
    bi0.setRVec(cg.Vector3.ZERO)
    bi0.updateBounds()
    bb0.addItem(bi0)

print(str(bb0))

print("  Creating splits...")
sp0 = cg.SplitSet()
sp0.addSplits(cg.AXIS_X, 3)
sp0.addSplits(cg.AXIS_Y, 3)
sp0.addSplits(cg.AXIS_Z, 3)

print("  Splitting bounding box...")
bb0.split(sp0, True, 4, 0, 0, cg.DEFAULT_TOLERANCE, True)
print("  Setting item IDs...")
setItemIDs(bb0)

print("  Creating bounding box polygons and styles...")
ps0 = cg.Polygon3Set()
addBoxPolygonsAndStyles(bb0, styles, styleSource, ps0)

print("  Creating camera...")
cam0 = cg.Camera()
cam0.setLens(35.)
cs0 = cg.CameraSetupFlags()
cs0.useDirection = True
cs0.useRight = True
cs0.useUp = True
cs0.useLookAt = False
cs0.useSky = True
cs0.useAngle = False
cs0.useLens = True
cam0.setOriginCam(-7., -30., 0., 30.)
cam0.validate(cs0)
V = cam0.getViewMatrix()
I = cg.Matrix4.scale(imageScale, imageScale, imageScale)

print("  Transforming bounding box polygons...")
ps0.transformVI(V, I)
ps0.applyTransform()

print("  Creating grid polygons...")
ps1 = cg.Polygon3Set()
sq0 = cg.Polygon3.square()
sq0.scale(cg.Vector3(imageWidth, 1., 1.))
sq1 = cg.Polygon3.square()
sq1.scale(cg.Vector3(1., 1., imageHeight))
sq1.translate(cg.Vector3(0.5, 0., 0.))
ci0 = cg.Polygon3.circle(100)
ci0.scale(cg.Vector3(0.4 * imageWidth, 1., 0.4 * imageWidth))
ci1 = cg.Polygon3.circle(100)
ci1.scale(cg.Vector3(0.1 * imageWidth, 1., 0.1 * imageWidth))

print("  Creating vertex styles...")
for i in range(0, vs0.getNumVertices()):
    v0 = vs0.getVertex(i)
    s0 = getVertexStyle(v0, styles2)
    styleSource.addStyle(s0)

print("  Transforming vertices...")
vs0.transformVI(V, I)
vs0.applyTransform()

print("  Creating vertex polygons...")
ps2 = cg.Polygon3Set()
for i in range(0, vs0.getNumVertices()):
    v0 = vs0.getVertex(i)
    getVertexPolygon(v0, ps2, 0.01 * imageScale)

ps1.addPolygon(sq0)
ps1.addPolygon(sq1)
ps1.addPolygon(ci0)
ps1.addPolygon(ci1)
ps1.addPolygons(ps0)
ps1.addPolygons(ps2)

print("  Rendering to image '" + outFile0 + "'...")
ip0 = cg.SVGImageProperties()
ip0.setFileName(outFile0)
ip0.setStyleSource(styleSource)
ip0.setWidth(imageWidth)
ip0.setHeight(imageHeight)
ip0.setOrigin(cg.Vector2(imageWidth / 2, imageHeight / 2))
ps1.writeSVG(ip0, "polygon", cg.AXIS_Y)

print("  Writing XML to '" + outFile1 + "'...")
bb0.writeToFile(outFile1)

bb1 = cg.BoundingBox()
cg.getBoundingBox(outFile1, 'bbox000', bb1)

print("  Writing XML to '" + outFile2 + "'...")
bb1.writeToFile(outFile2)

print("All done!")
