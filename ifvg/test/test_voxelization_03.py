#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Voxelization #2."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import Altjira as ai
import AltjiraGeoUtils as ag
import CIFVG as vg
import ifvg_local_config as lc

testName = "Voxelization #3: Mesh"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

octreeMaxNumLevels = lc.octreeMaxNumLevels
octreeOrder = lc.octreeOrder
octreeScale = lc.octreeScale
octreeMargin = lc.octreeMargin

voxelizeTarget = lc.voxelizeTarget
voxelizeFillNodes = lc.voxelizeFillNodes
voxelizePruneEmpty = True
pruneEmpty = False

partName0 = 'part'

meshInputFile0 = (lc.meshPath + '/' + lc.dataSetName 
    + '/' + partName0 + '.vgmesh')
voxelOutputFile0 = (lc.voxelizationPath  + '/' + lc.dataSetName 
    + '/' + partName0 + '.vgnodeh')

print("Loading mesh '%s'..." % meshInputFile0)

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

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

# center the mesh
mesh0.translate(c1.flip())

print("Creating octree context...")

ctx = vg.Context.create(octreeMaxNumLevels, octreeOrder, octreeScale)
mm.addLocalRef(ctx)

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

s2 = octreeScale * (1. - 2. * m0) / s1
sv0 = cg.Vector3(s2, s2, s2)
t1 = octreeScale * 0.5
tv0 = cg.Vector3(t1, t1, t1)

print("Transforming mesh...")

mesh0.scale(sv0)
mesh0.translate(tv0)
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

print("Creating root node...")

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)
root0.setID(partName0)

print("Inserting faces...")

clock0.start()
numFacesInserted = root0.voxelizeInsertFaces(mesh0, 
    vg.SEPARABILITY_26, False)
clock0.stop()

t0 = clock0.getElapsedTime()

print("  %d faces inserted in %f secs (%f faces/sec)" 
    % (numFacesInserted, t0, numFacesInserted / t0))

print("  Faces per level:")

nf0 = vg.NodeFilter.create()
mm.addLocalRef(nf0)
nf0.setContext(ctx)
nf0.setDataType(vg.Node.DATA_TYPE_FACE_VEC)

ns0 = vg.NodeSet()
for i in range(0, octreeMaxNumLevels):
    nf0.setDepthRange(i, i)
    ns0.clearNodes()
    cn0 = root0.find(ns0, nf0, True)
    cnf0 = 0
    for k in range(0, ns0.getNumNodes()):
        cn = ns0.getNode(k)
        cnf0 += cn.getNumFaces()
    print("    level %d: %d face nodes, %d faces" % (i, cn0, cnf0))
ns0.clearNodes()

print("Voxelizing faces...")

proc0 = vg.NodeVoxelizationProcessor.create()
mm.addLocalRef(proc0)
proc0.setTarget(voxelizeTarget)

clock0.start()
numVoxelsFilled = root0.voxelizeFaces(proc0, vg.DEPTH_UNSPECIFIED, 
    vg.SEPARABILITY_26, voxelizeFillNodes, voxelizePruneEmpty)
clock0.stop()

t0 = clock0.getElapsedTime()

filledVoxelsPerSec = numVoxelsFilled / t0
facesPerSec = numFacesInserted / t0

print("  Number of voxels set:      %d / %d" % (numVoxelsFilled, 
    numVoxelsTotal))
print("  Voxelization time:         %f secs (%f voxels/sec, %f faces/sec)" 
    % (t0, filledVoxelsPerSec, facesPerSec))

if (pruneEmpty):
    print("Pruning empty nodes...")
    
    clock0.start()
    numNodesPruned = root0.pruneEmpty()
    clock0.stop()
    
    t0 = clock0.getElapsedTime()
    
    prunedNodesPerSec = numNodesPruned / t0
    
    print("  Number of nodes pruned:    %d" % numNodesPruned)
    print("  Pruning time:              %f secs (%f voxels/sec)" 
        % (t0, prunedNodesPerSec))

octreeMemSize = root0.getMemSize(True)
bytesPerVoxel = octreeMemSize / numVoxelsFilled

print("  Allocated size of octree:  %d bytes (%f bytes/voxel)" 
    % (octreeMemSize, bytesPerVoxel))

print("  Data nodes per level:")

nf0 = vg.NodeFilter.create()
mm.addLocalRef(nf0)
nf0.setContext(ctx)
nf0.setDataType(vg.Node.DATA_TYPE_ANY_NOT_NULL)

ns0 = vg.NodeSet()
for i in range(0, octreeMaxNumLevels):
    nf0.setDepthRange(i, i)
    ns0.clearNodes()
    cn0 = root0.find(ns0, nf0, True)
    print("    level %d: %d data nodes" % (i, cn0))
    #for k in range(0, ns0.getNumNodes()):
    #    if ((k % 1000) == 0):
    #        cn = ns0.getNode(k)
    #        print("      [%03d] %s" % (k, cn.getValueString()))
ns0.clearNodes()

print("Writing node hierarchy to file '%s'..." % voxelOutputFile0)

ioCtx.clear()
ioCtx.openFileForOutput(voxelOutputFile0)

clock0.start()
ioCtx.begin()
root0.serializeHierarchy(ioCtx)
ioCtx.finish()
clock0.stop()

t0 = clock0.getElapsedTime()
numBytes0 = ioCtx.getOutputStreamSize()

print("  %d bytes written in %f secs" % (numBytes0, t0))

mm.removeLocalRef(root0)

print("All done!")

