#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import CGeoUtils as cg

def createArrow(polygonSet = None, length = 250., width = 4., 
    headLength = .1, headWidth = 4.):
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
    verts[2].setCoords(cg.Vector3((1. - headLength) * length, 
        -0.5 * width, 0.))
    verts[3].setCoords(cg.Vector3((1. - headLength) * length, 
        -0.5 * width * headWidth, 0.))
    verts[4].setCoords(cg.Vector3(length, 0., 0.))
    verts[5].setCoords(cg.Vector3((1. - headLength) * length, 
        0.5 * width * headWidth, 0.))
    verts[6].setCoords(cg.Vector3((1. - headLength) * length, 
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
    headLength = .1, headWidth = 4.):
    """Create an arrow polygon for a vector."""
    m = createVecRotZ(v)
    p = createArrow(None, v.norm(), width, headLength, headWidth)
    p.transform(m)
    #print ("[createVecArrow] DEBUG: m = " + str(m) + ", p = " + str(p) 
    #    + ", p.transformMatrix = " + str(p.getTransformMatrix()))
    #p.applyTransform()
    #print ("[createVecArrow] DEBUG: p = " + str(p) 
    #    + ", p.transformMatrix = " + str(p.getTransformMatrix()))
    if (not polygonSet is None):
        p.thisown = 0
        polygonSet.addPolygon(p)
    return p

def createPolygon01(polygonSet = None):
    """Create sample polygon 01."""
    if (not polygonSet is None):
        p = polygonSet.addPolygon()
    else:
        p = cg.Polygon3()
    verts = []
    for i in xrange(0, 5):
        verts += [p.addVertex()]
    verts[0].setCoords(cg.Vector3(65., 285., 0.))
    verts[1].setCoords(cg.Vector3(217., 154., 0.))
    verts[2].setCoords(cg.Vector3(165., -51., 0.))
    verts[3].setCoords(cg.Vector3(-65., -88., 0.))
    verts[4].setCoords(cg.Vector3(-102., 140., 0.))
    return p

print "Creating arrow polygon..."
ps0 = cg.Polygon3Set()
p0 = createArrow(ps0)

print "Creating rotation matrix..."
m0 = cg.Matrix4.rotate(0.5 * math.pi, cg.AXIS_Z)
print "  m0 = " + str(m0)

print "Testing vector transformation..."
xt0 = m0 * cg.Vector4.E_X
yt0 = m0 * cg.Vector4.E_Y
zt0 = m0 * cg.Vector4.E_Z
print "  m0 * E_X = " + str(xt0)
print "  m0 * E_Y = " + str(yt0)
print "  m0 * E_Z = " + str(zt0)

print "Testing vertex transformation..."
v00 = cg.Vertex3(cg.Vector3.E_X)
v01 = cg.Vertex3(cg.Vector3.E_Y)
v02 = cg.Vertex3(cg.Vector3.E_Z)
v00.transform(m0)
v01.transform(m0)
v02.transform(m0)
print "  m0 * v00 = " + str(v00)
print "  m0 * v01 = " + str(v01)
print "  m0 * v02 = " + str(v02)

print "Testing polygon transformation (single)..."
pt1 = p0.duplicate()
pt1.transform(m0)
ps0.addPolygon(pt1)

print "Testing polygon transformation (bulk)..."
ps1 = cg.Polygon3Set(ps0)
ps1.transform(m0)

print "Creating rotation matrix from vector..."
ps2 = cg.Polygon3Set()
v10 = cg.Vector3(150., 280., 0.)
v11 = v10.flip()
m10 = createVecRotZ(v10)
m11 = createVecRotZ(v11)
print "  v10 = " + str(v10)
print "  m10 = " + str(m10)
print "  v11 = " + str(v11)
print "  m11 = " + str(m11)
createVecArrow(v10, ps2)
createVecArrow(v11, ps2)

print "Testing translate/rotate/scale matrices..."
ps3 = cg.Polygon3Set()
T = cg.Matrix4.translate(50., 180., 0.)
R = cg.Matrix4.rotate(0.65 * math.pi, cg.AXIS_Z)
S = cg.Matrix4.scale(.4, .4, .4)
p20 = createPolygon01(ps3)
RS = cg.Matrix4(R * S)
TRS = cg.Matrix4(T * RS)
pt20 = p20.duplicate()
pt20.transform(S)
pt21 = p20.duplicate()
pt21.transform(RS)
pt22 = p20.duplicate()
pt22.transform(TRS)
ps3.addPolygon(pt20)
ps3.addPolygon(pt21)
ps3.addPolygon(pt22)

print "Creating SVG file..."
ps0.writeSVG('temp' + os.path.sep + "arrows01.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "arrow", cg.AXIS_Z)
ps1.writeSVG('temp' + os.path.sep + "arrows02.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "arrow", cg.AXIS_Z)
ps2.writeSVG('temp' + os.path.sep + "arrows03.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "arrow", cg.AXIS_Z)
ps3.writeSVG('temp' + os.path.sep + "polygons02.svg", 
    cg.SVG_DEFAULT_POLY_STYLE, "arrow", cg.AXIS_Z)

print "All done!"
