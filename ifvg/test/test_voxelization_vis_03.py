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

testName = "Voxelization #3: Triangle #3"

# memory management
mm = ib.IFObject()

def createTriMesh(v0, v1, v2, color):
    """Create triangle mesh."""
    m0 = cg.Mesh.create()
    m0.addVertex(v0)
    m0.addVertex(v1)
    m0.addVertex(v2)
    m0.addFace(cg.Face.create(0, 1, 2))
    m0.update()
    m0.setFaceVertexNormals()
    c0 = cg.Vector4()
    ag.colorToVec(color, c0)
    m0.setFaceVertexColors(c0)
    m0.createEdges()
    return m0

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
    cg.Vector3.create(2., -5., 10.)
]

lightColor = [
    ai.Color.create(1., 1., 1., 1.)
]

# light parameters
# (intensity, falloffExponent, falloffScale, unused)
lightParam = [
    cg.Vector4.create(4., 1.4, 0.2, 0.)
]

# shader parameters
# (flat shading, unused, unused, unused)
shaderParams0 = [ 1, 0, 0, 0 ]

geoutilsDir01 = "/home/flux4/recent/geoutils"
shaderSourceDir01 = geoutilsDir01 + "/data/shaders"
vertexShaderSourceFile01 = shaderSourceDir01 + "/lambert330.vert"
fragmentShaderSourceFile01 = shaderSourceDir01 + "/lambert330.frag"

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

octreeMaxNumLevels = 8
octreeOrder = 2
octreeScale = 4.
octreeColorOffset = 8
octreeLeafColorIndex = 4
octreeBoxInset = 0.0
numColors = 2 * octreeMaxNumLevels

renderOctreeLeavesOnly = False

voxelizeFillNodes = True
voxelizePruneEmpty = True

#vertexOffset = cg.Vector3(
#    -0.5 * octreeScale, -0.5 * octreeScale, -0.5 * octreeScale)

triangleVerts0 = [
    cg.Vertex3.create(0.45, 0.3, 0.4), 
    cg.Vertex3.create(3.95, 3.8, 2.6), 
    cg.Vertex3.create(0.9, 3.1, 3.8)
]
triangleVerts1 = [
    cg.Vertex3.create(0.45, 0.3, 0.4), 
    cg.Vertex3.create(4.51, 2.1, 2.6), 
    cg.Vertex3.create(3.95, 3.8, 2.6)
]

triangleColor0 = ai.Color("#8b4067")
triangleColor1 = ai.Color("#408b83")

s0 = 0.15
triangleScale0 = cg.Vector3(s0, s0, s0)
triangleOffset0 = cg.Vector3(1.2, 2.3, 1.3)

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

print("Creating octree...")

ctx = vg.Context.create(octreeMaxNumLevels, octreeOrder, octreeScale)
ctx.setID('Context01')
mm.addLocalRef(ctx)

ctx.printDebugInfo()

print("Creating root node...")

root0 = vg.Node.create(ctx)
root0.setID('root0')
mm.addLocalRef(root0)

n0 = ctx.getMaxNumLeafChildNodesPerDimension()
numVoxelsTotal =  n0 * n0 * n0

root0.printDebugInfo(True)

print("  minimum leaf size: %f" % ctx.getMinLeafSize())
print("  number of voxels:  %d" % numVoxelsTotal)

print("Inserting triangle faces...")

tri0 = createTriMesh(triangleVerts0[0], triangleVerts0[1], 
    triangleVerts0[2], triangleColor0)
tri0.setID("Triangle01")
mm.addLocalRef(tri0)

tri1 = createTriMesh(triangleVerts1[0], triangleVerts1[1], 
    triangleVerts1[2], triangleColor1)
tri1.setID("Triangle02")
mm.addLocalRef(tri1)

tris0 = cg.Mesh.create()
tris0.setID("Triangles01")
mm.addLocalRef(tris0)

tris0.merge(tri0)
tris0.merge(tri1)
tris0.update()

tris0.scale(triangleScale0)
tris0.translate(triangleOffset0)
tris0.applyTransform()

bc0 = tris0.getBarycenter()
vertexOffset = bc0.flip()

numTris = tris0.getNumFaces()

for k in range(0, numTris):
    f0 = tris0.getFace(k)
    print("  face #%03d: [%s]" % (k + 1, f0.getValueString()))
    tvd0 = vg.TriangleVoxelizationData()
    ctx.initTriangleVoxelizationData(f0, tvd0, vg.SEPARABILITY_26)
    print("  triangle voxelization data:")
    vg.printTriangleVoxelizationDataDebugInfo(tvd0)
    if (not root0.voxelizeInsertFace(f0, vg.SEPARABILITY_26, False)):
        print("  !!! Root node does not contain the voxelization.")

print("Voxel tree state:")

root0.printDebugInfo(True)

print("Voxelizing faces...")

clock0 = cg.Clock()

clock0.start()
numVoxels = root0.voxelizeFaces(vg.Context.DEPTH_UNSPECIFIED, 
    vg.VOXELIZATION_TARGET_DENSITY, vg.SEPARABILITY_26, 
    voxelizeFillNodes, voxelizePruneEmpty)
octreeMemSize = root0.getMemSize(True)
bytesPerVoxel = octreeMemSize / numVoxels
clock0.stop()

t0 = clock0.getElapsedTime()
voxelsPerSec = numVoxels / t0

print("Number of voxels set:     %d / %d" % (numVoxels, numVoxelsTotal))
print("Voxelization time:        %f secs (%f voxels/sec)" 
    % (t0, voxelsPerSec))
print("Allocated size of octree: %d bytes (%f bytes/voxel)" 
    % (octreeMemSize, bytesPerVoxel))

print("Creating meshes...")

clock0.start()
mesh0 = cg.Mesh.create()
mesh0.setID('Octree01')
mm.addLocalRef(mesh0)
if (renderOctreeLeavesOnly):
    # root node mesh
    root0.getMesh(mesh0, octreeBoxInset, colors, octreeColorOffset, 
        vg.Context.COLOR_INDEX_UNSPECIFIED, octreeLeafColorIndex, False)
root0.getMesh(mesh0, octreeBoxInset, colors, octreeColorOffset, 
    vg.Context.COLOR_INDEX_UNSPECIFIED, octreeLeafColorIndex, True, 
    renderOctreeLeavesOnly)
mesh0.update()
mesh0.setFaceVertexNormals()
mesh0.createEdges()
mesh0.translate(vertexOffset)
mesh0.applyTransform()
clock0.stop()

numVerts0 = mesh0.getNumVertices()
numFaces0 = mesh0.getNumFaces()
numEdges0 = mesh0.getNumEdges()

print("  Created mesh '%s' (%d vertices, %d faces, %d edges)." 
    % (mesh0.getID(), numVerts0, numFaces0, numEdges0))

t1 = clock0.getElapsedTime()
print("    Mesh creation time:  %f secs" % t1)

clock0.start()
mesh1 = tris0.copy()
mesh1.setID("Triangles01_render")
mm.addLocalRef(mesh1)
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

#print("  Mesh '%s'..." % mesh0.getID())
print("  Node '%s'..." % root0.getID())

nFaceType = cg.NFace.TYPE_EDGE

# vertices
va00 = ggl.VertexAttribute.create()
va00.setID("va00")
va00.init()
#va00.setData(mesh0, ggl.VertexAttribute.TYPE_POSITION, nFaceType)
#va00.update()

# emit colors
va01 = ggl.VertexAttribute.create()
va01.setID("va01")

# diffuse colors
va02 = ggl.VertexAttribute.create()
va02.setID("va02")
va02.init()
#va02.setData(mesh0, ggl.VertexAttribute.TYPE_DATA, nFaceType, 
#    cg.FaceData.TYPE_VERTEX_COLOR)
#va02.update()

# normals
va03 = ggl.VertexAttribute.create()
va03.setID("va03")
va03.init()
#va03.setData(mesh0, ggl.VertexAttribute.TYPE_DATA, nFaceType, 
#    cg.FaceData.TYPE_VERTEX_NORMAL)
#va03.update()

clock0.start()
root0.getVertexAttributes(va00, va02, va03, nFaceType, octreeBoxInset, 
    colors, octreeColorOffset, 0, vg.Context.COLOR_INDEX_UNSPECIFIED, 
    octreeLeafColorIndex, vertexOffset, None, True, 
    renderOctreeLeavesOnly)
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

