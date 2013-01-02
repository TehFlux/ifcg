#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math, random
import CGeoUtils as cg

random.seed(3)

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
    phi = random.random() * (rMax - rMin) + rMin
    return cg.Matrix4.rotate(phi, axis)

def randomS(rMin = 0.05, rMax = 2.):
    """Create random scale matrix."""
    s = random.random() * (rMax - rMin) + rMin
    return cg.Matrix4.scale(s, s, s)

def randomT(rMin = -500., rMax = 500.):
    """Create random translation matrix."""
    tx = random.random() * (rMax - rMin) + rMin
    ty = random.random() * (rMax - rMin) + rMin
    tz = random.random() * (rMax - rMin) + rMin
    return cg.Matrix4.translate(tx, ty, tz)

print "Extracting attribute from SVG file..."
d0 = cg.getAttrValue('test/images/leaf01.svg', 'path', 'leaf01', 'd')
print "  leaf01.d = " + d0

vs0 = cg.Vertex3Set.create()
cg.extractSVGVertices(d0, vs0)
print "  vs0 = " + str(vs0)

print "Creating polygon..."
p0 = cg.Polygon3(vs0)
v0 = p0.getBarycenter()
m0 = cg.Matrix4.translate(v0.flip())
m1 = cg.Matrix4.scale(.1, .1, .1)
p1 = cg.Polygon3(p0)
p1.transform(m1 * m0)
print "  p0 = " + str(p0)
print "  v0 = " + str(v0)
print "  p1 = " + str(p1)

ps0 = cg.Polygon3Set()
p1.thisown = 0
ps0.addPolygon(p1)
p1 = None

ps1 = cg.Polygon3Set()
n0 = 400
#n0 = 0
for i in xrange(0, n0):
    m2 = (randomT(-480., 480) 
        * randomR(axis = cg.AXIS_X) 
        * randomR(axis = cg.AXIS_Y)  
        * randomR(axis = cg.AXIS_Z) 
        * randomS(0.05, 1.8))
    ps0t = cg.Polygon3Set(ps0)
    ps0t.transform(m2)
    ps0t.applyTransform()
    ps1.addPolygons(ps0t)

print "Setting up view and image transform matrix..."
rotZ = -30. * math.pi / 180.
rotX = -35. * math.pi / 180.
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

print "Transforming polygons..."
ps2 = cg.Polygon3Set(ps1)
ps2.transformVI(V, I)
ps2.applyTransform()

print "Transforming axis vectors..."
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

print "Transforming cube edge vectors..."
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

ps0.writeSVG('temp' + os.path.sep + "polygons03.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "polygon", cg.AXIS_Z)
ps1.writeSVG('temp' + os.path.sep + "polygons04.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "polygon", cg.AXIS_Z)
ps2.writeSVG('temp' + os.path.sep + "polygons05.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "polygon", cg.AXIS_Z)

print "All done!"
