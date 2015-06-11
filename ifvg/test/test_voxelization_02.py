#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Voxelization #2."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import Altjira as ai
import AltjiraGeoUtils as ag
import CIFVG as vg

testName = "Voxelization #2: Mesh"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataDir0 = '/home/flux4/recent/p/data'
meshDir0 = dataDir0 + '/meshes'
meshFile0 = meshDir0 + '/unnamed-part-01.xml'

octreeMaxNumLevels = 7
octreeOrder = 2
octreeScale = 4.
octreeMargin = 4

voxelizeFillNodes = True
voxelizePruneEmpty = False

color0 = ai.Color("#8b4067")

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

print("Creating context...")

ctx = vg.Context.create(octreeMaxNumLevels, octreeOrder, octreeScale)
mm.addLocalRef(ctx)

#ctx.printDebugInfo()

n0 = ctx.getMaxNumLeafChildNodesPerDimension()
minLeafSize = ctx.getMinLeafSize()
numVoxelsTotal =  n0 * n0 * n0
m0 = minLeafSize * octreeMargin

print("  max. levels                    = %d" % octreeMaxNumLevels)
print("  order                          = %d" % octreeOrder)
print("  scale                          = %f" % octreeScale)
print("  max. leaf nodes per dimension  = %d" % n0)
print("  min. leaf size                 = %f" % minLeafSize)
print("  number of voxels               = %d" % numVoxelsTotal)

print("Transforming mesh...")

s1 = octreeScale * (1. - 2. * m0) / s0
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
mm.addLocalRef(root0)

#root0.printDebugInfo(True)

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
numNodesPruned = root0.pruneEmpty()
clock0.stop()

t0 = clock0.getElapsedTime()

prunedNodesPerSec = numNodesPruned / t0

print("  Pruning time:              %f secs (%f voxels/sec)" 
    % (t0, prunedNodesPerSec))

octreeMemSize = root0.getMemSize(True)
bytesPerVoxel = octreeMemSize / numVoxelsFilled

print("  Allocated size of octree:  %d bytes (%f bytes/voxel)" 
    % (octreeMemSize, bytesPerVoxel))

mm.removeLocalRef(root0)

print("All done!")

