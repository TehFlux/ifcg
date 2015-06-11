#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Voxelization #2."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsGL as ggl
import Altjira as ai
import AltjiraGeoUtils as ag
import math as m
import CIFVG as vg
import CIFVGViewer as vgv

testName = "Voxelization #4: Mesh #1"

# memory management
mm = ib.IFObject()

def updateShaderParams(program, p0 = 0, p1 = 0, p2 = 0, p3 = 0):
    """Update shader parameters."""
    pv0 = ib.IntVector()
    ib.addValues(pv0, 4, p0, p1, p2, p3)
    program.setUniform("cgShaderParams0", pv0, 4)

print("IFVG test: %s" % testName)

checkFPSInterval = 1000
mvpMatrix = cg.Matrix4.create(cg.Matrix4.UNIT)
mm.addLocalRef(mvpMatrix)
normalMatrix = cg.Matrix3.create(cg.Matrix3.UNIT)
mm.addLocalRef(normalMatrix)

# lights
lightPos = [
    cg.Vector3.create(4., 4., 10.)
]

lightColor = [
    ai.Color.create(1., 1., 1., 1.)
]

# light parameters
# (intensity, falloffExponent, falloffScale, unused)
lightParam = [
    cg.Vector4.create(4., 1.4, 0.2, 0.)
    #cg.Vector4.create(1., 0., 0., 0.)
]

# shader parameters
# (flat shading, unused, unused, unused)
shaderParams0 = [ 1, 0, 0, 0 ]

geoutilsDir01 = "/home/flux4/recent/geoutils"
shaderSourceDir01 = geoutilsDir01 + "/data/shaders"
vertexShaderSourceFile01 = shaderSourceDir01 + "/lambert330.vert"
fragmentShaderSourceFile01 = shaderSourceDir01 + "/lambert330.frag"

dataDir0 = '/home/flux4/recent/p/data'
meshDir0 = dataDir0 + '/meshes'
meshFile0 = meshDir0 + '/unnamed-part-01.xml'

distance = 11.
fov = 65.
near = 1.
far = 20.
pitch = 60.
roll = 0.
yaw = 0.
angleStep = 10.
distanceStep = 0.5
locStep = 0.5
fovStep = 5.
flatFaces = True
renderEdges = True
lineWidth = 1.

clearColor = ai.Color("#585e6b")

octreeMaxNumLevels = 7
octreeOrder = 2
octreeScale = 4.
octreeColorOffset = 8
octreeLeafColorIndex = 4
octreeBoxInset = 0.0
numColors = 2 * octreeMaxNumLevels
octreeMargin = 4

renderOctreeLeavesOnly = True

voxelizeFillNodes = True
voxelizePruneEmpty = False

meshColor0 = ai.Color("#8b4067")
meshFlipNormals = True

print("Creating colors...")

cb0 = ai.ColorBand.rainbow()
mm.addLocalRef(cb0)
colors = ai.ColorSet.create()
mm.addLocalRef(colors)
cb0.sample(numColors, colors)

print("Creating viewer...")

viewer = vgv.Viewer.create()
mm.addLocalRef(viewer)
viewer.setID("Viewer01")
viewer.setClearColor(clearColor)

viewer.init()
viewer.setWindowTitle("IFVG test: %s" % testName)
w = viewer.getWindowWidth()
h = viewer.getWindowHeight()
ar = w / h

if (not renderEdges):
    ggl.enableOpenGLBackFaceCulling()
ggl.enableOpenGLDepthBufferTest()
ggl.setOpenGLLineWidth(lineWidth)

print("  %s" % viewer.getString())

print("Loading mesh '%s'..." % meshFile0)

# register XML object factories
cg.Vector2.getXMLObjectFactory()
cg.Vector3.getXMLObjectFactory()
cg.FaceData.getXMLObjectFactory()

clock0 = cg.Clock()

mesh0 = cg.Mesh.create()
mm.addLocalRef(mesh0)

clock0.start()
mesh0.loadFromXMLFile(meshFile0)
mesh0.makeTris()
mesh0.update()
#mesh0.createEdges()
clock0.stop()

numVerts0 = mesh0.getNumVertices()
numFaces0 = mesh0.getNumFaces()
numEdges0 = mesh0.getNumEdges()

t0 = clock0.getElapsedTime()

print("  Loaded mesh '%s' (%d vertices, %d faces, %d edges) in %d secs" 
    % (mesh0.getID(), numVerts0, numFaces0, numEdges0, t0))

bb0 = mesh0.getBounds()
ao0 = bb0.getAxisOrder()
s0 = bb0.getExtent(ao0.a0)
e0 = bb0.getExtent()
c0 = bb0.getCenter()

print("  Bounding box: [%s] [center = (%s), scale = %f, extent = (%s)]" 
    % (bb0.getValueString(), c0.getValueString(), s0, 
        e0.getValueString()))

# center the mesh
mesh0.translate(c0.flip())
#mesh0.applyTransform()
#mesh0.update()

#bb1 = mesh0.getBounds()
#e1 = bb1.getExtent()
#c1 = bb1.getCenter()

#print("  Bounding box: [%s] [center = (%s), extent = (%s)]" 
#    % (bb1.getValueString(), c1.getValueString(), e1.getValueString()))

print("Creating octree...")

ctx = vg.Context.create(octreeMaxNumLevels, octreeOrder, octreeScale)
ctx.setID('Context01')
mm.addLocalRef(ctx)

#ctx.printDebugInfo()

n0 = ctx.getMaxNumLeafChildNodesPerDimension()
minLeafSize = ctx.getMinLeafSize()
numVoxelsTotal =  n0 * n0 * n0
m0 = minLeafSize * octreeMargin
m1 = octreeMargin / n0

print("  max. levels                    = %d" % octreeMaxNumLevels)
print("  order                          = %d" % octreeOrder)
print("  scale                          = %f" % octreeScale)
print("  octree margin                  = %f" % octreeMargin)
print("  max. leaf nodes per dimension  = %d" % n0)
print("  min. leaf size                 = %f" % minLeafSize)
print("  number of voxels               = %d" % numVoxelsTotal)

print("Transforming mesh...")

s1 = octreeScale * (1. - (2. * m1)) / s0
s2 = 0.5 * octreeScale
vertexOffset = cg.Vector3(-s2, -s2, -s2)
sv0 = cg.Vector3(s1, s1, s1)
mesh0.scale(sv0)
t1 = octreeScale * 0.5
tv0 = cg.Vector3(t1, t1, t1)
mesh0.translate(tv0)
mesh0.applyTransform()
mesh0.update()

bb1 = mesh0.getBounds()
e1 = bb1.getExtent()
c1 = bb1.getCenter()

print("  Bounding box: [%s] [center = (%s), extent = (%s)]" 
    % (bb1.getValueString(), c1.getValueString(), e1.getValueString()))

print("Creating root node...")

root0 = vg.Node.create(ctx)
root0.setID('root0')
mm.addLocalRef(root0)

root0.printDebugInfo(True)

print("Inserting faces...")

clock0.start()
numFacesInserted = root0.voxelizeInsertFaces(mesh0, 
    vg.SEPARABILITY_26, False)
clock0.stop()

t0 = clock0.getElapsedTime()

print("  %d faces inserted in %f secs (%f faces/sec)" 
    % (numFacesInserted, t0, numFacesInserted / t0))

print("Voxelizing faces...")

clock0.start()
numVoxelsFilled = root0.voxelizeFaces(vg.DEPTH_UNSPECIFIED, 
    vg.VOXELIZATION_TARGET_DENSITY, vg.SEPARABILITY_26, 
    voxelizeFillNodes, voxelizePruneEmpty)
clock0.stop()

t0 = clock0.getElapsedTime()

filledVoxelsPerSec = numVoxelsFilled / t0
facesPerSec = numFaces0 / t0

print("  Number of voxels set:      %d / %d" % (numVoxelsFilled, 
    numVoxelsTotal))
print("  Voxelization time:         %f secs (%f voxels/sec, %f faces/sec)" 
    % (t0, filledVoxelsPerSec, facesPerSec))

print("Pruning empty nodes...")

clock0.start()
numNodesPruned = root0.pruneEmpty(True)
clock0.stop()

t0 = clock0.getElapsedTime()

prunedNodesPerSec = numNodesPruned / t0
octreeMemSize = root0.getMemSize(True)
bytesPerVoxel = octreeMemSize / numVoxelsFilled

print("  Number of nodes pruned:    %d" % numNodesPruned)
print("  Pruning time:              %f secs (%f voxels/sec)" 
    % (t0, prunedNodesPerSec))
print("  Allocated size of octree:  %d bytes (%f bytes/voxel)" 
    % (octreeMemSize, bytesPerVoxel))

print("Creating meshes...")

clock0.start()
mesh1 = mesh0.copy()
mesh1.setID("Mirror01_render")
mm.addLocalRef(mesh1)
mesh1.setFaceVertexNormals(meshFlipNormals)
c0 = cg.Vector4()
ag.colorToVec(meshColor0, c0)
mesh1.setFaceVertexColors(c0)
mesh1.translate(vertexOffset)
mesh1.applyTransform()
clock0.stop()

numVerts1 = mesh1.getNumVertices()
numFaces1 = mesh1.getNumFaces()
numEdges1 = mesh1.getNumEdges()

print("  Created mesh '%s' (%d vertices, %d faces, %d edges)." 
    % (mesh1.getID(), numVerts1, numFaces1, numEdges1))

t2 = clock0.getElapsedTime()
print("    Mesh creation time:  %f secs" % t2)

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

# shader parameters
updateShaderParams(p0, *shaderParams0)

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
lcs0 = ai.ColorSet.create()
mm.addLocalRef(lcs0)
for it in lightColor:
    lcs0.addColor(it)
p0.setUniform("cgLightColor", lcs0)

# light parameters
lps1 = cg.VectorSet.create()
mm.addLocalRef(lps1)
for it in lightParam:
    lps1.addVector(it)
p0.setUniform("cgLightParam", lps1)

print("Initializing vertex attributes...")

print("  Node '%s'..." % root0.getID())

nFaceType = cg.NFace.TYPE_EDGE

# vertices
va00 = ggl.VertexAttribute.create()
va00.setID("va00")
va00.init()

# emit colors
va01 = ggl.VertexAttribute.create()
va01.setID("va01")

# diffuse colors
va02 = ggl.VertexAttribute.create()
va02.setID("va02")
va02.init()

# normals
va03 = ggl.VertexAttribute.create()
va03.setID("va03")
va03.init()

clock0.start()
root0.getVertexAttributes(va00, va02, va03, nFaceType, octreeBoxInset, 
    colors, octreeColorOffset, 0, vg.COLOR_INDEX_UNSPECIFIED, 
    octreeLeafColorIndex, vertexOffset, None, True, 
    renderOctreeLeavesOnly)
if (renderOctreeLeavesOnly):
    # render the root node itself
    root0.getVertexAttributes(va00, va02, va03, nFaceType, octreeBoxInset, 
        colors, octreeColorOffset, 0, vg.COLOR_INDEX_UNSPECIFIED, 
        octreeLeafColorIndex, vertexOffset, None, False, False)
clock0.stop()

va00.update()
va02.update()
va03.update()

t3 = clock0.getElapsedTime()
print("    Vertex attribute creation time:       %f secs" % t3)

numVertexAttribElements0 = va00.getNumElements()
numEdges2 = int(numVertexAttribElements0 / 2)

print("    Number of vertex attribute elements:  %d" 
    % numVertexAttribElements0)
print("    Number of edges:                      %d" % numEdges2)

print("    Initializing vertex array object...")

vao0 = ggl.VertexArrayObject.create()
vao0.setID(mesh0.getID() + "_vao")
mm.addLocalRef(vao0)
vao0.init()
vao0.addAttribute(va00)
vao0.addAttribute(va01)
vao0.addAttribute(va02)
vao0.addAttribute(va03)
vao0.update()

print("  Mesh '%s'..." % mesh1.getID())

nFaceType = cg.NFace.TYPE_FACE

# vertices
va10 = ggl.VertexAttribute.create()
va10.setID("va10")
va10.init()
va10.setData(mesh1, ggl.VertexAttribute.TYPE_POSITION, nFaceType)
va10.update()
numVertexAttribElements1 = va00.getNumElements()

# emit colors
va11 = ggl.VertexAttribute.create()
va11.setID("va11")

# diffuse colors
va12 = ggl.VertexAttribute.create()
va12.setID("va12")
va12.init()
va12.setData(mesh1, ggl.VertexAttribute.TYPE_DATA, nFaceType, 
    cg.FaceData.TYPE_VERTEX_COLOR)
va12.update()

# normals
va13 = ggl.VertexAttribute.create()
va13.setID("va13")
va13.init()
va13.setData(mesh1, ggl.VertexAttribute.TYPE_DATA, nFaceType, 
    cg.FaceData.TYPE_VERTEX_NORMAL)
va13.update()

print("    Initializing vertex array object...")

vao1 = ggl.VertexArrayObject.create()
vao1.setID(mesh0.getID() + "_vao")
mm.addLocalRef(vao1)
vao1.init()
vao1.addAttribute(va10)
vao1.addAttribute(va11)
vao1.addAttribute(va12)
vao1.addAttribute(va13)
vao1.update()

print("Running viewer...")

nFrames = 0
clock = cg.Clock.create()
mm.addLocalRef(clock)
clock.start()
locOffset = cg.Vector3(cg.Vector3.ZERO)
while (not viewer.getShutdownFlag()):
    viewer.clear()
    updateShaderParams(p0, 1, 0, 0, 0)
    vao0.bind()
    va00.draw(ggl.PRIMITIVE_LINE, numEdges2)
    updateShaderParams(p0, 0, 0, 0, 0)
    vao1.bind()
    va10.draw(ggl.PRIMITIVE_TRIANGLE, numFaces1)
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
            if ((e0.getAction() == 1) 
                or (e0.getAction() == 2)):
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
                elif (e0.getKeyCode() == 87):
                    # w
                    cx = locOffset.getElement(cg.AXIS_Z)
                    locOffset.setElement(cg.AXIS_Z, cx + locStep)
                    updateCam = True
                elif (e0.getKeyCode() == 65):
                    # a
                    cx = locOffset.getElement(cg.AXIS_X)
                    locOffset.setElement(cg.AXIS_X, cx - locStep)
                    updateCam = True
                elif (e0.getKeyCode() == 83):
                    # s
                    cx = locOffset.getElement(cg.AXIS_Z)
                    locOffset.setElement(cg.AXIS_Z, cx - locStep)
                    updateCam = True
                elif (e0.getKeyCode() == 68):
                    # d
                    cx = locOffset.getElement(cg.AXIS_X)
                    locOffset.setElement(cg.AXIS_X, cx + locStep)
                    updateCam = True
                elif (e0.getKeyCode() == 333):
                    # keypad -
                    fov -= fovStep
                    updateCam = True
                elif (e0.getKeyCode() == 334):
                    # keypad +
                    fov += fovStep
                    updateCam = True
                elif (e0.getKeyCode() == 320):
                    # keypad 0
                    roll = 0.
                    pitch = 60.
                    yaw = 0.
                    fov = 65.
                    locOffset.setElements(cg.Vector3.ZERO)
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
        if (yaw == 90.):
            yaw = 89.99
        if (yaw == -90.):
            yaw = -89.99
        if (yaw <= -180.):
            yaw += 359.99
        if (yaw >= 180.):
            yaw -= 359.99
        if (pitch <= -90.):
            pitch = -89.99
        if (pitch >= 90.):
            pitch = 89.99
        if (roll <= -180.):
            roll += 359.99
        if (roll >= 180.):
            roll -= 359.99
        if (distance < near):
            distance = near
        # update MVP matrix
        print("  Updating camera: d = %f, YPR = (%f, %f, %f)" 
            % (distance, yaw, pitch, roll))
        cam0.setOriginCam(distance, pitch, roll, yaw, 
            ar, cg.Camera.angleToD(fov * m.pi / 180, ar), 
            cg.AXIS_Y, cg.AXIS_Z, cg.AXIS_X, 
            cg.AXIS_X, cg.AXIS_Z, cg.AXIS_Z)
        loc0 = cam0.getLocation()
        loc0.addIP(locOffset)
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

