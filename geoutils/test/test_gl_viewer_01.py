#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""GeoUtils/GL test: Viewer #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsGL as ggl
import Altjira as ai

testName = "Viewer #1"

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

print("  %s" % viewer.getString())

print("Initializing shaders...")

p0 = ggl.Program()
p0.init()
p0.use()

print("Initializing uniforms...")

w = viewer.getWindowWidth()
h = viewer.getWindowHeight()
ar = w / h
mvpMatrix.setElement(0, 0, 1. / ar)
p0.setUniform("ifvgMVPMatrix", mvpMatrix)
try:
    p0.setUniform("ifvgNormalMatrix", normalMatrix)
except RuntimeError as e:
    print("  (!!!) ifvgNormalMatrix does not seem to be used.")

print("Initializing vertex attributes...")

vs0 = cg.Vertex3Set.create()
mm.addLocalRef(vs0)
for it in verts:
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

