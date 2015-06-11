#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Ray traversal #3."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import Altjira as ai
import AltjiraGeoUtils as ag
import CIFVG as vg
import ifvg_local_config as lc

testName = "Ray traversal #3: Icosphere (ray grid)"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

octreeMaxNumLevels = lc.octreeMaxNumLevels
octreeOrder = lc.octreeOrder
octreeScale = lc.octreeScale
octreeMargin = lc.octreeMargin

rayHitDataType = lc.rayHitDataType
rayHitVoxelClass = lc.rayHitVoxelClass
rayFillNodes = False
rayPruneEmpty = False
pruneEmpty = False
fillNonLeaves = True
enableX = True
enableY = True
enableZ = True

voxelizeDepth = 7

insideVoteThreshold = 0.9
insideMinVotes = 1

numColorsDepth = 2 * octreeMaxNumLevels
numColorsWallThickness = 20
minColorIndex = numColorsDepth
maxColorIndex = minColorIndex + numColorsWallThickness - 1
maxVisWallThickness = 20

minWallThickness = 20

nodeName0 = 'icosphere_ray_02'

voxelInputFile0 = 'temp/icosphere01.vgnodeh'
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

print("Loading node hierarchy from file '%s'..." % voxelInputFile0)

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

ioCtx.openFileForInput(voxelInputFile0)

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)

clock0 = cg.Clock()

clock0.start()
ioCtx.begin()
root0.deserializeHierarchy(ioCtx)
ioCtx.finish()
clock0.stop()

t0 = clock0.getElapsedTime()

print("  loaded in %f secs" % t0)

if (fillNonLeaves):
    print("  Filling non-leaf nodes...")
    
    fp0 = vg.NodeFillProcessor.create(ctx, False, False, 
        vg.DEPTH_UNSPECIFIED)
    mm.addLocalRef(fp0)
    
    nf2 = vg.NodeFilter.create()
    mm.addLocalRef(nf2)
    nf2.setContext(ctx)
    nf2.setLeafStatus(vg.NODE_NON_LEAF)
    
    print("    filter:    [%s]" % nf2.getValueString())
    
    clock0.start()
    numNodesFilled = root0.process(None, nf2, fp0, True)
    clock0.stop()
    
    t0 = clock0.getElapsedTime()
    
    filledNodesPerSec = numNodesFilled / t0
    
    print("    Number of nodes filled:    %d" % numNodesFilled)
    print("    Filling time:              %f secs (%f voxels/sec)" 
        % (t0, filledNodesPerSec))

maxDepth0 = root0.getMaxDepth()
memSize0 = root0.getMemSize(True)

print("  max. depth     = %d" % maxDepth0)
print("  allocated size = %d bytes" % memSize0)

#nt0 = vg.Node.DATA_TYPE_VOXEL_CLASS
nt0 = vg.Node.DATA_TYPE_UNKNOWN
#vc0 = vg.VOXEL_CLASS_FILLED
vc0 = vg.VOXEL_CLASS_UNDEFINED
ls0 = vg.NODE_LEAF

nf0 = vg.NodeFilter.create()
mm.addLocalRef(nf0)
nf0.setContext(ctx)
nf0.setDataType(nt0)
nf0.setVoxelClass(vc0)
nf0.setLeafStatus(ls0)

print("  filter:    [%s]" % nf0.getValueString())

print("  Data nodes of type '%s', class '%s', leaf status '%s' per level:" 
    % (vg.Node.getDataTypeString(nt0), vg.getVoxelClassValueString(vc0), 
        vg.getLeafStatusValueString(ls0)))

ns0 = vg.NodeSet()
voxelSize0 = 0.
for i in range(0, octreeMaxNumLevels):
    nf0.setDepthRange(i, i)
    ns0.clearNodes()
    cn0 = root0.find(ns0, nf0, True)
    print("    level %d: %d nodes" % (i, cn0))
    if (cn0 != 0):
        voxelSize0 = ctx.getVoxelSize(i)
ns0.clearNodes()

nf0.setDepthRange(vg.DEPTH_UNSPECIFIED, vg.DEPTH_UNSPECIFIED)

rayStepX = cg.Vector3(voxelSize0, 0., 0.)
rayStepY = cg.Vector3(0., voxelSize0, 0.)

proc0 = vg.NodeIntersectionProcessor.create()
mm.addLocalRef(proc0)
proc0.setContext(ctx)
proc0.setHitDataType(rayHitDataType)
proc0.setVoxelClassHit(rayHitVoxelClass)
#proc0.setEnableBoundaryData(True)
proc0.setTargetDepth(voxelizeDepth)
proc0.setEnableRayStabbing(True)

numRaysXY = int(octreeScale / ctx.getVoxelSize(voxelizeDepth))
numRays = 3 * numRaysXY * numRaysXY

print("Interior/exterior pass...")

print("  processor: [%s]" % proc0.getValueString())

print("  Tracing %d rays..." % numRays)

clock0.start()
numIntersections = 0
if (enableX):
    numIntersections += root0.castRayGrid(cg.AXIS_X, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
if (enableY):
    numIntersections += root0.castRayGrid(cg.AXIS_Y, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
if (enableZ):
    numIntersections += root0.castRayGrid(cg.AXIS_Z, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
clock0.stop()

t0 = clock0.getElapsedTime()

intersectionsPerSec = numIntersections / t0
raysPerSec = numRays / t0

print(("    %d rays cast, %d nodes intersected in %f secs "
    + "(%f rays/sec, %f nodes/sec)") 
        % (numRays, numIntersections, t0, raysPerSec, intersectionsPerSec))

print("  Processing nodes (ray vote evaluation)...")

iobProc0 = vg.NodeIOBEvalProcessor.create(ctx)
iobProc0.setInsideVoteThreshold(insideVoteThreshold)
iobProc0.setInsideMinVotes(insideMinVotes)
mm.addLocalRef(iobProc0)

nf3 = vg.NodeFilter.create()
mm.addLocalRef(nf3)
nf3.setContext(ctx)
nf3.setLeafStatus(vg.NODE_LEAF)

print("    filter:    [%s]" % nf3.getValueString())

clock0.start()
numNodesProcessed = root0.process(None, nf3, iobProc0, True)
clock0.stop()

t0 = clock0.getElapsedTime()

processedNodesPerSec = numNodesProcessed / t0

print("    Number of nodes processed:  %d" % numNodesProcessed)
print("    Processing time:            %f secs (%f voxels/sec)" 
    % (t0, processedNodesPerSec))

print("Wall thickness pass...")

proc0.setEnableIOB(False)
proc0.setEnableWallThickness(True)
#proc0.setMinWallThickness(minWallThickness)
#proc0.setFillInsideOnly(False)
#proc0.setMaxNumWallThicknessPasses(1)

print("  processor: [%s]" % proc0.getValueString())

print("  Tracing %d rays..." % numRays)

clock0.start()
numIntersections = 0
if (enableX):
    numIntersections += root0.castRayGrid(cg.AXIS_X, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
if (enableY):
    numIntersections += root0.castRayGrid(cg.AXIS_Y, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
if (enableZ):
    numIntersections += root0.castRayGrid(cg.AXIS_Z, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
clock0.stop()

t0 = clock0.getElapsedTime()

intersectionsPerSec = numIntersections / t0
raysPerSec = numRays / t0

print(("    %d rays cast, %d nodes intersected in %f secs "
    + "(%f rays/sec, %f nodes/sec)") 
        % (numRays, numIntersections, t0, raysPerSec, intersectionsPerSec))

print("  Processing nodes (wall thickness)...")

wtProc0 = vg.NodeIOBWallThicknessProcessor.create(ctx)
wtProc0.setEnableScanWallThickness(True)
wtProc0.setMinColorIndex(minColorIndex)
wtProc0.setMaxColorIndex(maxColorIndex)
mm.addLocalRef(wtProc0)

nf4 = vg.NodeFilter.create()
mm.addLocalRef(nf4)
nf4.setContext(ctx)
nf4.setMinDepth(voxelizeDepth)
nf4.setMaxDepth(voxelizeDepth)
nf4.setVoxelClass(vg.VOXEL_CLASS_FILLED)
nf4.setLeafStatus(vg.NODE_LEAF)

print("    filter:    [%s]" % nf4.getValueString())

clock0.start()
numNodesProcessed = root0.process(None, nf4, wtProc0, True)
minWallThickness0 = wtProc0.getMinWallThickness()
maxWallThickness0 = wtProc0.getMaxWallThickness()
# second pass: assign color indices
wtProc0.setEnableScanWallThickness(False)
if (minWallThickness0 > maxVisWallThickness):
    wtProc0.setMinWallThickness(maxVisWallThickness)
wtProc0.setMaxWallThickness(maxVisWallThickness)
numNodesProcessed = root0.process(None, nf4, wtProc0, True)
clock0.stop()

t0 = clock0.getElapsedTime()

processedNodesPerSec = numNodesProcessed / t0

print("    Number of nodes processed:  %d" % numNodesProcessed)
print("    Processing time:            %f secs (%f voxels/sec)" 
    % (t0, processedNodesPerSec))
print("    Wall thickness range:       %d - %d" 
    % (minWallThickness0, maxWallThickness0))

print("Boundary pass...")

proc0.setEnableWallThickness(False)
proc0.setEnableBoundaryData(True)

print("  processor: [%s]" % proc0.getValueString())

print("  Tracing %d rays..." % numRays)

clock0.start()
numIntersections = 0
if (enableX):
    numIntersections += root0.castRayGrid(cg.AXIS_X, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
if (enableY):
    numIntersections += root0.castRayGrid(cg.AXIS_Y, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
if (enableZ):
    numIntersections += root0.castRayGrid(cg.AXIS_Z, voxelizeDepth, 
        vg.Node.DEFAULT_RAY_PLANE_OFFSET, proc0, nf0, True, 
        vg.DEFAULT_TOLERANCE, rayFillNodes, rayPruneEmpty)
clock0.stop()

t0 = clock0.getElapsedTime()

intersectionsPerSec = numIntersections / t0
raysPerSec = numRays / t0

print(("    %d rays cast, %d nodes intersected in %f secs "
    + "(%f rays/sec, %f nodes/sec)") 
        % (numRays, numIntersections, t0, raysPerSec, intersectionsPerSec))

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

vc1 = rayHitVoxelClass
#vc1 = vg.VOXEL_CLASS_UNDEFINED

print("  Data nodes with class '%s' per level:" 
    % vg.getVoxelClassValueString(vc1))

nf1 = vg.NodeFilter.create()
mm.addLocalRef(nf1)
nf1.setContext(ctx)
#nf1.setDataType(rayHitDataType)
nf1.setVoxelClass(vc1) 

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

