# -*- coding: utf-8 -*-
"""Blender GeoUtils test 02"""

import IFMapping as im
import IFObjectBase as ib
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo
import BGeoUtils.Material as bgMat
import BGeoUtils.utils as bgu
import CGeoUtils as cg

tolerance = 1e-5

m0 = bgm.Mesh('Cube2')
m1 = bpy.data.meshes.get('Cube')
m0.setFromBMesh(m1)

m2 = m0.cgMesh
m2.update()
numFaces = m2.getNumFaces()
steps = 10000
im.initRandom()
nonPlanar = numFaces
i = 0
#dp = 0.01
#p = dp
p = 1.
while ((i < steps) and (nonPlanar > 0)):
    #p0 = p * im.getRandomDouble()
    f0 = m2.getFace(im.getRandomInt() % numFaces)
    f0.makePlanar(p, tolerance)
    #m2.update()
    nonPlanar = 0
    for k in range(0, numFaces):
        f0 = m2.getFace(k)
        f0.update()
        if (not f0.isPlanar(tolerance)):
            nonPlanar += 1
    i += 1
    #p += dp
    #if (p > 1.):
    #    p = 1.

print("Non-planar faces remaining after %d steps: %d" % (i, nonPlanar))

m2.update()

m3 = bgm.Mesh("Cube2M", m2, True)
o0 = bgo.Object("Cube2", m3, True)
o0.setLocation(cg.Vector3(3., 0., 0.))

im.disposeRandom()
