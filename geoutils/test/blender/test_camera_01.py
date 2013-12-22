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

# memory management
mm = ib.IFObject()

#bCamMatrix0 = cg.Matrix4.create(
#    0.877905, -0.402871, -0.258800, -0.405134, 
#    -0.235215, 0.107940, -0.965931, -6.170712, 
#    0.417080, 0.908870, -0.000001, 0.405135, 
#    0.000000, 0.000000, 0.000000, 1.000000)

bCamMatrix0 = cg.Matrix4.create()
mm.addLocalRef(bCamMatrix0)

bCam0 = bpy.data.objects.get("Camera")
bgu.getCGMatrix(bCam0.matrix_world, bCamMatrix0)
#cam0.matrix_world = bgu.getBlenderMatrix(
#    bCamMatrix0.transpose())

print(bCamMatrix0.getValueStringF(10))

m0 = cg.Matrix3.create()
mm.addLocalRef(m0)
m0.setElements(bCamMatrix0)
print(m0.getValueStringF(10))

t0 = cg.Vector3.create()
mm.addLocalRef(t0)
bCamMatrix0.getCol(3, t0)
print(t0.getValueString())

bgu.visualizeTransform(m0, t0, "CameraT")

cgCam0 = cg.Camera.create()
mm.addLocalRef(cgCam0)

bgCam0 = bgc.Camera(cgCam0)
bgCam0.setFromBCamera(bCam0)

print(cgCam0.getString())

#m2 = cgCam0.getModelViewMatrix()

#print("CG camera model/view matrix:")
#print(m2.getValueStringF(10))

m3 = cgCam0.getExtrinsicMatrix()

print("CG camera extrinsic matrix:")
print(m3.getValueStringF(10))

m1 = cg.Matrix3.create()
mm.addLocalRef(m1)
m1.setElements(m3)
print(m1.getValueStringF(10))

#t1 = cg.Vector3.create()
#mm.addLocalRef(t1)
#m2.getCol(3, t1)
#print(t1.getValueString())
t1 = cg.Vector3.ZERO

bgu.visualizeTransform(m1, t1, "CGCameraET")

