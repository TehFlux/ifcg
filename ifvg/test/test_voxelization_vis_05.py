#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Voxelization visualization #5."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsGL as ggl
import Altjira as ai
import AltjiraGeoUtils as ag
import math as m
import CIFVG as vg
import CIFVGViewer as vgv
import ifvg_local_config as lc

testName = "Voxelization visualization #5"

# memory management
mm = ib.IFObject()

def updateShaderParams(program, p0 = 0, p1 = 0, p2 = 0, p3 = 0):
    """Update shader parameters."""
    pv0 = ib.IntVector()
    ib.addValues(pv0, 4, p0, p1, p2, p3)
    program.setUniform("cgShaderParams0", pv0, 4)

def updateMVPMatrix(camera, locOffset, mvpMatrix, program):
    """Update model/view/projection matrix."""
    tm0 = cg.Matrix4.translate(locOffset)
    cm0 = camera.getExtrinsicMatrix()
    cmInv0 = cm0.invert()
    cmInv0.multiplyRight(tm0)
    cm2 = camera.getPerspectiveMatrix(cg.AXIS_Z, near, far, -2.)
    mvpMatrix.setElements(cmInv0)
    mvpMatrix.multiplyLeft(cm2)
    program.setUniform("cgMVPMatrix", mvpMatrix)

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

vertexShaderSourceFile01 = lc.shaderSourceDir + '/lambert330.vert'
fragmentShaderSourceFile01 = lc.shaderSourceDir + '/lambert330.frag'

partName0 = 'part'

meshInputFile0 = (lc.meshPath + '/' + lc.dataSetName 
    + '/' + partName0 + '.vgmesh')
voxelInputFile0 = (lc.voxelizationPath  + '/' + lc.dataSetName 
    + '/' + partName0 + '.vgnodeh')

distance = 11.
fov = 65.
near = 0.1
far = 20.
pitch = 60.
roll = 0.
yaw = 0.
angleStep = 10.
distanceStep = 0.5
locStep = 0.2
fovStep = 5.
flatFaces = True
renderEdges = True
lineWidth = 1.

clearColor = ai.Color("#585e6b")

octreeMaxNumLevels = lc.octreeMaxNumLevels
octreeOrder = lc.octreeOrder
octreeScale = lc.octreeScale
octreeMargin = lc.octreeMargin

octreeColorOffset = 8
octreeLeafColorIndex = 4
octreeBoxInset = 0.0
numColors = 2 * octreeMaxNumLevels
octreeVisScale = lc.octreeVisScale
octreeVisDataType = lc.octreeVisDataType
octreeVisVoxelClass = lc.octreeVisVoxelClass
renderOctreeLeavesOnly = True
useDataType = True

renderMesh = False
centerOnMesh = True
meshColor0 = ai.Color("#8b4067")
meshFlipNormals = True

print("Creating colors...")

cb0 = ai.ColorBand.rainbow()
mm.addLocalRef(cb0)
colors = ai.ColorSet.create()
mm.addLocalRef(colors)
cb0.sample(numColors, colors)

voxelClassColors = vg.VoxelClassColorVector()

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

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

if (renderMesh or centerOnMesh):
    print("Loading mesh '%s'..." % meshInputFile0)
    
    ioCtx.clear()
    ioCtx.openFileForInput(meshInputFile0)
    
    mesh0 = vg.Mesh.create()
    mm.addLocalRef(mesh0)
    
    clock0 = cg.Clock()
    
    clock0.start()
    ioCtx.begin()
    mesh0.deserialize(ioCtx)
    ioCtx.finish()
    clock0.stop()
    
    t0 = clock0.getElapsedTime()
    
    print("  loaded in %f secs" % t0)
    
    nv0 = mesh0.getNumVertices()
    nf0 = mesh0.getNumFaces()
    
    bb0 = mesh0.getBounds()
    ao0 = bb0.getAxisOrder()
    s0 = bb0.getExtent(ao0.a0)
    e0 = bb0.getExtent()
    c0 = bb0.getCenter()
    r0 = bb0.getRadius()
    
    print("  mesh '%s' (%d)" % (mesh0.getID(), mesh0.getIDNum()))
    print("  %d vertices, %d faces" % (nv0, nf0))
    print("  bounding box: [%s]" % bb0.getValueString())
    print("    center = (%s)" % c0.getValueString())
    print("    radius = (%s)" % r0.getValueString())
    print("    extent = (%s)" % e0.getValueString())
    print("    scale = %f" % s0)
    
    numVerts0 = nv0
    numFaces0 = nf0
    numEdges0 = mesh0.getNumEdges()

print("Input data bounding box:")

bb1 = lc.inputDataBoundingBox
ao1 = bb1.getAxisOrder()
s1 = bb1.getExtent(ao1.a0)
e1 = bb1.getExtent()
c1 = bb1.getCenter()
r1 = bb1.getRadius()

print("  bounding box: [%s]" % bb1.getValueString())
print("    center = (%s)" % c1.getValueString())
print("    radius = (%s)" % r1.getValueString())
print("    extent = (%s)" % e1.getValueString())
print("    scale = %f" % s1)

if (renderMesh or centerOnMesh):
    # center the mesh
    mesh0.translate(c1.flip())

print("Creating octree...")

ctx = vg.Context.create(octreeMaxNumLevels, octreeOrder, octreeScale)
ctx.setID('Context01')
mm.addLocalRef(ctx)

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

s2 = octreeScale * octreeVisScale * (1. - 2. * m0) / s1
t1 = octreeScale * octreeVisScale * 0.5
vertexOffset = cg.Vector3(-t1, -t1, -t1)
vertexScale = cg.Vector3(octreeVisScale, octreeVisScale, octreeVisScale)
sv0 = cg.Vector3(s2, s2, s2)
tv0 = cg.Vector3(t1, t1, t1)

if (renderMesh or centerOnMesh):
    print("Transforming mesh...")
    
    mesh0.scale(sv0)
    #mesh0.translate(tv0)
    mesh0.applyTransform(True)
    mesh0.update(False, False)
    
    bb3 = mesh0.getBounds()
    ao3 = bb3.getAxisOrder()
    s3 = bb3.getExtent(ao3.a0)
    e3 = bb3.getExtent()
    c3 = bb3.getCenter()
    r3 = bb3.getRadius()
    
    print("  bounding box: [%s]" % bb3.getValueString())
    print("    center = (%s)" % c3.getValueString())
    print("    radius = (%s)" % r3.getValueString())
    print("    extent = (%s)" % e3.getValueString())
    print("    scale = %f" % s3)
    
    locOffset = cg.Vector3(c3.flip())
else:
    locOffset = cg.Vector3(cg.Vector3.ZERO)

print("Loading node hierarchy from file '%s'..." % voxelInputFile0)

ioCtx.clear()

ioCtx.openFileForInput(voxelInputFile0)

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)
root0.setID(partName0 + '_root')

clock0 = cg.Clock()

clock0.start()
ioCtx.begin()
root0.deserializeHierarchy(ioCtx)
ioCtx.finish()
clock0.stop()

t0 = clock0.getElapsedTime()

print("  loaded in %f secs" % t0)

maxDepth0 = root0.getMaxDepth()
memSize0 = root0.getMemSize(True)

print("  max. depth     = %d" % maxDepth0)
print("  allocated size = %d bytes" % memSize0)

if (useDataType):
    useVoxelClass = vg.Node.dataTypeHasVoxelClassInfo(octreeVisDataType)
    if (useVoxelClass):
        print("  Data nodes of type '%s' with class '%s' per level:" 
            % (vg.Node.getDataTypeString(octreeVisDataType), 
                vg.getVoxelClassValueString(octreeVisVoxelClass)))
    else:
        print("  Data nodes of type '%s':" 
            % vg.Node.getDataTypeString(octreeVisDataType))
    
    nf0 = vg.NodeFilter.create()
    mm.addLocalRef(nf0)
    nf0.setContext(ctx)
    nf0.setDataType(octreeVisDataType)
    if (useVoxelClass):
        nf0.setVoxelClass(octreeVisVoxelClass)
    
    ns0 = vg.NodeSet()
    for i in range(0, octreeMaxNumLevels):
        nf0.setDepthRange(i, i)
        ns0.clearNodes()
        cn0 = root0.find(ns0, nf0, True)
        print("    level %d: %d data nodes" % (i, cn0))
    ns0.clearNodes()
else:
    useVoxelClass = False

print("Creating meshes...")

if (renderMesh):
    clock0.start()
    mesh1 = mesh0.copy()
    mesh1.setID("Mesh01_render")
    mm.addLocalRef(mesh1)
    mesh1.setFaceVertexNormals(meshFlipNormals)
    c0 = cg.Vector4()
    ag.colorToVec(meshColor0, c0)
    mesh1.setFaceVertexColors(c0)
    #mesh1.translate(vertexOffset)
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
updateMVPMatrix(cam0, locOffset, mvpMatrix, p0)
print("  using MVP matrix: \n%s" % mvpMatrix.getValueStringF(10))
try:
    normalMatrix.setElements(mvpMatrix.invert().transpose())
    p0.setUniform("cgNormalMatrix", normalMatrix)
    print("  using normal matrix: \n%s" % normalMatrix.getValueStringF(10))
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

nf1 = vg.NodeFilter.create()
mm.addLocalRef(nf1)
nf1.setContext(ctx)
nf1.setLeavesOnly(renderOctreeLeavesOnly)
if (useDataType):
    nf1.setDataType(octreeVisDataType)
if (useVoxelClass):
    nf1.setVoxelClass(octreeVisVoxelClass)

clock0.start()
root0.getVertexAttributes(va00, va02, va03, nFaceType, octreeBoxInset, 
    colors, octreeColorOffset, 0, vg.COLOR_INDEX_UNSPECIFIED, 
    octreeLeafColorIndex, voxelClassColors, vertexOffset, vertexScale, 
    nf1, True)
if (renderOctreeLeavesOnly or useDataType):
    # render the root node itself
    root0.getVertexAttributes(va00, va02, va03, nFaceType, octreeBoxInset, 
        colors, octreeColorOffset, 0, vg.COLOR_INDEX_UNSPECIFIED, 
        octreeLeafColorIndex, voxelClassColors, vertexOffset, vertexScale, 
        None, False)
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
vao0.setID(root0.getID() + "_vao")
mm.addLocalRef(vao0)
vao0.init()
vao0.addAttribute(va00)
vao0.addAttribute(va01)
vao0.addAttribute(va02)
vao0.addAttribute(va03)
vao0.update()

if (renderMesh):
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
#locOffset = cg.Vector3(cg.Vector3.ZERO)
while (not viewer.getShutdownFlag()):
    viewer.clear()
    updateShaderParams(p0, 1, 0, 0, 0)
    vao0.bind()
    va00.draw(ggl.PRIMITIVE_LINE, numEdges2)
    if (renderMesh):
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
                elif (e0.getKeyCode() == 70):
                    # r
                    cy = locOffset.getElement(cg.AXIS_Y)
                    locOffset.setElement(cg.AXIS_Y, cy + locStep)
                    updateCam = True
                elif (e0.getKeyCode() == 82):
                    # f
                    cy = locOffset.getElement(cg.AXIS_Y)
                    locOffset.setElement(cg.AXIS_Y, cy - locStep)
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
        #loc0 = cam0.getLocation()
        #loc0.addIP(locOffset)
        updateMVPMatrix(cam0, locOffset, mvpMatrix, p0)

viewer.shutdown()
mm.removeLocalRef(vao0)
mm.removeLocalRef(viewer)

print("All done!")

