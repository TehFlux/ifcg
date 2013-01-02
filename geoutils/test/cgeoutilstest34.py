#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test 34."""
import math, os
import IFObjectBase as ib
import CGeoUtils as cg
import Altjira as ai
import AltjiraGeoUtils as ag

print("CGeoUtils test 34.")

# memory management
mm = ib.IFObject()

v0 = cg.Voxel(cg.Vector3(0, 4, 0), 1, cg.Vector3(0.5, 0.5, 0))
print(v0.getString())

l0 = cg.Line3()
l0.setU(cg.Vector3(1, 1, 0))
print(l0.getString())

pv0 = v0.getBoxFaces()
p0 = pv0[3]
pl0 = p0.getPlane()

print(p0.getString())
print(pl0.getString())

ip0 = cg.Vector3()
l0.intersectPlane(pl0, ip0)

print("intersection point: " + ip0.getString())

tm0 = pl0.getTangentBase()
tmInv = tm0.invert()

print("tangent base:     " + tm0.getString())
print("tangent base inv: " + tmInv.getString())

tp0 = cg.Polygon3(p0)
ov0 = tp0.getVertex(0).getVector()
tp0.translate(ov0.flip())
tp0.transform(tmInv)
tp0.applyTransform()

ip1 = cg.Vector3(ip0)
ip1 = tmInv * (ip1 + ov0.flip())

print("polygon in tangent space:            " + tp0.getString())
print("intersection point in tangent space: " + ip1.getString())

#tp1 = cg.Polygon2()
#tp0.getPolygon2(tp1)

print("intersection in poly: " + str(l0.intersectionInPoly(p0)))

print("All done!")
