#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: FBX scene traversal."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx

testName = "FBX node hierarchy"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed'
dataPath1 = '/home/flux4/recent/p/data'
#inFile0 = dataPath0 + '/unnamed_part.fbx'
inFile0 = dataPath0 + '/unnamed.fbx'

#outFile0 = dataPath1 + '/other/unnamed-part-01.xml'
outFile0 = dataPath1 + '/other/unnamed-01.xml'

m0 = fbx.FBXManager.create()
mm.addLocalRef(m0)
s0 = fbx.FBXScene.create()
mm.addLocalRef(s0)
s0.setFbxManager(m0)

print("  Loading data from file '%s'..." % inFile0)

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

print("All done!")

