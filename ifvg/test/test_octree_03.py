#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Octree #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import CIFVG as vg

testName = "Octree #3"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

maxNumLevels = 3
order = 2
scale = 1.

print("Creating context...")

ctx = vg.Context.create(maxNumLevels, order, scale)
mm.addLocalRef(ctx)

ctx.printDebugInfo()

print("Creating root node #1...")

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)

root0.printDebugInfo(True)

print("  Adding nodes...")

n00 = vg.Node.create(ctx)
n01 = vg.Node.create(ctx)
mm.addLocalRef(n00)
mm.addLocalRef(n01)

dv0 = ib.DoubleVector()
dv0.push_back(2.3251)
n00.setData(vg.Node.DATA_TYPE_DENSITY, dv0)

dv0.clear()
ib.addValues(dv0, 4, 0.3, 0.7, 0.1, 0.8)
n01.setData(vg.Node.DATA_TYPE_COLOR_RGBA, dv0)

n00.printDebugInfo(True)
n01.printDebugInfo(True)

root0.setChildNodeByOrderIndex(n00, 0)
root0.setChildNodeByOrderIndex(n01, 2)

mm.removeLocalRef(n00)
mm.removeLocalRef(n01)

print("  Inserting node...")

p0 = cg.Vector3.create(0.75, 0.75, 0.75)
mm.addLocalRef(p0)

n02 = root0.insertChild(p0, maxNumLevels - 1)
mm.addLocalRef(n02)

dv0.clear()
ib.addValues(dv0, 4, 0.1, 0.2, 0.3, 0.4)
n02.setData(vg.Node.DATA_TYPE_COLOR_RGBA, dv0)

n02.printDebugInfo()

mm.removeLocalRef(n02)

print("  Voxel tree state:")

root0.printDebugInfo(True)

print("Creating root node #2...")

root1 = vg.Node.create(ctx)
mm.addLocalRef(root1)

root1.printDebugInfo(True)

print("  Adding nodes...")

n10 = vg.Node.create(ctx)
n11 = vg.Node.create(ctx)
mm.addLocalRef(n10)
mm.addLocalRef(n11)

n10.setData(vg.Node.DATA_TYPE_VOXEL_CLASS, None)
n10.setVoxelClass(vg.VOXEL_CLASS_FILLED)

n11.setData(vg.Node.DATA_TYPE_VOXEL_CLASS, None)
n11.setVoxelClass(vg.VOXEL_CLASS_INSIDE)

n10.printDebugInfo(True)
n11.printDebugInfo(True)

root1.setChildNodeByOrderIndex(n10, 1)
root1.setChildNodeByOrderIndex(n11, 5)

mm.removeLocalRef(n10)
mm.removeLocalRef(n11)

print("  Inserting node...")

p1 = cg.Vector3.create(0.55, 0.55, 0.65)
mm.addLocalRef(p1)

n12 = root1.insertChild(p1, maxNumLevels - 1)
mm.addLocalRef(n12)

n12.setData(vg.Node.DATA_TYPE_VOXEL_CLASS, None)
n12.setVoxelClass(vg.VOXEL_CLASS_OUTSIDE)

n12.printDebugInfo()

mm.removeLocalRef(n12)

print("  Voxel tree state:")

root1.printDebugInfo(True)

print("Merging nodes...")

root0.merge(root1)

print("  Voxel tree state (after merging) #1:")

root1.printDebugInfo(True)

print("  Voxel tree state (after merging) #0:")

root0.printDebugInfo(True)

mm.removeLocalRef(root0)
mm.removeLocalRef(root1)

print("All done!")

