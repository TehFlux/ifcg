#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Octree #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import CIFVG as vg

testName = "Octree #1"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

def locatePoints(points, node):
    """Locate points."""
    k = 0
    while (k < len(points0)):
        cp = points0[k]
        print("  [%03d] (%s)" % (k, cp.getValueString()))
        n0 = root0.locateChild(cp)
        mm.addLocalRef(n0)
        #print("    %s" % n0.getString())
        loc0 = n0.getLocation()
        depth0 = n0.getDepth()
        s0 = ctx.getVoxelSize(depth0)
        #print("    depth = %d, loc = (%s), size = %f" % (depth0, 
        #    loc0.getValueString(), s0))
        n0.printDebugInfo()
        mm.removeLocalRef(n0)
        k += 1

maxNumLevels = 4
order = 2
scale = 4.

points0 = [
    cg.Vector3.create(0.25, 0.25, 0.25), 
    cg.Vector3.create(0.75, 0.25, 0.25), 
    cg.Vector3.create(0.25, 0.75, 0.25), 
    cg.Vector3.create(0.75, 0.75, 0.25), 
    cg.Vector3.create(0.25, 0.25, 0.75), 
    cg.Vector3.create(0.75, 0.25, 0.75), 
    cg.Vector3.create(0.25, 0.75, 0.75), 
    cg.Vector3.create(0.75, 0.75, 0.75)
]

for it in points0:
    mm.addLocalRef(it)

print("Creating context...")

ctx = vg.Context.create(maxNumLevels, order, scale)
mm.addLocalRef(ctx)

ctx.printDebugInfo()

print("Creating root node...")

#rootImpl = vg.Node.createImpl()
#vg.Node.refImpl(rootImpl)

#print("  %s" % vg.Node.getImplValueString(rootImpl, ctx))

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)

#print("  %s" % root0.getString())
root0.printDebugInfo(True)

#print("Testing point location:")

#locatePoints(points0, root0)

print("Adding nodes...")

n0 = vg.Node.create(ctx)
n1 = vg.Node.create(ctx)
mm.addLocalRef(n0)
mm.addLocalRef(n1)

dv0 = ib.DoubleVector()
dv0.push_back(2.3251)
n0.setData(vg.Node.DATA_TYPE_DENSITY, dv0)

dv0.clear()
ib.addValues(dv0, 4, 0.3, 0.7, 0.1, 0.8)
n1.setData(vg.Node.DATA_TYPE_COLOR_RGBA, dv0)

n0.printDebugInfo(True)
n1.printDebugInfo(True)

root0.setChildNodeByOrderIndex(n0, 0)
root0.setChildNodeByOrderIndex(n1, 2)

mm.removeLocalRef(n0)
mm.removeLocalRef(n1)

print("Inserting node...")

p = cg.Vector3.create(0.75, 0.75, 0.75)
mm.addLocalRef(p)

n2 = root0.insertChild(p, maxNumLevels - 1)
mm.addLocalRef(n2)

dv0.clear()
ib.addValues(dv0, 4, 0.1, 0.2, 0.3, 0.4)
n2.setData(vg.Node.DATA_TYPE_COLOR_RGBA, dv0)

n2.printDebugInfo()

mm.removeLocalRef(n2)

print("Voxel tree state:")

root0.printDebugInfo(True)

print("Testing point location:")

locatePoints(points0, root0)

print("Filling tree...")

root0.fill(False, True, 2)

print("Voxel tree state after filling:")

root0.printDebugInfo(True)

mm.removeLocalRef(root0)

print("All done!")

