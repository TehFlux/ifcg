#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Voxelization #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import Altjira as ai
import AltjiraGeoUtils as ag
import CIFVG as vg

testName = "Voxelization #1: Triangle"

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

print("IFVG test: %s" % testName)

maxNumLevels = 8
order = 2
scale = 4.

voxelizeFillNodes = True
voxelizePruneEmpty = True

triangleVerts0 = [
    cg.Vertex3.create(0.45, 0.3, 0.4), 
    cg.Vertex3.create(3.95, 3.8, 2.6), 
    cg.Vertex3.create(0.9, 3.1, 3.8)
]

triangleColor0 = ai.Color("#8b4067")

s0 = 0.15
triangleScale0 = cg.Vector3(s0, s0, s0)
triangleOffset0 = cg.Vector3(1.3, 2.3, 1.3)

tri0 = createTriMesh(triangleVerts0[0], triangleVerts0[1], 
    triangleVerts0[2], triangleColor0)
mm.addLocalRef(tri0)
tri0.scale(triangleScale0)
tri0.translate(triangleOffset0)
tri0.applyTransform()

print("Creating context...")

ctx = vg.Context.create(maxNumLevels, order, scale)
mm.addLocalRef(ctx)

ctx.printDebugInfo()

n0 = ctx.getMaxNumLeafChildNodesPerDimension()
numVoxelsTotal =  n0 * n0 * n0

print("Creating root node...")

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)

root0.printDebugInfo(True)

print("  minimum leaf size: %f" % ctx.getMinLeafSize())

print("Inserting triangle face...")

f0 = tri0.getFace(0)
f0.setID("Triangle01_f0")

print("  face: [%s]" % f0.getValueString())

tvd0 = vg.TriangleVoxelizationData()
ctx.initTriangleVoxelizationData(f0, tvd0, vg.SEPARABILITY_26)

print("  triangle voxelization data:")

vg.printTriangleVoxelizationDataDebugInfo(tvd0)

if (not root0.voxelizeInsertFace(f0, vg.SEPARABILITY_26, False)):
    print("  !!! Root node does not contain the voxelization.")

print("Voxel tree state:")

root0.printDebugInfo(True)

print("Voxelizing faces...")

numVoxels = root0.voxelizeFaces(vg.Context.DEPTH_UNSPECIFIED, 
    vg.VOXELIZATION_TARGET_DENSITY, vg.SEPARABILITY_26, 
    voxelizeFillNodes, voxelizePruneEmpty)
#root0.pruneEmpty(True)

print("Voxel tree state (after voxelization):")

root0.printDebugInfo(True)

print("Number of voxels set: %d / %d" % (numVoxels, numVoxelsTotal))

mm.removeLocalRef(root0)

print("All done!")

