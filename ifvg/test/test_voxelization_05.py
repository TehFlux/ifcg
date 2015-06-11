#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Voxelization #5."""
import sys, os
import IFObjectBase as ib
import GeoUtilsFBX as fbx
import CGeoUtils as cg
import Altjira as ai
import AltjiraGeoUtils as ag
import CIFVG as vg
import ifvg_local_config as lc

testName = "Voxelization #5: Part"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

octreeMaxNumLevels = lc.octreeMaxNumLevels
octreeOrder = lc.octreeOrder
octreeScale = lc.octreeScale
octreeMargin = lc.octreeMargin

voxelizeTarget = lc.voxelizeTarget
#voxelizeDepth = lc.voxelizeDepth
voxelizeDepth = 8
voxelizeFillNodes = True
voxelizePruneEmpty = True
pruneEmpty = False

# use existing part voxelizations
usePartVoxelizations = True
# dump part voxelizations to files
dumpPartVoxelizations = True
# merge voxelizations
mergeVoxelizations = True

#nodeName0 = 'NODE_NAME'
#targetName0 = 'target_name'

rootNodeName0 = 'ROOT_NODE'

excludeNodes = [
    # list of node names to be excluded
    'NODE_NAME_EXCLUDE'
]
includeNodes = None
targetName0 = "unnamed_%02d" % voxelizeDepth

dataPath0 = lc.meshPath
dataSetName0 = lc.dataSetName
inFile0 = lc.fbxHierarchyFile

voxelOutputDir0 = (lc.voxelizationPath  + '/' + lc.dataSetName 
    + ('/level_%02d' % voxelizeDepth))
voxelOutputFile0 = voxelOutputDir0 + '/' + targetName0 + '.vgnodeh'

clock0 = cg.Clock()

print("Input data bounding box:")

bb0 = lc.inputDataBoundingBox
ao0 = bb0.getAxisOrder()
s0 = bb0.getExtent(ao0.a0)
e0 = bb0.getExtent()
c0 = bb0.getCenter()
r0 = bb0.getRadius()

print("  bounding box: [%s]" % bb0.getValueString())
print("    center = (%s)" % c0.getValueString())
print("    radius = (%s)" % r0.getValueString())
print("    extent = (%s)" % e0.getValueString())
print("    scale = %f" % s0)

print("Creating octree context...")

ctx = vg.Context.create(octreeMaxNumLevels, octreeOrder, octreeScale)
mm.addLocalRef(ctx)

n0 = ctx.getMaxNumLeafChildNodesPerDimension()
minLeafSize = ctx.getMinLeafSize()
voxelizationLeafSize = ctx.getVoxelSize(voxelizeDepth)
numVoxelsTotal =  n0 * n0 * n0
m0 = voxelizationLeafSize * octreeMargin

print("  max. levels                    = %d" % octreeMaxNumLevels)
print("  order                          = %d" % octreeOrder)
print("  scale                          = %f" % octreeScale)
print("  max. leaf nodes per dimension  = %d" % n0)
print("  min. leaf size                 = %f" % minLeafSize)
print("  number of voxels               = %d" % numVoxelsTotal)

s1 = octreeScale * (1. - 2. * m0) / s0
sv0 = cg.Vector3(s1, s1, s1)
t1 = octreeScale * 0.5
tv0 = cg.Vector3(t1, t1, t1)

print("Using mesh scale: %f" % s1)

print("Loading FBX hierarchy data from file '%s'..." % inFile0)

fbx0 = fbx.FBXNode.create()
mm.addLocalRef(fbx0)

fbx0.loadFromXMLFile(inFile0)

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

print("Using voxelization depth: %d" % voxelizeDepth)

print("Creating root node '%s'..." % targetName0)

numFaces0 = 0
numVerts0 = 0
numFacesInserted = 0
totalFaceInsertionTime = 0.
numVoxelsFilled = 0
totalVoxelizationTime = 0.
numNodesMerged = 0
totalMergeTime = 0.

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)
root0.setID(targetName0)

proc0 = vg.NodeVoxelizationProcessor.create()
mm.addLocalRef(proc0)
proc0.setTarget(voxelizeTarget)

print("Compiling list of nodes...")

iv0 = None
if (not includeNodes is None):
    print("  Including nodes:")
    iv0 = ib.StringVector()
    for it in includeNodes:
        print("    %s" % it)
        iv0.push_back(it)
ev0 = None
if (not excludeNodes is None):
    print("  Excluding nodes:")
    ev0 = ib.StringVector()
    for it in excludeNodes:
        print("    %s" % it)
        ev0.push_back(it)

ns0 = fbx.FBXNodeSet.create()
mm.addLocalRef(ns0)

fbx1 = fbx0
if (not rootNodeName0 is None):
    print("  Searching for root node '%s'..." % rootNodeName0)
    fbx1 = fbx0.findNodeByName(rootNodeName0, True)
    if (fbx1 is None):
        print("  !!! Root node not found.")
        sys.exit(0)

print("Searching for nodes...")

n0 = fbx1.findNodesByName(ns0, iv0, ev0, True)

for i in range(0, ns0.getNumNodes()):
    cn0 = ns0.getNode(i)
    print("  [%03d] %s" % (i, cn0.getName()))

print("  %d nodes found" % n0)

#sys.exit(0)

print("Processing nodes...")

print("  Looking for mesh nodes...")

ns1 = fbx.FBXNodeSet.create()
mm.addLocalRef(ns1)

meshRecursive = True
if (not excludeNodes is None):
    meshRecursive = False
ns0.findNodesByAttributeType(fbx.FBXNode.TYPE_MESH, ns1, meshRecursive)
nm0 = ns1.getNumNodes()

print("  %d mesh nodes found" % nm0)

if (nm0 == 0):
    print("  !!! No mesh nodes found.")
    sys.exit(0)

if (not (dumpPartVoxelizations 
    or mergeVoxelizations)):
    print("Nothing to be done.")
    sys.exit(0)

print("  Voxelizing meshes...")

for i in range(0, nm0):
    cn1 = ns1.getNode(i)
    cid0 = cn1.getID();
    
    print("      [%04d/%04d] mesh node: {%s}[%s]" % (i, nm0, cid0, 
        cn1.getValueString()))
    
    fn0 = (dataPath0 + '/' + dataSetName0 + '/' + cid0 
        + ".vgmesh")
    fn1 = (voxelOutputDir0 + '/' + cid0 
        + ('_level_%02d.vgnodeh' % voxelizeDepth))
    
    root1 = vg.Node.create(ctx)
    mm.addLocalRef(root1)
    
    if (usePartVoxelizations 
        and mergeVoxelizations 
        and (os.path.isfile(fn1))):
        # use existing part voxelization for merging
        print("        Loading voxelization from file '%s'..." % fn1)
        
        ioCtx.clear()
        ioCtx.openFileForInput(fn1)

        clock0.start()
        ioCtx.begin()
        root1.deserializeHierarchy(ioCtx)
        ioCtx.finish()
        clock0.stop()
        
        t0 = clock0.getElapsedTime()
        
        print("          loaded in %f secs" % t0)
        
    elif (dumpPartVoxelizations
        or mergeVoxelizations):
        # voxelize part mesh
        print("        Loading mesh from file '%s'..." % fn0)
        
        cm1 = vg.Mesh.create()
        mm.addLocalRef(cm1)
        
        ioCtx.clear()
        ioCtx.openFileForInput(fn0)
        ioCtx.begin()
        cm1.deserialize(ioCtx)
        ioCtx.finish()
        
        nv1 = cm1.getNumVertices()
        nf1 = cm1.getNumFaces()
        
        bb1 = cm1.getBounds()
        ao1 = bb1.getAxisOrder()
        s1 = bb1.getExtent(ao1.a0)
        e1 = bb1.getExtent()
        c1 = bb1.getCenter()
        
        numVerts0 += nv1
        numFaces0 += nf1
        
        print("        %d vertices, %d faces" % (nv1, nf1))
        print(("        bounding box: [%s] [center = (%s), " 
            + "scale = %f, extent = (%s)]") 
                % (bb1.getValueString(), c1.getValueString(), s1, 
                    e1.getValueString()))
        
        print("        Transforming mesh...")
        
        # center mesh
        cm1.translate(c0.flip())
        
        cm1.scale(sv0)
        cm1.translate(tv0)
        cm1.applyTransform(True)
        cm1.update(False, False)
        
        print("        Inserting faces...")
        
        clock0.start()
        nfi0 = root1.voxelizeInsertFaces(cm1, 
            vg.SEPARABILITY_26, False)
        clock0.stop()
        
        t0 = clock0.getElapsedTime()
        
        facesPerSec = nfi0 / t0
        numFacesInserted += nfi0
        totalFaceInsertionTime += t0
        
        print("          %d faces inserted in %f secs (%f faces/sec)" 
            % (nfi0, t0, facesPerSec))
        
        print("        Voxelizing faces...")
        
        clock0.start()
        nvf0 = root1.voxelizeFaces(proc0, voxelizeDepth, 
            vg.SEPARABILITY_26, voxelizeFillNodes, voxelizePruneEmpty)
        clock0.stop()
        
        t0 = clock0.getElapsedTime()
        
        filledVoxelsPerSec = nvf0 / t0
        numVoxelsFilled += nvf0
        totalVoxelizationTime += t0
        
        print("         Number of voxels set:   %d / %d" 
            % (nvf0, numVoxelsTotal))
        print(("         Voxelization time:      %f secs "
            + "(%f voxels/sec, %f faces/sec)") 
                % (t0, filledVoxelsPerSec, nfi0 / t0))
        
        if (dumpPartVoxelizations):
            print("        Writing voxelization to file: %s" % fn1)
            
            ioCtx.clear()
            ioCtx.openFileForOutput(fn1)
            
            clock0.start()
            ioCtx.begin()
            root1.serializeHierarchy(ioCtx)
            ioCtx.finish()
            clock0.stop()
            
            t0 = clock0.getElapsedTime()
            numBytes0 = ioCtx.getOutputStreamSize()
            
            print("          %d bytes written in %f secs" % (numBytes0, t0))
        
        mm.removeLocalRef(cm1)
    else:
        print("        Nothing to be done.")
    
    if (mergeVoxelizations):
        print("        Merging voxelization...")
        
        clock0.start()
        nnm0 = root0.merge(root1)
        clock0.stop()
        
        t0 = clock0.getElapsedTime()
        
        mergedNodesPerSec = nnm0 / t0
        numNodesMerged += nnm0
        totalMergeTime += t0
        
        print(("         Merging time:           %f secs "
            + "(%f nodes/sec)") % (t0, mergedNodesPerSec))
        
        print("         Allocated size of octree:  %f MiB"
            % (root0.getMemSize(True) / 1e6))
    
    mm.removeLocalRef(root1)
    
print("  %d meshes voxelized (%d vertices, %d faces)" 
    % (nm0, numVerts0, numFaces0))

if (pruneEmpty):
    print("  Pruning empty nodes...")
    
    clock0.start()
    numNodesPruned = root0.pruneEmpty()
    clock0.stop()
    
    t0 = clock0.getElapsedTime()
    
    prunedNodesPerSec = numNodesPruned / t0
    
    print("    Number of nodes pruned:  %d" % numNodesPruned)
    print("    Pruning time:            %f secs (%f voxels/sec)" 
        % (t0, prunedNodesPerSec))

if (totalFaceInsertionTime > 0.):
    print(("  Face insertion time:       %f secs "
        + "(%f faces/sec)") % (totalFaceInsertionTime, 
            numFacesInserted / totalFaceInsertionTime))
if (totalVoxelizationTime > 0.):
    print(("  Voxelization time:         %f secs "
        + "(%f voxels/sec, %f faces/sec)") % (totalVoxelizationTime, 
            numVoxelsFilled / totalVoxelizationTime, 
            numFacesInserted / totalVoxelizationTime))

if (mergeVoxelizations):
    print(("  Merging time:              %f secs "
        + "(%f nodes/sec)") % (totalMergeTime, 
            numNodesMerged / totalMergeTime))
    
    print("  Allocated size of octree:   %f MiB"
        % (root0.getMemSize(True) / 1e6))
    
    print("  Writing voxelization to file: %s" % voxelOutputFile0)
    
    ioCtx.clear()
    ioCtx.openFileForOutput(voxelOutputFile0)
    
    clock0.start()
    ioCtx.begin()
    root0.serializeHierarchy(ioCtx)
    ioCtx.finish()
    clock0.stop()
    
    t0 = clock0.getElapsedTime()
    numBytes0 = ioCtx.getOutputStreamSize()
    
    print("    %d bytes written in %f secs" % (numBytes0, t0))

mm.removeLocalRef(root0)

print("All done!")

