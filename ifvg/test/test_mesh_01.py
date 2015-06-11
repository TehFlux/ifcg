#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Octree #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import CIFVG as vg

testName = "Mesh #1"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

outFile0 = 'temp/test_mesh_01.mesh'

print("Creating mesh...")

cube0 = cg.Mesh.cube()
mm.addLocalRef(cube0)
cube0.makeTris()
cube0.update()

mesh0 = vg.Mesh.create()
mm.addLocalRef(mesh0)
mesh0.setID('Mesh01')
mesh0.setIDNum(1)
mesh0.merge(cube0)
mesh0.update()

print("  " + mesh0.getString())

print("Creating I/O context...")

ioCtx = ib.IFIOContext.create()
mm.addLocalRef(ioCtx)

ioCtx.setStringBufferOutput()

print("Serializing mesh...")

clock0 = cg.Clock()

clock0.start()
ioCtx.begin()
mesh0.serialize(ioCtx)
ioCtx.finish()
clock0.stop()

dataSize0 = ioCtx.getOutputStreamSize()

print("  I/O context state:")
ioCtx.printDebugInfo(True, True, True, True)

print("  %d bytes written in %f secs" % (dataSize0, 
    clock0.getElapsedTime()))

print("Serializing mesh to file '%s'..." % outFile0)

ioCtx.clear()
ioCtx.openFileForOutput(outFile0)

clock0.start()
ioCtx.begin()
mesh0.serialize(ioCtx)
ioCtx.finish()
clock0.stop()

dataSize0 = ioCtx.getOutputStreamSize()

print("  %d bytes written in %f secs" % (dataSize0, 
    clock0.getElapsedTime()))

print("Deserializing mesh from file '%s'..." % outFile0)

ioCtx.clear()
ioCtx.openFileForInput(outFile0)

mesh1 = vg.Mesh.create()
mm.addLocalRef(mesh1)

clock0.start()
ioCtx.begin()
mesh1.deserialize(ioCtx)
ioCtx.finish()
clock0.stop()

print("  I/O context state:")
ioCtx.printDebugInfo(True, True, True, True)

print("  " + mesh1.getString())

mm.removeLocalRef(mesh0)
mm.removeLocalRef(mesh1)

print("All done!")

