# -*- coding: utf-8 -*-
"""Blender GeoUtils test 03"""

import IFMapping as im
import IFObjectBase as ib
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo
import BGeoUtils.Material as bgMat
import BGeoUtils.utils as bgu
import CGeoUtils as cg

tolerance = 1e-5

m0 = bgm.Mesh('Cube')
m1 = bpy.data.meshes.get('Cube')
m0.setFromBMesh(m1)

m2 = m0.cgMesh
m2.update()
numFaces = m2.getNumFaces()
steps = 10000
faces0 = ib.UIntVector()
for i in range(0, numFaces):
    faces0.push_back(i)

p = 1.
nonPlanar = m2.makePlanar(faces0, steps, p, tolerance)

print("Non-planar faces remaining : %d" % (nonPlanar))

m0.update()

