#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG node hierarchy info."""
import IFObjectBase as ib
import CGeoUtils as cg
import CIFVG as vg
import ifvg_local_config as lc
import sys

# memory management
mm = ib.IFObject()

print("IFVG node hierarchy info.")

if (len(sys.argv) < 2):
    print("Usage: %s <vgnodeh_file>" % sys.argv[0])
    sys.exit(0)

inFile0 = sys.argv[1]

print("Creating context...")

octreeMaxNumLevels = lc.octreeMaxNumLevels
octreeOrder = lc.octreeOrder
octreeScale = lc.octreeScale

ctx = vg.Context.create(octreeMaxNumLevels, octreeOrder, octreeScale)
mm.addLocalRef(ctx)

print("Loading node hierarchy from file '%s'..." % inFile0)

ioCtx = vg.IOContext.create()
mm.addLocalRef(ioCtx)

ioCtx.openFileForInput(inFile0)

root0 = vg.Node.create(ctx)
mm.addLocalRef(root0)

clock0 = cg.Clock()

clock0.start()
ioCtx.begin()
root0.deserializeHierarchy(ioCtx)
ioCtx.finish()
clock0.stop()

t0 = clock0.getElapsedTime()

print("  loaded in %f secs" % t0)

maxDepth0 = root0.getMaxDepth()
memSize0 = root0.getMemSize(True)

print("  max. depth     = %d" % maxDepth0)
print("  allocated size = %d bytes" % memSize0)

print("  Data nodes per level:")

nf0 = vg.NodeFilter.create()
mm.addLocalRef(nf0)
nf0.setContext(ctx)
nf0.setDataType(vg.Node.DATA_TYPE_ANY_NOT_NULL)

ns0 = vg.NodeSet()
for i in range(0, octreeMaxNumLevels):
    nf0.setDepthRange(i, i)
    ns0.clearNodes()
    cn0 = root0.find(ns0, nf0, True)
    print("    level %d: %d data nodes" % (i, cn0))
    #for k in range(0, ns0.getNumNodes()):
    #    if ((k % 1000) == 0):
    #        cn = ns0.getNode(k)
    #        print("      [%03d] %s" % (k, cn.getValueString()))
ns0.clearNodes()

mm.removeLocalRef(root0)

print("All done!")

