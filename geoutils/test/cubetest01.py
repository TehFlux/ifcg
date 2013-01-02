#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os, sys
sys.path.append('/Users/jmeier/usr/python3.1/lib/python3.1/site-packages')
sys.path.append('/Users/jmeier/svn/stuff/trunk/geoutils/python')

import CGeoUtils as cg

outputPath = '/Users/jmeier/svn/stuff/trunk/geoutils/temp'
outFile0 = outputPath + os.path.sep + 'cubetest01.png'

# Cube transform matrix from cube04+.blend
t1 = cg.Matrix4(
    0.828808, 0.553586, -0.081358, 0.904233, 
    -0.540801, 0.755241, -0.370332, 0.000000, 
    -0.143565, 0.350933, 0.925330, 0.000000, 
    0.000000, 0.000000, 0.000000, 1.000000)

# Camera matrix from cube08.blend
bCamMatrix5 = cg.Matrix4(
    0.877905, -0.402871, -0.258800, -0.405134, 
    -0.235215, 0.107940, -0.965931, -6.170712, 
    0.417080, 0.908870, -0.000001, 0.405135, 
    0.000000, 0.000000, 0.000000, 1.000000)

def getBlenderVector(v0):
    """Create a Blender (compatible) vector specification from a CGeoUtils 
       vector."""
    return [ v0[0], v0[1], v0[2], v0[3] ]

def getBlenderMatrix(m0):
    """Create a Blender (compatible) matrix specification from a CGeoUtils 
       matrix."""
    return [
        getBlenderVector(m0.getC0()), 
        getBlenderVector(m0.getC1()), 
        getBlenderVector(m0.getC2()), 
        getBlenderVector(m0.getC3())
    ]

c0 = bpy.data.objects.get('Cube')
c0.matrix_world = getBlenderMatrix(t1)
cam0 = bpy.data.objects.get('Camera')
cam0.matrix_world = getBlenderMatrix(bCamMatrix5)

s0 = bpy.context.scene
r0 = s0.render
r0.resolution_x = 1024
r0.resolution_y = 768
r0.resolution_percentage = 100
r0.alpha_mode = 'PREMUL'
r0.color_mode = 'RGBA'
r0.filepath = outputPath
r0.file_format = 'PNG'

bpy.ops.render.render()

img0 = bpy.data.images.get("Render Result")
img0.save_render(outFile0)
