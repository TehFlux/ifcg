#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import CGeoUtils as cg
import Altjira as ai

print("Testing GeoUtils...")

outFile0 = 'temp' + os.path.sep + 'cube04g.svg'
cubeScale = 2.
imageWidth = 1024
imageHeight = 768
imageScale = imageWidth
numStyles = 6
MATRIX_TOLERANCE = 1e-5
LENS_TOLERANCE = 1e-4

# Cube transform matrix from cube03.blend
t0 = cg.Matrix4(
    0.785901, 0.430357, 0.444019, 0.933393, 
    -0.440122, 0.893695, -0.087192, 0.015805, 
    -0.434341, -0.126898, 0.891765, 0.684029, 
    0.000000, 0.000000, 0.000000, 1.000000)
# Cube transform matrix from cube04+.blend
t1 = cg.Matrix4(
    0.828808, 0.553586, -0.081358, 0.904233, 
    -0.540801, 0.755241, -0.370332, 0.000000, 
    -0.143565, 0.350933, 0.925330, 0.000000, 
    0.000000, 0.000000, 0.000000, 1.000000)
tCube = t1

# Camera matrix from cube02.blend/cube03.blend
bCamMatrix0 = cg.Matrix4(
    -0.892515, -0.348676, 0.286080, 1.977419, 
    0.451018, -0.689992, 0.566122, 3.913095, 
    0.000000, 0.634299, 0.773087, 5.343665, 
    0.000000, 0.000000, 0.000000, 1.000000)
# Camera matrix from cube04.blend
bCamMatrix1 = cg.Matrix4(
    1.000000, 0.000000, 0.000000, 0.000000, 
    0.000000, -0.000001, -1.000000, -5.968145, 
    0.000000, 1.000000, -0.000001, 0.000000, 
    0.000000, 0.000000, 0.000000, 1.000000)
# Camera matrix from cube05.blend
bCamMatrix2 = cg.Matrix4(
    0.965931, -0.000000, -0.258800, 0.000000, 
    -0.258800, -0.000001, -0.965931, -5.968145, 
    0.000000, 1.000000, -0.000001, 0.000000, 
    0.000000, 0.000000, 0.000000, 1.000000)
# Camera matrix from cube06.blend
bCamMatrix3 = cg.Matrix4(
    0.965931, -0.000000, -0.258800, -0.405134, 
    -0.258800, -0.000001, -0.965931, -5.005950, 
    0.000000, 1.000000, -0.000001, 0.000000, 
    0.000000, 0.000000, 0.000000, 1.000000)
# Camera matrix from cube07.blend
bCamMatrix4 = cg.Matrix4(
    0.965931, -0.000000, -0.258800, -0.405134, 
    -0.258800, -0.000001, -0.965931, -6.170712, 
    0.000000, 1.000000, -0.000001, 0.405135, 
    0.000000, 0.000000, 0.000000, 1.000000)
# Camera matrix from cube08.blend
bCamMatrix5 = cg.Matrix4(
    0.877905, -0.402871, -0.258800, -0.405134, 
    -0.235215, 0.107940, -0.965931, -6.170712, 
    0.417080, 0.908870, -0.000001, 0.405135, 
    0.000000, 0.000000, 0.000000, 1.000000)

# Blender camera world matrix.
bCamMatrix = bCamMatrix5
# Default Blender camera lens.
bCamLens = 35

right = bCamMatrix.getC0().getV3()
up = bCamMatrix.getC1().getV3()
direction = bCamMatrix.getC2().getV3()
location = bCamMatrix.getC3().getV3()
lens = bCamLens
angle = 2. * math.atan(16. / bCamLens)

# Adjustment for direction vector based on camera angle, required since 
# the CGeoUtils camera includes the angle in the direction vector. Also 
# flips the direction vector since the Z axis of the local coordinate system 
# of the Blender camera points away from the direction the camera is looking.
a0 = -0.5 / math.tan(0.5 * angle)

def compareScalar(name, c0, cmp0, t = cg.DEFAULT_TOLERANCE):
    """Compare vectors."""
    result = "FAILED"
    if (cg.eq(c0, cmp0, t)):
        result = "PASSED"
    print ("  " + name + ": " + str(c0) + " (should be: " + str(cmp0) 
        + ") " + result)
    if (result == "PASSED"):
        return 0
    return 1

def compareVectors0(name, v0, cmp0):
    """Compare vectors."""
    result = "FAILED"
    if (v0.eq(cmp0)):
        result = "PASSED"
    print ("  " + name + ": " + str(v0) + " (should be: " + str(cmp0) 
        + ", angle = " + str(v0.angle(cmp0) * 180. / math.pi) + "°, length = " 
        + str(v0.norm() / cmp0.norm()) + ") " + result)
    if (result == "PASSED"):
        return 0
    return 1

def compareVectors1(name0, name1, v0, v1):
    """Compare vectors."""
    print ("  " + name0 + "/" + name1 + ": angle = " + str(v0.angle(v1) 
        * 180. / math.pi) + "°, length = (" + str(v0.norm()) + ", " 
        + str(v1.norm()) + ")")
    return 0

def compareMatrices(name, m0, m1, t = cg.DEFAULT_TOLERANCE):
    """Compare vectors."""
    result = "FAILED"
    if (m0.eq(m1, t)):
        result = "PASSED"
    print ("  " + name + ": " + str(m0) + " (should be: " + str(m1) 
        + ") " + result)
    if (result == "PASSED"):
        return 0
    return 1

def checkCamera(cam, m, lens):
    """Check camera.
    
    Compare the camera vectors with a Blender camera world matrix and print 
    the results."""
    result = 0
    print("Camera:                 " + str(cam))
    print("Blender camera matrix:  " + str(m))
    print("Blender camera lens:    " + str(lens))
    right = m.getC0().getV3()
    up = m.getC1().getV3()
    direction = m.getC2().getV3()
    location = m.getC3().getV3()
    angle = 2. * math.atan(16. / lens)
    a0 = -0.5 / math.tan(0.5 * angle)
    print("Blender camera:")
    result += compareVectors1('right', 'up', right, up)
    result += compareVectors1('right', 'direction', right, direction)
    result += compareVectors1('direction', 'up', direction, up)
    print("GeoUtils camera:")
    result += compareVectors0("right    ", cam.getRight(), right)
    result += compareVectors0("up       ", cam.getUp(), up)
    result += compareVectors0("direction", cam.getDirection(), direction * a0)
    result += compareVectors0("location ", cam.getLocation(), location)
    result += compareScalar("lens     ", cam.getLens(), lens, LENS_TOLERANCE)
    # Vectors extracted from transform matrix should match camera vectors.
    T = cam.getTranslationMatrix(False)
    R = cam.getRotationMatrix()
    TR = T * R
    right0 = TR.getC0().getV3()
    direction0 = TR.getC1().getV3()
    up0 = TR.getC2().getV3()
    location0 = TR.getC3().getV3()
    print("GeoUtils camera (extracted from camera matrix):")
    result += compareVectors0("right    ", right0, cam.getRight())
    result += compareVectors0("up       ", up0, cam.getUp())
    # Multiply direction from the matrix by -a0 since direction (as an input 
    # vector) includes perspective while the matrix does not. The minus 
    # undoes the flipping of the depth axis contained in a0.
    result += compareVectors0("direction", direction0 * -a0, cam.getDirection())
    result += compareVectors0("location ", location0, cam.getLocation())
    # Comparison oddities:
    # > direction and up need to be swapped in the blender matrix (possibly 
    #   because Blender uses Z as the depth axis in the camera system).
    # > Y-coordinates need to be flipped after the (CGeoUtils) view 
    #   transformation (possibly because the Blender depth axis points in the 
    #   other direction).
    bm0 = cg.Matrix4(m)
    bm1 = bm0.permuteColumns(0, 2, 1, 3)
    bmInv = bm1.invert()
    xm0 = cg.Matrix4(cg.Matrix4.UNIT)
    xm0.setElement(1, 1, -1.)
    gm0 = cam.getViewMatrix(cg.Camera.MODE_ORTHO, False)
    gm0.multiplyLeft(xm0)
    result += compareMatrices("matrix   ", gm0, bmInv, MATRIX_TOLERANCE)
    if (result == 0):
        print("  (***) PASSED all tests!")
    else:
        print("  (!!!) FAILED some tests.")

print("  Creating styles...")

colors = ai.ColorVector()
c0 = ai.createFloatColor(0.3, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
c1 = ai.createFloatColor(0.8, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
ai.createColors(colors, c0, c1, numStyles, 1, 1)
numColors = colors.size()

styles = []
styleSource = cg.SVGShapeStyleVectorSource.create()

st0 = cg.getSVGShapeStyle("#707070", 0.7, "#000000", 1., 0.)
styleSource.addStyle(st0)
styleSource.addStyle(st0)
st1 = cg.getSVGShapeStyle("#707070", 0.0, "#707070", 1., 1.)
styleSource.addStyle(st1)
styleSource.addStyle(st1)

for i in range(0, numColors):
    c = colors[i]
    ch0 = c.getHex()
    print(("    c%02d = " % i) + ch0)
    s0 = cg.getSVGShapeStyle(ch0[:7], c.getAlpha(), "#000000", 1., 1.)
    styles += [s0]
    styleSource.addStyle(s0)

print("  Creating cube mesh...")
g0 = cg.TransformableGroup()
c0 = cg.Mesh.cube()
g0.addItem(c0)
c0.scale(cg.Vector3(cubeScale, cubeScale, cubeScale))
if (not tCube is None):
    print("WARNING: Transforming cube mesh!")
    c0.transform(tCube)
c0.applyTransform()

print("  Creating camera...")
cam0 = cg.Camera()
cs0 = cg.CameraSetupFlags()
cs0.useDirection = True
cs0.useRight = True
cs0.useUp = True
cs0.useLookAt = False
cs0.useSky = True
cs0.useAngle = False
cs0.useLens = False
cam0.setRight(right)
cam0.setUp(up)
cam0.setDirection(direction * a0)
cam0.setLocation(location)
cam0.setLens(lens)
cam0.validate(cs0)
checkCamera(cam0, bCamMatrix, bCamLens)
#V = cam0.getViewMatrix(cg.Camera.MODE_PERSPECTIVE, False)
V = cam0.getViewMatrix()
I = cg.Matrix4.scale(imageScale, imageScale, imageScale)

print("  Transforming mesh...")
c0.transformVI(V, I)
c0.applyTransform()
#c0.removeBackfaces(cg.Vector3.E_Y.flip())

ps0 = cg.Polygon3Set()
c0.getPolygons(ps0)
ps0.sort(cg.Polygon3CompareAxis.create(cg.AXIS_Y))

ps1 = cg.Polygon3Set()
sq0 = cg.Polygon3.square()
sq0.scale(cg.Vector3(imageWidth, 1., 1.))
sq1 = cg.Polygon3.square()
sq1.scale(cg.Vector3(1., 1., imageHeight))
sq1.translate(cg.Vector3(0.5, 0., 0.))
ci0 = cg.Polygon3.circle(100)
ci0.scale(cg.Vector3(0.4 * imageWidth, 1., 0.4 * imageWidth))
ci1 = cg.Polygon3.circle(100)
ci1.scale(cg.Vector3(0.1 * imageWidth, 1., 0.1 * imageWidth))

ps1.addPolygon(sq0)
ps1.addPolygon(sq1)
ps1.addPolygon(ci0)
ps1.addPolygon(ci1)
ps1.addPolygons(ps0)

ip0 = cg.SVGImageProperties()
ip0.setFileName(outFile0)
ip0.setStyleSource(styleSource)
ip0.setWidth(imageWidth)
ip0.setHeight(imageHeight)
ip0.setOrigin(cg.Vector2(imageWidth / 2, imageHeight / 2))
ps1.writeSVG(ip0, "polygon", cg.AXIS_Y)

print("All done!")
