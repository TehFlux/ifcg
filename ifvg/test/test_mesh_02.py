#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Octree #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx
import CIFVG as vg

testName = "Mesh #2"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed'
dataPath1 = '/home/flux4/recent/p/data'
dataPath2 = dataPath1 + '/meshes'

nodeName0 = 'n_00000135'

#inFile0 = dataPath2 + '/unnamed-part/' + nodeName0 + '.vgmesh'
inFile0 = dataPath2 + '/unnamed/' + nodeName0 + '.vgmesh'

#inFile1 = dataPath1 + '/other/unnamed-part-01.xml'
inFile1 = dataPath1 + '/other/unnamed-01.xml'

outFile0 = dataPath2 + '/unnamed/' + nodeName0 + '.obj'

meshScale = 0.001

print("Loading FBX hierarchy data from file '%s'..." % inFile1)

root0 = fbx.FBXNode.create()
mm.addLocalRef(root0)

root0.loadFromXMLFile(inFile1)

print("Looking for node '%s'..." % nodeName0)

n0 = root0.findNodeByID(nodeName0)
if (not n0 is None):
    print("    {%s}[%s]" % (n0.getID(), n0.getValueString()))

print("Loading mesh from file '%s'..." % inFile0)

ioCtx = ib.IFIOContext.create()
mm.addLocalRef(ioCtx)

ioCtx.clear()
ioCtx.openFileForInput(inFile0)

mesh0 = vg.Mesh.create()
mm.addLocalRef(mesh0)

ioCtx.begin()
mesh0.deserialize(ioCtx)
ioCtx.finish()

nv0 = mesh0.getNumVertices()
nf0 = mesh0.getNumFaces()
bb0 = mesh0.getBounds()
ao0 = bb0.getAxisOrder()
s0 = bb0.getExtent(ao0.a0)
e0 = bb0.getExtent()
c0 = bb0.getCenter()

print("  %d vertices, %d faces" % (nv0, nf0))
print("  bounding box: [%s] [center = (%s), scale = %f, extent = (%s)]" 
    % (bb0.getValueString(), c0.getValueString(), s0, e0.getValueString()))

print("Rescaling mesh...")

sv0 = cg.Vector3(meshScale, meshScale, meshScale)
mesh0.scale(sv0)
mesh0.applyTransform(True)

print("Writing mesh to file '%s'..." % outFile0)

ioCtx.clear()
ioCtx.openFileForOutput(outFile0)

ioCtx.begin()
mesh0.writeOBJ(ioCtx)
ioCtx.finish()

mm.removeLocalRef(mesh0)

print("All done!")

