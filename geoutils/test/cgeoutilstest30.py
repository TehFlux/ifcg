#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import CGeoUtils as cg
import Altjira as ai

print("Testing GeoUtils...")

def compareScalar(name, c0, cmp0):
    """Compare vectors."""
    result = "FAILED"
    if (cg.eq(c0, cmp0)):
        result = "PASSED"
    print ("  " + name + ": " + str(c0) + " (should be: " + str(cmp0) 
        + ") " + result)

def compareVectors0(name, v0, cmp0):
    """Compare vectors."""
    result = "FAILED"
    if (v0.eq(cmp0)):
        result = "PASSED"
    print ("  " + name + ": " + str(v0) + " (should be: " + str(cmp0) 
        + ", angle = " + str(v0.angle(cmp0) * 180. / math.pi) + "°, length = " 
        + str(v0.norm() / cmp0.norm()) + ") " + result)

def compareVectors1(name0, name1, v0, v1):
    """Compare vectors."""
    print ("  " + name0 + "/" + name1 + ": angle = " + str(v0.angle(v1) 
        * 180. / math.pi) + "°, length = (" + str(v0.norm()) + ", " 
        + str(v1.norm()) + ")")

# Default Blender camera world matrix.
bCamMatrix = cg.Matrix4(
    0.685881, -0.317370, 0.654862, 7.481132, 
    0.727634, 0.312469, -0.610666, -6.507640, 
    -0.010817, 0.895343, 0.445245, 5.343665, 
    0.000000, 0.000000, 0.000000, 1.000000)
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

print("Blender camera:")
compareVectors1('right', 'up', right, up)
compareVectors1('right', 'direction', right, direction)
compareVectors1('direction', 'up', direction, up)

cam0 = cg.Camera()
cs0 = cg.CameraSetupFlags()
cs0.useDirection = True
cs0.useRight = True
cs0.useUp = True
cs0.useLookAt = False
cs0.useSky = False
cs0.useAngle = False
cs0.useLens = True
cam0.setRight(right)
cam0.setUp(up)
cam0.setDirection(direction.flip() * a0)
cam0.setLocation(location)
cam0.setLens(lens)
cam0.validate(cs0)

print("GeoUtils camera:")
compareVectors0("right    ", cam0.getRight(), right)
compareVectors0("up       ", cam0.getUp(), up)
compareVectors0("direction", cam0.getDirection(), direction * a0)
compareVectors0("location ", cam0.getLocation(), location)
compareScalar("lens     ", cam0.getLens(), lens)

print("All done!")
