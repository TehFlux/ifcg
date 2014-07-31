#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""GeoUtils/GL test: Viewer #3."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsGL as ggl
import Altjira as ai
import math as m

testName = "Viewer #3: Lambert shader"

# memory management
mm = ib.IFObject()

print("GeoUtils/GL test: %s" % testName)

checkFPSInterval = 200
mvpMatrix = cg.Matrix4.create(cg.Matrix4.UNIT)
mm.addLocalRef(mvpMatrix)
normalMatrix = cg.Matrix3.create(cg.Matrix3.UNIT)
mm.addLocalRef(normalMatrix)

lightPos = [
    cg.Vector3.create(2., 5., 10.)
]

lightColor = [
    ai.Color.create(1., 1., 1., 1.)
]

# light parameters
# (intensity, falloffExponent, falloffScale, unused)
lightParam = [
    cg.Vector4.create(4., 1.4, 0.2, 0.)
]

verts = [
    cg.Vertex3.create(-0.5, -0.433, 0.), 
    cg.Vertex3.create(0.5, -0.433, 0.), 
    cg.Vertex3.create(0., 0.433, 0.)
]

emitColors = [
    ai.Color.create(0.05, 0., 0., 1.), 
    ai.Color.create(0., 0.05, 0., 1.), 
    ai.Color.create(0., 0., 0.05, 1.)
]

diffuseColors = [
    ai.Color.create(1., 0., 0., 1.), 
    ai.Color.create(0., 1., 0., 1.), 
    ai.Color.create(0., 0., 1., 1.)
]

normals = [
    cg.Vector3.create(0., 0., 1.), 
    cg.Vector3.create(0., 0., 1.), 
    cg.Vector3.create(0., 0., 1.)
]

vertexScale0 = cg.Vector3(5., 5., 5.)

vertexShaderSourceFile01 = "data/shaders/lambert330.vert"
fragmentShaderSourceFile01 = "data/shaders/lambert330.frag"

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

distance = 10.
fov = 65.
near = 1.
far = 20.
pitch = 60.
roll = 0.
yaw = 0.
angleStep = 10.
distanceStep = 0.5

print("Creating camera...")

cam0 = cg.Camera.create()
mm.addLocalRef(cam0)
cam0.setOriginCam(distance, pitch, roll, yaw, 
    ar, cg.Camera.angleToD(fov * m.pi / 180, ar), 
    cg.AXIS_Y, cg.AXIS_Z, cg.AXIS_X, 
    cg.AXIS_X, cg.AXIS_Z, cg.AXIS_Z)

# this is the recommended way to obtain the MVP matrix
cm0 = cam0.getExtrinsicMatrix()
cmInv0 = cm0.invert()
# scale perspective matrix for OpenGL value ranges
cm2 = cam0.getPerspectiveMatrix(cg.AXIS_Z, near, far, -2.)

mvp2 = cg.Matrix4.create()
mm.addLocalRef(mvp2)
mvp2.setElements(cmInv0)
mvp2.multiplyLeft(cm2)

print("  camera inverse extrinsic matrix: \n%s" 
    % cmInv0.getValueStringF(10))

print("  camera perspective matrix: \n%s" % cm2.getValueStringF(10))

print("  camera calculated MVP matrix: \n%s" % mvp2.getValueStringF(10))

# mvp0, mvp1, mvp2 should all have the same effect
mvpMatrix.setElements(mvp2)
normalMatrix.setElements(mvp2.invert().transpose())

print("  using MVP matrix: \n%s" % mvpMatrix.getValueStringF(10))

print("Initializing shaders...")

print("  Vertex shader:   %s" % vertexShaderSourceFile01)

vertexShaderSource01 = open(vertexShaderSourceFile01, 'r').read()

print("  Fragment shader: %s" % fragmentShaderSourceFile01)

fragmentShaderSource01 = open(fragmentShaderSourceFile01, 'r').read()

p0 = ggl.Program.create(vertexShaderSource01, fragmentShaderSource01)
mm.addLocalRef(p0)
p0.init()
p0.use()

print("Initializing uniforms...")

# transformation matrices
p0.setUniform("cgMVPMatrix", mvpMatrix)
try:
    p0.setUniform("cgNormalMatrix", normalMatrix)
except RuntimeError as e:
    print("  (!!!) cgNormalMatrix does not seem to be used.")

# light positions
lps0 = cg.VectorSet.create()
mm.addLocalRef(lps0)
for it in lightPos:
    lps0.addVector(it)
p0.setUniform("cgLightPos", lps0)

# light colors
lcs0 = cg.VectorSet.create()
mm.addLocalRef(lcs0)
lcs1 = ai.ColorSet.create()
mm.addLocalRef(lcs1)
for it in lightColor:
    lcs1.addColor(it)
    cv0 = cg.Vector4.create(
        it.getRed(), it.getGreen(), it.getBlue(), it.getAlpha())
    lcs0.addVector(cv0)
p0.setUniform("cgLightColor", lcs0)

# light parameters
lps1 = cg.VectorSet.create()
mm.addLocalRef(lps1)
for it in lightParam:
    lps1.addVector(it)
p0.setUniform("cgLightParam", lps1)

print("Initializing vertex attributes...")

# vertices
vs0 = cg.Vertex3Set.create()
mm.addLocalRef(vs0)
k = 0
for it in verts:
    it.scale(vertexScale0)
    v0 = cg.Vertex3(it)
    v1 = cg.Vertex3(it)
    v0.transform(mvpMatrix)
    v1.transformVI(mvpMatrix)
    print("  vertex [%03d]: (%s) -> (%s) -> (%s)" 
        % (k, it.getValueString(), v0.getValueString(), 
            v1.getValueString()))
    l = 0
    for it1 in lightPos:
        ld0 = (it1 - it.getVector()).normalize()
        print("    [%03d] lightDir = (%s)" % (l, ld0.getValueString()))
    vs0.addVertex(it)
    k += 1

va0 = ggl.VertexAttribute.create()
va0.init()
va0.setData(vs0)
va0.update()

# emit colors
cs0 = ai.ColorSet.create()
mm.addLocalRef(cs0)
for it in emitColors:
    cs0.addColor(it)

va1 = ggl.VertexAttribute.create()
va1.init()
va1.setData(cs0)
va1.update()

# diffuse colors
cs1 = ai.ColorSet.create()
mm.addLocalRef(cs1)
for it in diffuseColors:
    cs1.addColor(it)

va2 = ggl.VertexAttribute.create()
va2.init()
va2.setData(cs1)
va2.update()

# normals
vs1 = cg.VectorSet.create()
mm.addLocalRef(vs1)
for it in normals:
    vs1.addVector(it)

va3 = ggl.VertexAttribute.create()
va3.init()
va3.setData(vs1)
va3.update()

print("Initializing vertex array object...")

vao0 = ggl.VertexArrayObject.create()
mm.addLocalRef(vao0)
vao0.init()
vao0.addAttribute(va0)
vao0.addAttribute(va1)
vao0.addAttribute(va2)
vao0.addAttribute(va3)
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
    updateCam = False
    for i in range(0, ne0):
        e0 = es0.getEvent(i)
        if (e0.getEventType() != ggl.ViewerEvent.TYPE_CURSOR_POS):
            print ("  event: [%s]" % e0.getValueString())
        if (e0.getEventType() == ggl.ViewerEvent.TYPE_KEY):
            # handle key event
            if (e0.getAction() == 1):
                # key press events
                if (e0.getKeyCode() == 256):
                    # escape
                    viewer.closeWindow()
                    viewer.shutdown(False)
                elif (e0.getKeyCode() == 263):
                    # left
                    yaw -= angleStep
                    updateCam = True
                elif (e0.getKeyCode() == 262):
                    # right
                    yaw += angleStep
                    updateCam = True
                elif (e0.getKeyCode() == 265):
                    # up
                    pitch -= angleStep
                    updateCam = True
                elif (e0.getKeyCode() == 264):
                    # down
                    pitch += angleStep
                    updateCam = True
                elif (e0.getKeyCode() == 44):
                    # ,
                    roll -= angleStep
                    updateCam = True
                elif (e0.getKeyCode() == 46):
                    # .
                    roll += angleStep
                    updateCam = True
                elif (e0.getKeyCode() == 266):
                    # PgUp
                    distance -= distanceStep
                    updateCam = True
                elif (e0.getKeyCode() == 267):
                    # PgDown
                    distance += distanceStep
                    updateCam = True
                elif (e0.getKeyCode() == 320):
                    # keypad 0
                    roll = 0.
                    pitch = 60.
                    yaw = 0.
                    updateCam = True
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
                p0.setUniform("cgMVPMatrix", mvpMatrix)
                w = w0
                h = h0
                ar = ar0
    if (updateCam):
        # update camera
        # normalize euler angles
        if (yaw < -180.):
            yaw += 360.
        if (yaw > 180.):
            yaw -= 360.
        if (pitch <= -90.):
            pitch = -89.99
        if (pitch >= 90.):
            pitch = 89.99
        if (roll < -180.):
            roll += 360.
        if (roll > 180.):
            roll -= 360.
        # update MVP matrix
        print("  Updating camera: d = %f, YPR = (%f, %f, %f)" 
            % (distance, yaw, pitch, roll))
        cam0.setOriginCam(distance, pitch, roll, yaw, 
            ar, cg.Camera.angleToD(fov * m.pi / 180, ar), 
            cg.AXIS_Y, cg.AXIS_Z, cg.AXIS_X, 
            cg.AXIS_X, cg.AXIS_Z, cg.AXIS_Z)
        cm0 = cam0.getExtrinsicMatrix()
        cmInv0 = cm0.invert()
        cm2 = cam0.getPerspectiveMatrix(cg.AXIS_Z, near, far, -2.)
        mvpMatrix.setElements(cmInv0)
        mvpMatrix.multiplyLeft(cm2)
        p0.setUniform("cgMVPMatrix", mvpMatrix)

viewer.shutdown()
mm.removeLocalRef(vao0)
mm.removeLocalRef(viewer)

print("All done!")

