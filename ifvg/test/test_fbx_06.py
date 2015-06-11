#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: FBX scene traversal."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx
import CIFVG as vg

testName = "FBX mesh extraction #1"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed'
dataPath1 = '/home/flux4/recent/p/data'
dataPath2 = dataPath1 + '/meshes'

#inFile0 = dataPath0 + '/unnamed_part.fbx'
inFile0 = dataPath0 + '/unnamed.fbx'

#outFile0 = dataPath1 + '/other/unnamed-part-01.xml'
outFile0 = dataPath1 + '/other/unnamed-01.xml'

#outFilePath0 = dataPath2 + '/unnamed-part'
outFilePath0 = dataPath2 + '/unnamed'

transformMeshes = True

print("  Loading FBX data from file '%s'..." % inFile0)

m0 = fbx.FBXManager.create()
mm.addLocalRef(m0)
s0 = fbx.FBXScene.create()
mm.addLocalRef(s0)
s0.setFbxManager(m0)

s0.loadFromFile(inFile0)

root0 = s0.getRootNode()
mm.addLocalRef(root0)

print("  Building node hierarchy...")

root0.addChildNodesFBX(True)
numNodes0 = root0.assignNodeIDs("n_")

print("    %d nodes processed" % numNodes0)

print("  Updating transformations...")

root0.updateTransformFBX(True)

print("  Updating mesh data...")

root0.updateMeshDataFBX(True)

print("  Updating bounds...")

root0.updateBoundsFBX(True)

bb0 = cg.Range3()
if (root0.getHierarchyBounds(bb0)):
    ao0 = bb0.getAxisOrder()
    s0 = bb0.getExtent(ao0.a0)
    e0 = bb0.getExtent()
    c0 = bb0.getCenter()
    print("    bounding box: [%s] [center = (%s), scale = %f, extent = (%s)]" 
        % (bb0.getValueString(), c0.getValueString(), s0, 
            e0.getValueString()))

print("  Writing hierarchy to file '%s'..." % outFile0)

root0.writeToXMLFile(outFile0)

print("  Looking for mesh nodes...")

ns0 = fbx.FBXNodeSet()
n0 = root0.findNodesByAttributeType(fbx.FBXNode.TYPE_MESH, ns0)

n1 = ns0.getNumNodes()

print("    %d mesh nodes found" % n1)

ioCtx = ib.IFIOContext.create()
mm.addLocalRef(ioCtx)

print("Writing meshes to file...")

clock0 = cg.Clock()

clock0.start()
k = 0
bytesTotal = 0
for i in range(0, n1):
    cn = ns0.getNode(i)
    nid0 = cn.getID()
    print("    [%04d] {%s}[%s]" % (k, cn.getID(), cn.getValueString()))
    fn0 = outFilePath0 + "/" + nid0 + ".vgmesh"
    cm0 = vg.Mesh.create()
    mm.addLocalRef(cm0)
    cm0.setID(nid0)
    cm0.setIDNum(cn.getIDNum())
    cn.getMesh(cm0, False, None, False)
    ct0 = cn.getGlobalTransform()
    if (transformMeshes 
        and (not ct0 is None)):
        cm0.transform(ct0)
        cm0.applyTransform(True)
    print("      mesh: %d verts, %d faces" % (cm0.getNumVertices(), 
        cm0.getNumFaces()))
    print("      --> %s" % fn0)
    ioCtx.clear()
    ioCtx.openFileForOutput(fn0)
    ioCtx.begin()
    cm0.serialize(ioCtx)
    ioCtx.finish()
    s0 = ioCtx.getOutputStreamSize()
    bytesTotal += s0
    print("      %d bytes written, %d bytes total (%f MiB)" 
        % (s0, bytesTotal, bytesTotal / 1000000))
    mm.removeLocalRef(cm0)
    k += 1

clock0.stop()
t0 = clock0.getElapsedTime()

print(("  %d meshes dumped in %f secs, %d bytes total (%f MiB)") 
        % (k, t0, bytesTotal, bytesTotal / 1000000))

print("All done!")

