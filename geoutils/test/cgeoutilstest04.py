#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math, sys
import CGeoUtils as cg

COLORS = [
    '#20e045', 
    '#20e0c7', 
    '#207be0', 
    '#5b20e0', 
    '#de20e0', 
    '#e0206b', 
    '#e02020', 
    '#e07320', 
    '#e0da20', 
    '#87e020'
]

def getSVGAttrs(color = 0):
    if (color >= len(COLORS)):
        color = color % len(COLORS)
    if (color == 0):
        return cg.SVG_DEFAULT_POLY_STYLE
    return cg.SVG_DEFAULT_POLY_STYLE.replace('#20e045', COLORS[color])

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
I = PC * cg.Matrix4.scale(50., 1., 50.)
print "RX         = " + str(RX)
print "RZ         = " + str(RZ)
print "R          = " + str(R)
print "T          = " + str(T)
print "P          = " + str(P)
print "TRInv      = " + str(TRInv)
print "TR * TRInv = " + str(TR * TRInv)
print "V          = " + str(V)
print "I          = " + str(I)

print "Transforming axis vectors..."
x0 = cg.mult3(100., cg.Vector3.E_X)
y0 = cg.mult3(100., cg.Vector3.E_Y)
z0 = cg.mult3(100., cg.Vector3.E_Z)
xtv0 = cg.Vertex3(x0)
xt0 = xtv0.transformVI(V, I).getVector()
ytv0 = cg.Vertex3(y0)
yt0 = ytv0.transformVI(V, I).getVector()
ztv0 = cg.Vertex3(z0)
zt0 = ztv0.transformVI(V, I).getVector()
print "xt0 = " + str(xt0)
print "yt0 = " + str(yt0)
print "zt0 = " + str(zt0)

print "Transforming cube edge vectors..."
cp0 = createCubePoly()
cpt0 = cg.Polygon3(cp0)
cpt0.transformVI(V, I)

ps0 = cg.Polygon3Set()
vecs = [
    xt0, yt0, zt0
]
for v in vecs:
    createVecArrow(cg.Vector3(v), ps0)
cpt0.applyTransform()
createPolyArrows(cpt0, ps0)

svg = cg.SVG_DEFAULT_HEADER
for i in xrange(0, ps0.getNumPolygons()):
    p = ps0.getPolygon(i)
    svg += p.getSVG(getSVGAttrs(2 * i), "vector%03d" % i, cg.AXIS_Z)
svg += cg.SVG_DEFAULT_FOOTER
f = open('temp' + os.path.sep + "vectors03.svg", 'w')
f.write(svg)
f.close()

print "All done!"
