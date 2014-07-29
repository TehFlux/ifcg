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

checkFPSInterval = 100
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

print("Creating camera...")

# camera matrix from triangle01.blend
# pos = (4, -7, 3)
# rot = ((1.1636990308761597, 0.043727900832891464, 0.5013790130615234), 
#   'XYZ')) (66.675, 2.505, 28.727)°
# depth = -Z, horizon = X, up = Y
# fov = 55°
#mv0 = cg.Matrix4.create(
#    0.876,     -0.155,      0.457,          4,
#     0.48,      0.367,     -0.797,         -7,
#  -0.0437,      0.917,      0.396,          3,
#        0,          0,          0,          1)
mv0 = cg.Matrix4.create(
    1, 0, 0, 0, 
    0, 1, 0, 0, 
    0, 0, 1, -10, 
    0, 0, 0, 1
)
mm.addLocalRef(mv0)

fov = 35.
d = 1. / (2. * m.tan((fov * m.pi / 180.) / 2.))
pm0 = cg.Matrix4.create(cg.Matrix4.UNIT)
mm.addLocalRef(pm0)
pm0.setElement(3, cg.AXIS_Z, -1. / d)
pm0.setElement(3, 3, 0)

print("  perspectiveMatrix: \n%s" % pm0.getValueStringF(10))

#cam0 = cg.Camera.create()
#mm.addLocalRef(cam0)
#cam0.setOriginCam(5, 30., 0., 30., ar, 
#    cg.AXIS_Z, cg.AXIS_Y, cg.AXIS_X)
#m0 = cam0.getModelViewMatrix(cg.Camera.MODE_PERSPECTIVE, 
#    cg.Camera.DEFAULT_ADJUST_LOCATION, 
#    cg.HANDEDNESS_RIGHT, cg.AXIS_Z, cg.AXIS_Y, cg.AXIS_X)
#p1 = cam0.getPerspectiveMatrix()

#print("  %s" % cam0.getString())

m1 = cg.Matrix4.swapAxes(cg.AXIS_X, cg.AXIS_Z, cg.AXIS_Y)

mvpMatrix.setElements(mv0)
mvpMatrix.multiplyLeft(pm0)
#mvpMatrix.multiplyLeft(m1)

print("  mvpMatrix: \n%s" % mvpMatrix.getValueStringF(10))

s1 = cg.Matrix4.scale(1. / ar, 1., 1., 1.)
mvpMatrix.multiplyLeft(s1)

print("  mvpMatrix: \n%s" % mvpMatrix.getValueStringF(10))

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
for it in verts:
    it.scale(s0)
    vs0.addVertex(it)

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
                mvpMatrix.setElement(0, 0, 1. / ar0)
                p0.setUniform("ifvgMVPMatrix", mvpMatrix)
                w = w0
                h = h0
                ar = ar0

viewer.shutdown()
mm.removeLocalRef(vao0)
mm.removeLocalRef(viewer)

print("All done!")

