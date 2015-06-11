#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Octree visualization #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsGL as ggl
import Altjira as ai
import AltjiraGeoUtils as ag
import math as m
import CIFVG as vg
import CIFVGViewer as vgv
import ifvg_local_config as lc

testName = "Octree visualization #2"

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
#    cg.Vector3.create(4., 4., 10.)
#    cg.Vector3.create(-6., -4., 6.)
    cg.Vector3.create(6., -4., 6.)
#    cg.Vector3.create(-6., -5., 7.)
#    cg.Vector3.create(6., 4., 6.)
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

#nodeName0 = 'ray_test_01'
#nodeName0 = 'icosphere01'
#nodeName0 = 'part'
#nodeName0 = 'unnamed'
#nodeName0 = 'unnamed_int_ext'

#nodeName0 = 'icosphere_ray_01'
nodeName0 = 'icosphere_ray_02'
#nodeName0 = 'icosphere_wt_01'
#nodeName0 = 'unnamed_int_ext'

voxelizeDepth = 8

voxelInputFile0 = 'temp/' + nodeName0 + '.vgnodeh'
#voxelInputFile0 = (lc.voxelizationPath  + '/' + lc.dataSetName 
#    + ('/level_%02d' % voxelizeDepth) + '/' + nodeName0 + '.vgnodeh')

distance = 11.
fov = 65.
near = 0.1
far = 20.
pitch = 60.
roll = 0.
yaw = 0.
angleStep = 5.
distanceStep = 0.2
locStep = 0.1
fovStep = 2.

lineWidth = 3.
clearColor = ai.Color("#585e6b")

octreeMaxNumLevels = lc.octreeMaxNumLevels
octreeOrder = lc.octreeOrder
octreeScale = lc.octreeScale
octreeMargin = lc.octreeMargin

octreeColorOffset = 7
octreeLeafColorIndex = 4
octreeBoxInset = 0.0
numColorsDepth = 2 * octreeMaxNumLevels
numColorsWallThickness = 20
octreeVisScale = lc.octreeVisScale

#octreeVisDataType0 = lc.rayHitDataType
#octreeVisDataType0 = vg.Node.DATA_TYPE_UNKNOWN
#octreeVisVoxelClass0 = lc.rayHitVoxelClass | vg.VOXEL_CLASS_FILLED
#octreeVisVoxelClass0 = vg.VOXEL_CLASS_INSIDE
#octreeVisVoxelClass0 = vg.VOXEL_CLASS_UNDEFINED
#octreeVisVoxelClass0 = (vg.VOXEL_CLASS_FILLED | vg.VOXEL_CLASS_INSIDE 
#    | vg.VOXEL_CLASS_BOUNDARY | lc.rayHitVoxelClass)
#octreeVisVoxelClass0 = (vg.VOXEL_CLASS_INSIDE 
#    | vg.VOXEL_CLASS_BOUNDARY | lc.rayHitVoxelClass)
#octreeVisVoxelClass0 = vg.VOXEL_CLASS_BOUNDARY | vg.VOXEL_CLASS_INSIDE
#octreeVisVoxelClass0 = vg.VOXEL_CLASS_INSIDE
#octreeVisVoxelClass0 = vg.VOXEL_CLASS_BOUNDARY
octreeVisVoxelClass0 = vg.VOXEL_CLASS_FILLED
#octreeVisVoxelClass0 = lc.rayHitVoxelClass
renderOctreeLeavesOnly0 = True
boundaryFacesOnly0 = False
useDataType0 = False
useVoxelClass0 = True
flatFaces0 = False
renderEdges0 = False
enableBackfaceCulling0 = True
renderNodes0 = True
renderRoot0 = False
#region0 = None
region0 = cg.Range3.create()
mm.addLocalRef(region0)
region0.setBounds(cg.Vector3(0., 0., 0.))
region0.extend(cg.Vector3(0.5 * octreeScale, 0.5 * octreeScale, 
    0.5 * octreeScale))

# unit 1
enableUnit1 = True
octreeVisVoxelClass1 = vg.VOXEL_CLASS_INSIDE
renderOctreeLeavesOnly1 = True
useDataType1 = False
useVoxelClass1 = True
boundaryFacesOnly1 = False
flatFaces1 = False
renderEdges1 = True
enableBackfaceCulling1 = False
renderRoot1 = False
renderNodes1 = True
#region1 = None
region1 = region0

print("Creating colors...")

cb0 = ai.ColorBand.rainbow()
mm.addLocalRef(cb0)
cb1 = ai.ColorBand.flame()
mm.addLocalRef(cb1)

colors = ai.ColorSet.create()
mm.addLocalRef(colors)
cb0.sample(numColorsDepth, colors)
cb1.sample(numColorsWallThickness, colors)

cs0 = ai.ColorSet.create()
mm.addLocalRef(cs0)

voxelInsideColor = ai.Color.create("#d21799")
cs0.addColor(voxelInsideColor)
voxelFilledColor = ai.Color.create("#00b385")
cs0.addColor(voxelFilledColor)
voxelHitColor = ai.Color.create("#d2cb17")
cs0.addColor(voxelHitColor)
voxelBoundaryColor = ai.Color.create("#ffa811")
cs0.addColor(voxelBoundaryColor)

voxelClassColors = vg.VoxelClassColorVector()
cc2 = vg.VoxelClassColor()
cc2.voxelClass = vg.VOXEL_CLASS_INSIDE
cc2.color = voxelInsideColor
voxelClassColors.push_back(cc2)
cc3 = vg.VoxelClassColor()
cc3.voxelClass = vg.VOXEL_CLASS_BOUNDARY
cc3.color = voxelBoundaryColor
voxelClassColors.push_back(cc3)
cc1 = vg.VoxelClassColor()
cc1.voxelClass = vg.VOXEL_CLASS_FILLED
cc1.color = voxelFilledColor
voxelClassColors.push_back(cc1)
cc0 = vg.VoxelClassColor()
cc0.voxelClass = lc.rayHitVoxelClass
cc0.color = voxelHitColor
voxelClassColors.push_back(cc0)

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

ggl.enableOpenGLDepthBufferTest()
ggl.setOpenGLLineWidth(lineWidth)

print("  %s" % viewer.getString())

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

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

s1 = 1.
s2 = octreeScale * octreeVisScale * (1. - 2. * m0) / s1
t1 = octreeScale * octreeVisScale * 0.5
vertexOffset = cg.Vector3(-t1, -t1, -t1)
vertexScale = cg.Vector3(octreeVisScale, octreeVisScale, octreeVisScale)
sv0 = cg.Vector3(s2, s2, s2)
tv0 = cg.Vector3(t1, t1, t1)

locOffset = cg.Vector3(cg.Vector3.ZERO)

print("Loading node hierarchy from file '%s'..." % voxelInputFile0)

ioCtx.clear()

ioCtx.openFileForInput(voxelInputFile0)

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)
root0.setID(nodeName0 + '_root')

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

print("  Unit #0:")

if (renderEdges0):
    nFaceType = cg.NFace.TYPE_EDGE
else:
    nFaceType = cg.NFace.TYPE_FACE

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
if (renderOctreeLeavesOnly0):
    nf1.setLeafStatus(vg.NODE_LEAF)
if (useDataType0):
    nf1.setDataType(octreeVisDataType0)
if (useVoxelClass0):
    nf1.setVoxelClass(octreeVisVoxelClass0)
if (not region0 is None):
    nf1.setRegion(region0)

clock0.start()
if (renderNodes0):
    root0.getVertexAttributes(va00, va02, va03, nFaceType, octreeBoxInset, 
        colors, octreeColorOffset, numColorsDepth, vg.COLOR_INDEX_UNSPECIFIED, 
        octreeLeafColorIndex, voxelClassColors, vertexOffset, vertexScale, 
        nf1, True, boundaryFacesOnly0)
if (renderRoot0 and renderEdges0 
    and (renderOctreeLeavesOnly0 or useDataType0)):
    # render the root node itself
    root0.getVertexAttributes(va00, va02, va03, nFaceType, octreeBoxInset, 
        colors, octreeColorOffset, numColorsDepth, 
        vg.COLOR_INDEX_UNSPECIFIED, octreeLeafColorIndex, voxelClassColors, 
        vertexOffset, vertexScale, 
        None, False)
clock0.stop()

va00.update()
va02.update()
va03.update()

t3 = clock0.getElapsedTime()
print("    Vertex attribute creation time:       %f secs" % t3)

numVertexAttribElements0 = va00.getNumElements()
numEdges0 = int(numVertexAttribElements0 / 2)
numFaces0 = int(numVertexAttribElements0 / 3)

print("    Number of vertex attribute elements:  %d" 
    % numVertexAttribElements0)
print("    Number of edges:                      %d" % numEdges0)
print("    Number of faces:                      %d" % numFaces0)

print("    Initializing vertex array object...")

vao0 = ggl.VertexArrayObject.create()
vao0.setID(root0.getID() + "_vao0")
mm.addLocalRef(vao0)
vao0.init()
vao0.addAttribute(va00)
vao0.addAttribute(va01)
vao0.addAttribute(va02)
vao0.addAttribute(va03)
vao0.update()

if enableUnit1:
    print("  Unit #1:")
    
    if (renderEdges1):
        nFaceType = cg.NFace.TYPE_EDGE
    else:
        nFaceType = cg.NFace.TYPE_FACE
    
    # vertices
    va10 = ggl.VertexAttribute.create()
    va10.setID("va10")
    va10.init()
    
    # emit colors
    va11 = ggl.VertexAttribute.create()
    va11.setID("va11")
    
    # diffuse colors
    va12 = ggl.VertexAttribute.create()
    va12.setID("va12")
    va12.init()
    
    # normals
    va13 = ggl.VertexAttribute.create()
    va13.setID("va13")
    va13.init()
    
    nf2 = vg.NodeFilter.create()
    mm.addLocalRef(nf2)
    nf2.setContext(ctx)
    if (renderOctreeLeavesOnly1):
        nf2.setLeafStatus(vg.NODE_LEAF)
    if (useDataType1):
        nf2.setDataType(octreeVisDataType1)
    if (useVoxelClass1):
        nf2.setVoxelClass(octreeVisVoxelClass1)
    if (not region1 is None):
        nf2.setRegion(region1)
    
    clock0.start()
    if (renderNodes1):
        root0.getVertexAttributes(va10, va12, va13, nFaceType, octreeBoxInset, 
            colors, octreeColorOffset, 0, vg.COLOR_INDEX_UNSPECIFIED, 
            octreeLeafColorIndex, voxelClassColors, vertexOffset, vertexScale, 
            nf2, True, boundaryFacesOnly1)
    if (renderRoot1 and renderEdges1 
        and (renderOctreeLeavesOnly1 or useDataType1)):
        # render the root node itself
        root0.getVertexAttributes(va10, va12, va13, nFaceType, octreeBoxInset, 
            colors, octreeColorOffset, 0, vg.COLOR_INDEX_UNSPECIFIED, 
            octreeLeafColorIndex, voxelClassColors, vertexOffset, vertexScale, 
            None, False)
    clock0.stop()
    
    va10.update()
    va12.update()
    va13.update()
    
    t3 = clock0.getElapsedTime()
    print("    Vertex attribute creation time:       %f secs" % t3)
    
    numVertexAttribElements1 = va10.getNumElements()
    numEdges1 = int(numVertexAttribElements1 / 2)
    numFaces1 = int(numVertexAttribElements1 / 3)
    
    print("    Number of vertex attribute elements:  %d" 
        % numVertexAttribElements1)
    print("    Number of edges:                      %d" % numEdges1)
    print("    Number of faces:                      %d" % numFaces1)
    
    print("    Initializing vertex array object...")
    
    vao1 = ggl.VertexArrayObject.create()
    vao1.setID(root0.getID() + "_vao1")
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
    # unit #0
    if (renderEdges0 or flatFaces0):
        updateShaderParams(p0, 1, 0, 0, 0)
    else:
        updateShaderParams(p0, 0, 0, 0, 0)
    vao0.bind()
    if (renderEdges0):
        ggl.enableOpenGLBackFaceCulling(False)
        va00.draw(ggl.PRIMITIVE_LINE, numEdges0)
    else:
        ggl.enableOpenGLBackFaceCulling(enableBackfaceCulling0)
        va00.draw(ggl.PRIMITIVE_TRIANGLE, numFaces0)
    # unit #1
    if (enableUnit1):
        if (renderEdges1 or flatFaces1):
            updateShaderParams(p0, 1, 0, 0, 0)
        else:
            updateShaderParams(p0, 0, 0, 0, 0)
        vao1.bind()
        if (renderEdges1):
            ggl.enableOpenGLBackFaceCulling(False)
            va10.draw(ggl.PRIMITIVE_LINE, numEdges1)
        else:
            ggl.enableOpenGLBackFaceCulling(enableBackfaceCulling1)
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
        if (pitch == -90.):
            pitch = -89.99
        if (pitch == 90.):
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

