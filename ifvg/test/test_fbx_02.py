#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: FBX scene traversal."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx

testName = "FBX mesh extraction"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed'
dataPath1 = '/home/flux4/recent/p/data'
inFile0 = dataPath0 + '/unnamed_part.fbx'
#inFile0 = dataPath0 + '/unnamed.fbx'

nodeName0 = 'NODE_NAME'
meshScale0 = 5.
outFile0 = dataPath1 + '/meshes/unnamed-part-01.xml'

m0 = fbx.FBXManager.create()
mm.addLocalRef(m0)
s0 = fbx.FBXScene.create()
mm.addLocalRef(s0)
s0.setFbxManager(m0)

print("  Loading data from file '%s'..." % inFile0)

s0.loadFromFile(inFile0)

print("  Looking for node '%s'..." % nodeName0)

n0 = s0.findChildNodeByName(nodeName0)

if (n0 is None):
    print("    !!! Node not found.")
    sys.exit(-1)

print("    found node: [%s]" % n0.getValueString())

print("  Extracting meshes...")

mesh0 = cg.Mesh.create()
mm.addLocalRef(m0)

n0.getMesh(mesh0, True)
mesh0.update()

numVerts0 = mesh0.getNumVertices()
numFaces0 = mesh0.getNumFaces()

print("    Extracted mesh (%d verts, %d faces)." 
    % (numVerts0, numFaces0))

bb0 = mesh0.getBounds()
ao0 = bb0.getAxisOrder()
s0 = bb0.getExtent(ao0.a0)
e0 = bb0.getExtent()
c0 = bb0.getCenter()

print("    Bounding box: [%s] [center = (%s), scale = %f, extent = (%s)]" 
    % (bb0.getValueString(), c0.getValueString(), s0, 
        e0.getValueString()))

print("  Normalizing mesh...")

mesh0.translate(c0.flip())

s1 = meshScale0 / s0
sv0 = cg.Vector3(s1, s1, s1)
mesh0.scale(sv0)

mesh0.applyTransform()

print("  Writing mesh to file '%s'..." % outFile0)

mesh0.writeToXMLFile(outFile0)

print("All done!")

