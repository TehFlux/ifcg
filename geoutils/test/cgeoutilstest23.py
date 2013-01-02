#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print "Testing scatter LUT generation..."

# General setup.

im.initRandom(16)

numShapes = 400
numEntries = numShapes
radius = 1.5
baseSize = 0.5
scaleMin0 = 0.3
scaleMax0 = 1.
scaleMin1 = 0.1
scaleMax1 = 1.
worldScale = 250.

sphere0 = cg.Sphere3.create()
sphere0.setR(radius)
sphere0.scale(cg.Vector3(1., 1., 0.3))

inFile0 = 'test' + os.path.sep + 'images' + os.path.sep + 'leaf01.svg'
outFile0 = 'temp' + os.path.sep + 'scatter01.svg'

# Generate some SVG styles.

numColors = 169
colors = []
vMin = 0.2
vMax = 1.0
hMin = 0.
hMax = 1.
l0 = math.sqrt(numColors)
dv = (vMax - vMin) / (l0 - 1)
dh = (hMax - hMin) / (l0 - 1)
c1 = ai.FloatColor()
c1.c0 = hMin
c1.c1 = 0.7
c1.c2 = vMin
c1.alpha = 0.7
c1.space = ai.Color.SPACE_HSV
for i in xrange(0, int(l0)):
    c1.c2 = vMin
    for j in xrange(0, int(l0)):
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
        colors += [[cSpec, c2.alpha]]
        c1.c2 += dv
    c1.c0 += dh
styles = cg.SVGShapeStyleVector()
for c in colors:
    #print "  " + c
    styles.push_back(cg.getSVGShapeStyle(c[0], c[1], "#000000", 1., 0.))

def createArrow(polygonSet = None, length = 250., width = 4., 
    headLength = 25., headWidth = 4., headInset = 5.):
    """Create an arrow polygon."""
    if (not polygonSet is None):
        p0 = polygonSet.addPolygon();
    else:
        p0 = cg.Polygon3()
    verts = []
    for i in xrange(0, 7):
        verts += [p0.addVertex()]
    verts[0].setCoords(cg.Vector3(0., 0.5 * width, 0.))
    verts[1].setCoords(cg.Vector3(0., -0.5 * width, 0.))
    verts[2].setCoords(cg.Vector3(length - headLength + headInset, 
        -0.5 * width, 0.))
    verts[3].setCoords(cg.Vector3(length - headLength, 
        -0.5 * width * headWidth, 0.))
    verts[4].setCoords(cg.Vector3(length, 0., 0.))
    verts[5].setCoords(cg.Vector3(length - headLength, 
        0.5 * width * headWidth, 0.))
    verts[6].setCoords(cg.Vector3(length - headLength + headInset, 
        0.5 * width, 0.))
    return p0

def createVecRotZ(v):
    """Create rotation matrix for a vector in the XY-Plane."""
    phi = v.angle(cg.Vector3.E_X)
    if (v[1] < 0.):
        phi *= -1;
    ## <---- DEBUG ----- 
    #print ("[createVecRotZ] DEBUG: v = " + str(v) + ", phi = " + str(phi) 
    #    + " (" + str(phi * 180. / math.pi) + "°)")
    ## ----- DEBUG ---->
    return cg.Matrix4.rotate(phi, cg.AXIS_Z)

def createVecArrow(v, polygonSet = None, width = 4., 
    headLength = 25., headWidth = 4., headInset = 5., o = None):
    """Create an arrow polygon for a vector."""
    vp = cg.Vector3(v)
    vp.setX2(0.)
    m = createVecRotZ(vp)
    if (not o is None):
        t = cg.Matrix4.translate(o[0], o[1])
        m = t * m
    p = createArrow(None, vp.norm(), width, headLength, headWidth, headInset)
    p.transform(m)
    if (not polygonSet is None):
        p.thisown = 0
        polygonSet.addPolygon(p)
    return p

def createPolyArrows(p, polygonSet, width = 4., 
    headLength = 25., headWidth = 4., o = None):
    """Create arrows for a polygon."""
    for i in xrange(0, p.getNumEdges()):
        e = p.getEdge(i)
        v0 = p.getVertex(e.getV0()).getVector()
        v1 = p.getVertex(e.getV1()).getVector()
        createVecArrow(v1 - v0, polygonSet, o = v0)

def createCubePoly(l = 400.):
    """Create polygon for a cube."""
    s = 0.5 * l;
    ev = [
        cg.Vertex3(-s, -s, -s), 
        cg.Vertex3(s, -s, -s), 
        cg.Vertex3(s, s, -s), 
        cg.Vertex3(-s, s, -s), 
        cg.Vertex3(-s, -s, s), 
        cg.Vertex3(s, -s, s), 
        cg.Vertex3(s, s, s), 
        cg.Vertex3(-s, s, s)
    ]
    p = cg.Polygon3()
    for v in ev:
        v.thisown = 0
        p.addVertex(v)
    edges = [
        [0, 4], [1, 5], [2, 6], [3, 7], 
        [4, 5], [5, 6], [6, 7], [7, 4], 
        [0, 1], [1, 2], [2, 3], [3, 0]
    ]
    for e in edges:
        ex = p.addEdge()
        ex.setV0(e[0])
        ex.setV1(e[1])
    return p

def randomR(rMin = 0., rMax = 2. * math.pi, axis = cg.AXIS_Z):
    """Create random rotation matrix."""
    phi = im.getRandomDouble() * (rMax - rMin) + rMin
    return cg.Matrix4.rotate(phi, axis)

def randomS(rMin = 0.05, rMax = 2.):
    """Create random scale matrix."""
    s = im.getRandomDouble() * (rMax - rMin) + rMin
    return cg.Matrix4.scale(s, s, s)

print "  Creating scatter LUT..."

# Create a LUT containing random translation vectors.

lut0 = cg.Scatter.createLUT(numEntries, cg.Vector3(2., 2., 2.), 
    cg.Vector3.ZERO, sphere0)

#for i in xrange(0, numEntries):
#    v0 = lut0(float(i) / (numEntries - 1))
#    print ("    %03d: " % i) + str(v0) + ", " + str(v0.norm())

# Load a shape.

print "  Loading base shape..."

n0 = ag.LoadSVG()
n0.setFileName(inFile0)
n0.addElementID('leaf01')
n0.update()
g0 = n0.getOutput(0)

ps0 = cg.Polygon3Set()
ps0.addPolygon(cg.Polygon3.upcast(g0.getItem(0)))
ps0.center()
ps0.normalize()
ps0.scale(cg.Vector3(baseSize, baseSize, baseSize))
ps0.applyTransform(True)

#p0 = ps0.getPolygon(0)
#print "    " + str(p0)

print "  Creating transformed duplicates..."

ps1 = cg.Polygon3Set()
sr0 = cg.Range(scaleMax0, scaleMin0)
for i in xrange(0, numShapes):
    v0 = lut0(float(i) / (numShapes - 1))
    m2 = cg.Matrix4.translate(v0)
    s0 = sr0.getValue(v0.norm() / radius)
    m3 = cg.Matrix4.scale(cg.Vector3(s0, s0, s0))
    m4 = (m2 * randomR(axis = cg.AXIS_X) 
        * randomR(axis = cg.AXIS_Y) 
        * randomR(axis = cg.AXIS_Z) 
        * randomS(scaleMin1, scaleMax1)
        * m3)
    ps0t = cg.Polygon3Set(ps0)
    ps0t.transform(m4)
    ps0t.applyTransform()
    ps1.addPolygons(ps0t)

#for i in xrange(0, ps1.getNumPolygons()):
#    p0 = ps1.getPolygon(i)
#    print ("    %03d: " % i) + str(p0)

print "  Setting up view and image transform matrix..."
rotZ = -30. * math.pi / 180.
rotX = -35. * math.pi / 180.
#rotZ = 0.
#rotX = 0.
RX = cg.Matrix4.rotate(rotX, cg.AXIS_X)
RZ = cg.Matrix4.rotate(rotZ, cg.AXIS_Z)
R = RZ * RX
distance = 2000.
tv = cg.mult3(distance, R.getM3x3() * cg.Vector3.E_Y)
T = cg.Matrix4.translate(tv.flip())
d = 50.
P = cg.Matrix4.perspective(d, cg.AXIS_Y)
TR = T * R
TRInv = TR.invert()
V = P * TRInv
PC = cg.Matrix4(
    1., 0., 0., 0., 
    0., 0., 1., 0., 
    0., 1., 0., 0., 
    0., 0., 0., 1.
)
I = PC * cg.Matrix4.scale(40., 1., 40.)

print "  Transforming polygons..."
ps2 = cg.Polygon3Set(ps1)
ps2.scale(cg.Vector3(worldScale, worldScale, worldScale))
ps2.transformVI(V, I)
ps2.applyTransform()

print "  Transforming axis vectors..."
# These need to be transformed separately because the vector arrows are 
# genereted in the XY plane and are not truly 3D (think billboards).
x0 = cg.mult3(100., cg.Vector3.E_X)
y0 = cg.mult3(100., cg.Vector3.E_Y)
z0 = cg.mult3(100., cg.Vector3.E_Z)
xtv0 = cg.Vertex3(x0)
xt0 = xtv0.transformVI(V, I).getVector()
#xt0 = xtv0.getVector()
ytv0 = cg.Vertex3(y0)
yt0 = ytv0.transformVI(V, I).getVector()
#yt0 = ytv0.getVector()
ztv0 = cg.Vertex3(z0)
zt0 = ztv0.transformVI(V, I).getVector()
#zt0 = ztv0.getVector()

print "  Transforming cube edge vectors..."
# These need to be transformed separately because the vector arrows are 
# genereted in the XY plane and are not truly 3D (think billboards).
cp0 = createCubePoly()
cpt0 = cg.Polygon3(cp0)
cpt0.transformVI(V, I)
cpt0.applyTransform()

vecs = [
    xt0, yt0, zt0
]
for v in vecs:
    createVecArrow(v, ps2)
createPolyArrows(cpt0, ps2)
#print "  ps2 = " + str(ps2)
#for i in xrange(0, ps2.getNumPolygons()):
#    px0 = ps2.getPolygon(i)
#    print ("    %03d: " % i) + str(px0)

ps2.writeSVG(outFile0, styles, "polygon", cg.AXIS_Z)

print "All done!"
