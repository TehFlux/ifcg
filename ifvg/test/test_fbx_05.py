#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: FBX scene traversal."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx

testName = "FBX node hierarchy #2"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed'
dataPath1 = '/home/flux4/recent/p/data'

#inFile0 = dataPath1 + '/other/unnamed-part-01.xml'
inFile0 = dataPath1 + '/other/unnamed-01.xml'

print("  Loading data from file '%s'..." % inFile0)

root0 = fbx.FBXNode.create()
mm.addLocalRef(root0)

root0.loadFromXMLFile(inFile0)

print("  Calculating hierarchy bounds...")

bb0 = cg.Range3()
if (root0.getHierarchyBounds(bb0)):
    ao0 = bb0.getAxisOrder()
    s0 = bb0.getExtent(ao0.a0)
    e0 = bb0.getExtent()
    c0 = bb0.getCenter()
    print("    bounding box: [%s] [center = (%s), scale = %f, extent = (%s)]" 
        % (bb0.getValueString(), c0.getValueString(), s0, 
            e0.getValueString()))

nv0 = root0.getHierarchyNumVerts()
nf0 = root0.getHierarchyNumFaces()

print("    %d vertices, %d faces" % (nv0, nf0))

print("  Looking for mesh nodes...")

ns0 = fbx.FBXNodeSet()
n0 = root0.findNodesByAttributeType(fbx.FBXNode.TYPE_MESH, ns0)

#n1 = ns0.getNumNodes()
#k = 0
#for i in range(0, n1):
#    cn = ns0.getNode(i)
#    print("    [%04d] {%s}[%s]" % (k, cn.getID(), cn.getValueString()))
#    k += 1

print("    %d mesh nodes found" % n0)

print("All done!")

