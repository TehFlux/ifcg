#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import IFObjectBase as ob
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
    if (color > len(COLORS)):
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
    headLength = 25., headWidth = 4., headInset = 5.):
    """Create an arrow polygon for a vector."""
    m = createVecRotZ(v)
    p = createArrow(None, v.norm(), width, headLength, headWidth, headInset)
    p.transform(m)
    #p.applyTransform()
    if (not polygonSet is None):
        p.thisown = 0
        polygonSet.addPolygon(p)
    return p

print "Testing 2D vectors..."
ps0 = cg.Polygon3Set()
d0 = ob.DoubleVector()
d0.push_back(-100.)
d0.push_back(350.)
v00 = cg.Vector2(220., 110.)
v01 = cg.Vector2(d0)
vecs = [
    v00, v01, 
    v00.flip(), cg.mult2(50., v00.normalize()), v00.project(v01), 
    v00.ortho(v01), v00.swap(), v00 + v01, 
    cg.mult2(100., cg.Vector2.axis(cg.AXIS_X)), 
    cg.mult2(100., cg.Vector2.axis(cg.AXIS_Y))
]
for v in vecs:
    createVecArrow(cg.Vector3(v), ps0)
svg = cg.SVG_DEFAULT_HEADER
for i in xrange(0, ps0.getNumPolygons()):
    p = ps0.getPolygon(i)
    svg += p.getSVG(getSVGAttrs(i), "vector%03d" % i, cg.AXIS_Z)
svg += cg.SVG_DEFAULT_FOOTER
f = open('temp' + os.path.sep + "vectors01.svg", 'w')
f.write(svg)
f.close()

print "Testing 2D transformations..."
ps1 = cg.Polygon3Set()
v10 = cg.Vector2(220., 110.)
m10 = cg.Matrix2.rotate(math.pi * 1.45);
m11 = cg.Matrix2.scale(0.5, 0.5);
m12 = m10.invert()
print "  m10   = " + str(m10)
print "  m11   = " + str(m11)
print "  m12   = " + str(m12)
print "  m10.T = " + str(m10.transpose())
vt10 = m10 * v10
vt11 = m11 * vt10
vt12 = m12 * vt11
vecs = [
    v10, vt10, vt11, vt12
]
for v in vecs:
    createVecArrow(cg.Vector3(v), ps1)
svg = cg.SVG_DEFAULT_HEADER
for i in xrange(0, ps1.getNumPolygons()):
    p = ps1.getPolygon(i)
    svg += p.getSVG(getSVGAttrs(i), "vector%03d" % i, cg.AXIS_Z)
svg += cg.SVG_DEFAULT_FOOTER
f = open('temp' + os.path.sep + "vectors02.svg", 'w')
f.write(svg)
f.close()

print "All done!"
