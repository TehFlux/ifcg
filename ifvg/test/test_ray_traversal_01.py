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

testName = "Ray traversal #1"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

octreeMaxNumLevels = lc.octreeMaxNumLevels
octreeOrder = lc.octreeOrder
octreeScale = lc.octreeScale
octreeMargin = lc.octreeMargin

rayHitDataType = lc.rayHitDataType
rayHitVoxelClass = lc.rayHitVoxelClass
rayFillNodes = True
rayPruneEmpty = False
pruneEmpty = True

ray0 = cg.Line3.create(
    cg.Vector3(0.2, 0.2, -1.), 
    cg.Vector3(1., 0.3, 3).normalize()
)
mm.addLocalRef(ray0)

nodeName0 = 'ray_test_01'

voxelOutputFile0 = 'temp/' + nodeName0 + '.vgnodeh'

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

print("Creating root node...")

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)
root0.setID(nodeName0)

print("Tracing ray: [%s] ..." % ray0.getValueString())

ni0 = vg.NodeIntersection()

if (not root0.intersectRay(ray0, ni0)):
    print("  !!! Ray does not intersect the root node.")
    sys.exit(0)

print("  root node intersection:")
print("    intersection = [%s]" % vg.getNodeIntersectionValueString(ctx, ni0))

iv0 = cg.Vector3()
iv1 = cg.Vector3()
ray0.eval(ni0.intersection, iv0, iv1)

print("    loc = [(%s), (%s)]" % (iv0.getValueString(), iv1.getValueString()))

## <---- DEBUG -----
#sys.exit(0)
## ----- DEBUG ---->

proc0 = vg.NodeIntersectionProcessor.create()
mm.addLocalRef(proc0)
proc0.setContext(ctx)
proc0.setHitDataType(rayHitDataType)
proc0.setHitVoxelClass(rayHitVoxelClass)
proc0.setRay(ray0)

print("  processor: [%s]" % proc0.getValueString())

nf0 = vg.NodeFilter.create()
mm.addLocalRef(nf0)
nf0.setContext(ctx)
nf0.setMinDepth(octreeMaxNumLevels - 1)

print("  filter:    [%s]" % nf0.getValueString())

# <---- DEBUG -----
if (vg.NodeProcessor.checkFlags(nf0.process(root0), 
    vg.NodeFilter.RESULT_PASS)):
    print("  .o. DEBUG: Root node passes filter.")
# ----- DEBUG ---->

clock0 = cg.Clock()

clock0.start()
numIntersections = root0.intersectRay(ray0, proc0, nf0, True, 
    vg.DEFAULT_TOLERANCE, None, rayFillNodes, rayPruneEmpty)
clock0.stop()

t0 = clock0.getElapsedTime()

print("  %d nodes intersected in %f secs (%f nodes/sec)" 
    % (numIntersections, t0, numIntersections / t0))

if (pruneEmpty):
    print("Pruning empty nodes...")
    
    clock0.start()
    numNodesPruned = root0.pruneEmpty(True)
    clock0.stop()
    
    t0 = clock0.getElapsedTime()
    
    prunedNodesPerSec = numNodesPruned / t0
    
    print("  Number of nodes pruned:    %d" % numNodesPruned)
    print("  Pruning time:              %f secs (%f voxels/sec)" 
        % (t0, prunedNodesPerSec))
    
octreeMemSize = root0.getMemSize(True)
if (numIntersections > 0):
    bytesPerVoxel = octreeMemSize / numIntersections
else:
    bytesPerVoxel = 0

print("  Allocated size of octree:  %d bytes (%f bytes/voxel)" 
    % (octreeMemSize, bytesPerVoxel))

print("  Data nodes of type '%s' with class '%s' per level:" 
    % (vg.Node.getDataTypeString(rayHitDataType), 
        vg.getVoxelClassValueString(rayHitVoxelClass)))

nf1 = vg.NodeFilter.create()
mm.addLocalRef(nf1)
nf1.setContext(ctx)
nf1.setDataType(rayHitDataType)
nf1.setVoxelClass(rayHitVoxelClass) 

ns0 = vg.NodeSet()
for i in range(0, octreeMaxNumLevels):
    nf1.setDepthRange(i, i)
    ns0.clearNodes()
    cn0 = root0.find(ns0, nf1, True)
    print("    level %d: %d nodes" % (i, cn0))
ns0.clearNodes()

print("Writing node hierarchy to file '%s'..." % voxelOutputFile0)

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

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

