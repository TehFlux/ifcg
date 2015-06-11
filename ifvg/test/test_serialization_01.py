#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Octree #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import CIFVG as vg

testName = "Serialization #1"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

outFile0 = 'temp/test_serialization_01.octree'

maxNumLevels = 3
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

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)

root0.printDebugInfo(True)

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

#print("Filling tree...")
#
#root0.fill(False, True, 2)
#
#print("Voxel tree state after filling:")
#
#root0.printDebugInfo(True)

print("Creating I/O context...")

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

ioCtx.setStringBufferOutput()

print("Serializing node hierarchy...")

clock0 = cg.Clock()

clock0.start()
ioCtx.begin()
root0.serializeHierarchy(ioCtx)
ioCtx.finish()
clock0.stop()

dataSize0 = ioCtx.getOutputStreamSize()

print("  I/O context state:")
ioCtx.printDebugInfo(True, True, True, True)

print("  %d bytes written in %f secs" % (dataSize0, 
    clock0.getElapsedTime()))

print("Serializing node hierarchy to file '%s'..." % outFile0)

ioCtx.clear()
ioCtx.openFileForOutput(outFile0)

clock0.start()
ioCtx.begin()
root0.serializeHierarchy(ioCtx)
ioCtx.finish()
clock0.stop()

dataSize0 = ioCtx.getOutputStreamSize()

print("  %d bytes written in %f secs" % (dataSize0, 
    clock0.getElapsedTime()))

print("Deserializing node hierarchy from file '%s'..." % outFile0)

ioCtx.clear()
ioCtx.openFileForInput(outFile0)

root1 = vg.Node.create(ctx)
mm.addLocalRef(root1)

clock0.start()
ioCtx.begin()
root1.deserializeHierarchy(ioCtx)
ioCtx.finish()
clock0.stop()

print("  I/O context state:")
ioCtx.printDebugInfo(True, True, True, True)

print("Voxel tree state (deserialized):")

root1.printDebugInfo(True)

mm.removeLocalRef(root0)
mm.removeLocalRef(root1)

print("All done!")

