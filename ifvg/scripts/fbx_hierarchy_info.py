#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG FBX hierarchy info.

This script can be used to obtain information from an FBX hierarchy file."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx
import ifvg_local_config as lc

# memory management
mm = ib.IFObject()

print("IFVG FBX hierarchy info.")

if (len(sys.argv) < 2):
    print("Usage: %s <fbx_hierarchy_file>" % sys.argv[0])
    sys.exit(0)

inFile0 = sys.argv[1]

print("Loading data from file '%s'..." % inFile0)

root0 = fbx.FBXNode.create()
mm.addLocalRef(root0)

clock0 = cg.Clock()

clock0.start()
root0.loadFromXMLFile(inFile0)
clock0.stop()

t0 = clock0.getElapsedTime()

print("  loaded in %f secs" % t0)

print("Calculating hierarchy bounds...")

bb0 = cg.Range3()
if (root0.getHierarchyBounds(bb0)):
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

nv0 = root0.getHierarchyNumVerts()
nf0 = root0.getHierarchyNumFaces()

print("    %d vertices, %d faces" % (nv0, nf0))

print("Looking for mesh nodes...")

ns0 = fbx.FBXNodeSet()
n0 = root0.findNodesByAttributeType(fbx.FBXNode.TYPE_MESH, ns0)

print("    %d mesh nodes found" % n0)

print("All done!")

