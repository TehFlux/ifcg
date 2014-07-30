#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""GeoUtils/GL test: Viewer #2."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsGL as ggl
import Altjira as ai
import math as m

testName = "Viewer #2"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

checkFPSInterval = 200
mvpMatrix = cg.Matrix4.create(cg.Matrix4.UNIT)
mm.addLocalRef(mvpMatrix)
normalMatrix = cg.Matrix3.create(cg.Matrix3.UNIT)
mm.addLocalRef(normalMatrix)

verts = [
    cg.Vertex3.create(-0.5, -0.433, 0.), 
    cg.Vertex3.create(0.5, -0.433, 0.), 
    cg.Vertex3.create(0., 0.433, 0.)
]

colors = [
    ai.Color.create(1., 0., 0., 1.), 
    ai.Color.create(0., 1., 0., 1.), 
    ai.Color.create(0., 0., 1., 1.)
]

print("Creating viewer...")

viewer = ggl.Viewer.create()
mm.addLocalRef(viewer)
viewer.setID("Viewer01")

viewer.init()
viewer.setWindowTitle("GeoUtils/GL test: %s" % testName)
w = viewer.getWindowWidth()
h = viewer.getWindowHeight()
ar = w / h

print("  %s" % viewer.getString())

## inverse of the extrinsic camera matrix
#mv0 = cg.Matrix4.create(
#    1, 0, 0, 0, 
#    0, 1, 0, 0, 
#    0, 0, 1, -10, 
#    0, 0, 0, 1
#)
# inverse camera matrix from triangle01.blend
# pos = (0, -1, 10)
# rot = (0, 0, -32°)
# fov = 65°
mv0 = cg.Matrix4.create(
     0.848,     -0.53,         0,     -0.53,
      0.53,     0.848,         0,     0.848,
         0,         0,         1,       -10,
         0,         0,         0,         1)
mm.addLocalRef(mv0)

print("  camera inverse extrinsic matrix (triangle01.blend): \n%s" 
    % mv0.getValueStringF(10))

fov = 65.

## have to use the aspect ratio as the half-width of the image plane and 
## also no division by 2 because the value range for OpenGL is [-1, 1], 
## i.e. 2 in total.
#d = ar / (m.tan((fov * m.pi / 180.) / 2.))
d = cg.Camera.angleToD(fov * m.pi / 180, ar, 2.)
near = 1.
far = 20.
pm0 = cg.Matrix4.create(cg.Matrix4.UNIT)
mm.addLocalRef(pm0)
# this is basically the OpenGL projection matrix multiplied by 1/d.
pm0.setElement(cg.AXIS_Z, cg.AXIS_Z, -(far + near) / (d * (far - near)))
pm0.setElement(cg.AXIS_Z, cg.AXIS_W, -2. * far * near / (d * (far - near)))
pm0.setElement(cg.AXIS_W, cg.AXIS_Z, -1. / d)
pm0.setElement(cg.AXIS_W, cg.AXIS_W, 0)

print(("  calculated perspective matrix "
    + "(fov = %f°, near = %f, far = %f): \n%s") 
        % (fov, near, far, pm0.getValueStringF(10)))

mvp0 = cg.Matrix4.create()
mm.addLocalRef(mvp0)
mvp0.setElements(mv0)
mvp0.multiplyLeft(pm0)
s1 = cg.Matrix4.scale(1. / ar, 1., 1., 1.)
mvp0.multiplyLeft(s1)

print("  calculated MVP matrix: \n%s" % mvp0.getValueStringF(10))

print("Creating camera...")

cam0 = cg.Camera.create()
mm.addLocalRef(cam0)
cam0.setOriginCam(10, 60., 0., 10., 
    ar, cg.Camera.angleToD(fov * m.pi / 180, ar), 
    cg.AXIS_Y, cg.AXIS_Z, cg.AXIS_X)

## camera position according to triangle01.blend
#T0 = cg.Matrix4.translate(cg.Vector3(0., -1., 10.))
#R0 = cg.Matrix4.rotate(-32. * m.pi / 180., cg.AXIS_Z)
#CM0 = cg.Matrix4(T0 * R0)
#cam0.setVectors(
#    cg.Vector3.ZERO, 
#    cg.Vector3.E_Z, 
#    cg.Vector3.ZERO, 
#    cg.Vector3(ar, 0., 0.), 
#    cg.Vector3.E_Y, 
#    cg.Vector3.E_Y)
#cam0.setAngle(fov * m.pi / 180.)
#sf0 = cg.Camera.createSetupFlags(True, True, True, False, 
#    True, True, False)
#cam0.setSetupFlags(sf0)
#cam0.transform(CM0)
#cam0.applyTransform()

# this is the recommended way to obtain the MVP matrix
cm0 = cam0.getExtrinsicMatrix()
cmInv0 = cm0.invert()
# scale perspective matrix for OpenGL value ranges
cm2 = cam0.getPerspectiveMatrix(cg.AXIS_Z, near, far, -2.)

angles0 = cam0.getEulerAngles(cg.HANDEDNESS_RIGHT, 
    cg.AXIS_Y, cg.AXIS_Z, cg.AXIS_X) * (180. / m.pi)
cm3 = cam0.getRotationMatrix(cg.HANDEDNESS_RIGHT, 
    cg.AXIS_Y, cg.AXIS_Z, cg.AXIS_X)
cmInv3 = cm3.invert()

mvp2 = cg.Matrix4.create()
mm.addLocalRef(mvp2)
mvp2.setElements(cmInv0)
mvp2.multiplyLeft(cm2)

print("  camera euler angles (YPR): (%s)" % angles0.getValueString())

print("  camera inverse extrinsic matrix: \n%s" 
    % cmInv0.getValueStringF(10))

print("  camera inverse rotation matrix: \n%s" 
    % cmInv3.getValueStringF(10))

print("  camera perspective matrix: \n%s" % cm2.getValueStringF(10))

# another possible way to obtain the MVP matrix
mvp1 = cam0.getModelViewMatrix(cg.Camera.MODE_PERSPECTIVE, 
    cg.Camera.DEFAULT_ADJUST_LOCATION, 
    cg.HANDEDNESS_RIGHT, cg.AXIS_Y, cg.AXIS_Z, cg.AXIS_X, 
    near, far, -2.)

print("  camera MVP matrix: \n%s" % mvp1.getValueStringF(10))

print("  camera calculated MVP matrix: \n%s" % mvp2.getValueStringF(10))

# mvp0, mvp1, mvp2 should all have the same effect
mvpMatrix.setElements(mvp1)
normalMatrix.setElements(mvp1.invert().transpose())

print("  using MVP matrix: \n%s" % mvpMatrix.getValueStringF(10))

print("Initializing shaders...")

p0 = ggl.Program()
p0.init()
p0.use()

print("Initializing uniforms...")

p0.setUniform("ifvgMVPMatrix", mvpMatrix)
try:
    p0.setUniform("ifvgNormalMatrix", normalMatrix)
except RuntimeError as e:
    print("  (!!!) ifvgNormalMatrix does not seem to be used.")

print("Initializing vertex attributes...")

vs0 = cg.Vertex3Set.create()
mm.addLocalRef(vs0)
s0 = cg.Vector3(5., 5., 5.)
k = 0
for it in verts:
    it.scale(s0)
    v0 = cg.Vertex3(it)
    v1 = cg.Vertex3(it)
    v0.transform(mvpMatrix)
    v1.transformVI(mvpMatrix)
    print("  vertex [%03d]: (%s) -> (%s) -> (%s)" 
        % (k, it.getValueString(), v0.getValueString(), 
            v1.getValueString()))
    vs0.addVertex(it)
    k += 1

va0 = ggl.VertexAttribute.create()
va0.init()
va0.setData(vs0)
va0.update()

cs0 = ai.ColorSet.create()
mm.addLocalRef(cs0)
for it in colors:
    cs0.addColor(it)

va1 = ggl.VertexAttribute.create()
va1.init()
va1.setData(cs0)
va1.update()

print("Initializing vertex array object...")

vao0 = ggl.VertexArrayObject.create()
mm.addLocalRef(vao0)
vao0.init()
vao0.addAttribute(va0)
vao0.addAttribute(va1)
vao0.update()

print("Running viewer...")

nFrames = 0
clock = cg.Clock.create()
mm.addLocalRef(clock)
clock.start()
while (not viewer.getShutdownFlag()):
    viewer.clear()
    va0.draw(ggl.PRIMITIVE_TRIANGLE, 1)
    viewer.swapBuffers()
    viewer.pollEvents()
    # fps count
    if (nFrames == checkFPSInterval):
        clock.stop()
        secs = clock.getElapsedTime()
        fps = nFrames / secs
        print ("  fps = %f, width = %d, height = %d" % (fps, w, h))
        nFrames = 0
        clock.start()
    else:
        nFrames += 1
    # handle events
    es0 = viewer.getEvents()
    ne0 = es0.getNumEvents()
    for i in range(0, ne0):
        e0 = es0.getEvent(i)
        if (e0.getEventType() != ggl.ViewerEvent.TYPE_CURSOR_POS):
            print ("  event: [%s]" % e0.getValueString())
        if (e0.getEventType() == ggl.ViewerEvent.TYPE_KEY):
            # handle key event
            if ((e0.getKeyCode() == 256) 
                and (e0.getKeyAction() == 1)):
                # escape
                viewer.closeWindow()
                viewer.shutdown(False)
        elif (e0.getEventType() == ggl.ViewerEvent.TYPE_WINDOW_CLOSE):
            # handle window close event
            viewer.shutdown(False)
        elif (e0.getEventType() == ggl.ViewerEvent.TYPE_WINDOW_SIZE):
            # handle window size event
            # adjust view matrix according to aspect ratio
            w0 = viewer.getWindowWidth()
            h0 = viewer.getWindowHeight()
            ar0 = w0 / h0
            if (ar0 != ar):
                s1 = cg.Matrix4.scale(ar / ar0, 1., 1., 1.)
                mvpMatrix.multiplyLeft(s1)
                p0.setUniform("ifvgMVPMatrix", mvpMatrix)
                w = w0
                h = h0
                ar = ar0

viewer.shutdown()
mm.removeLocalRef(vao0)
mm.removeLocalRef(viewer)

print("All done!")

