# -*- coding: utf-8 -*-
"""Blender GeoUtils test 01"""

import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo
import BGeoUtils.Material as bgMat
import BGeoUtils.utils as bgu
import CGeoUtils as cg

m0 = cg.Matrix3(cg.Matrix3.UNIT)
t0 = bgu.visualizeTransform(m0, name = "T0")


m0 = bgm.Mesh('Icosphere')
m1 = bpy.data.meshes.get('Icosphere')
m0.setFromBMesh(m1)
vs0 = m0.cgMesh.getVertexSource()
pca0 = vs0.getPCABase()
t0 = bgu.visualizeTransform(pca0, name = "PCA0")

