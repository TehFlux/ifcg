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

print("Blender camera world matrix:")
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

ypr0 = cgCam0.getEulerAngles()
print("CG camera YPR angles: (%s)" % ypr0.getValueString())

upAxis = cg.AXIS_Z
depthAxis = cg.AXIS_Y
horizonAxis = cg.AXIS_X

yawM0 = cg.Matrix3.create()
yawM0.setElements(cg.Matrix3.rotate(ypr0[0], upAxis))
print("CG camera yaw matrix:")
print(yawM0.getValueStringF(10))

pitchM0 = cg.Matrix3.create()
pitchM0.setElements(cg.Matrix3.rotate(ypr0[1], horizonAxis))
print("CG camera pitch matrix:")
print(pitchM0.getValueStringF(10))

rollM0 = cg.Matrix3.create()
rollM0.setElements(cg.Matrix3.rotate(ypr0[2], depthAxis))
print("CG camera roll matrix:")
print(rollM0.getValueStringF(10))

ypM0 = cg.Matrix3.create()
ypM0.setElements(yawM0 * pitchM0)
print("CG camera yaw/pitch matrix:")
print(ypM0.getValueStringF(10))

yprM0 = cg.Matrix3.create()
yprM0.setElements(ypM0 * rollM0)
print("CG camera yaw/pitch/roll matrix:")
print(ypM0.getValueStringF(10))

mm.addLocalRef(yawM0)
mm.addLocalRef(pitchM0)
mm.addLocalRef(rollM0)
mm.addLocalRef(ypM0)
mm.addLocalRef(yprM0)

m1.setElements(yprM0)
t1.setElements(-2., 0., 0.)

bgu.visualizeTransform(m1, t1, "CGCameraYPR")

rot0 = cgCam0.getRotationMatrix()

print("CG camera rotation matrix:")
print(rot0.getValueStringF(10))

m1.setElements(ypM0)
t1.setElements(2., 0., 0.)

bgu.visualizeTransform(m1, t1, "CGCameraRot")

print("Blender camera world matrix:")
print(bCamMatrix0.getValueStringF(10))

print("CG camera world matrix (Blender):")
m2 = cg.Matrix4.create()
mm.addLocalRef(m2)
bgu.getCGMatrix(bgCam0.getBMatrixWorld(), m2)
m2.transposeIP()
print(m2.getValueStringF(10))

if (bCamMatrix0.eq(m2)):
    print("(***) Matrices are equal.")
else:
    print("(!!!) Matrices are NOT equal!")

