#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""GeoUtils/GL test: Viewer #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsGL as ggl

testName = "Viewer #1"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

checkFPSInterval = 100
mvpMatrix = cg.Matrix4.create(cg.Matrix4.UNIT)
mm.addLocalRef(mvpMatrix)
normalMatrix = cg.Matrix3.create(cg.Matrix3.UNIT)
mm.addLocalRef(normalMatrix)

print("Creating viewer...")

viewer = ggl.Viewer.create()
mm.addLocalRef(viewer)

viewer.init()
viewer.setWindowTitle("GeoUtils/GL test: %s" % testName)

print("  %s" % viewer.getString())

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

print("Running viewer...")

nFrames = 0
clock = cg.Clock.create()
mm.addLocalRef(clock)
clock.start()
while (not viewer.getShutdownFlag()):
    viewer.clear()
    viewer.swapBuffers()
    viewer.pollEvents()
    if (nFrames == checkFPSInterval):
        clock.stop()
        secs = clock.getElapsedTime()
        fps = nFrames / secs
        print ("  fps = %f" % fps)
        nFrames = 0
        clock.start()
    else:
        nFrames += 1

viewer.shutdown()
mm.removeLocalRef(viewer)

print("All done!")

