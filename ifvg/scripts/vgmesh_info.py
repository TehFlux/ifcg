#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG VGMesh info.

This script is used to obtain information on a vgmesh file."""
import sys, os
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx
import CIFVG as vg
import ifvg_local_config as lc

# memory management
mm = ib.IFObject()

print("IFVG VGMesh info.")

if (len(sys.argv) < 2):
    print("Usage: %s <mesh_file>" % sys.argv[0])
    sys.exit(0)

inFile0 = sys.argv[1]

print("Loading mesh from file '%s'..." % inFile0)

ioCtx = ib.IFIOContext.create()
mm.addLocalRef(ioCtx)

ioCtx.clear()
ioCtx.openFileForInput(inFile0)

mesh0 = vg.Mesh.create()
mm.addLocalRef(mesh0)

clock0 = cg.Clock()

clock0.start()
ioCtx.begin()
mesh0.deserialize(ioCtx)
ioCtx.finish()
clock0.stop()

t0 = clock0.getElapsedTime()

print("  loaded in %f secs" % t0)

nv0 = mesh0.getNumVertices()
nf0 = mesh0.getNumFaces()
bb0 = mesh0.getBounds()
ao0 = bb0.getAxisOrder()
s0 = bb0.getExtent(ao0.a0)
e0 = bb0.getExtent()
c0 = bb0.getCenter()
r0 = bb0.getRadius()

print("  mesh '%s' (%d)" % (mesh0.getID(), mesh0.getIDNum()))
print("  %d vertices, %d faces" % (nv0, nf0))
print("  bounding box: [%s]" % bb0.getValueString())
print("    center = (%s)" % c0.getValueString())
print("    radius = (%s)" % r0.getValueString())
print("    extent = (%s)" % e0.getValueString())
print("    scale = %f" % s0)

mm.removeLocalRef(mesh0)

print("All done!")

