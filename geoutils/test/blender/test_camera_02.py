import IFObjectBase as ib
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.utils as bgu
import BGeoUtils.Data as bgd
import BGeoUtils.Object as bgo
import BGeoUtils.Material as bgm
import BGeoUtils.Camera as bgc
import math as m
import bpy

# This is a snippet to extract the extrinsic camera matrix from a 
# Blender camera.

# memory management
mm = ib.IFObject()

cm0 = cg.Matrix4.create()
mm.addLocalRef(cm0)

bCam0 = bpy.data.objects.get("Camera")
bgu.getCGMatrix(bCam0.matrix_world, cm0)

print(cm0.getValueStringF(10, 3, ",", ",\n"))

print(cm0.invert().getValueStringF(10, 3, ",", ",\n"))

