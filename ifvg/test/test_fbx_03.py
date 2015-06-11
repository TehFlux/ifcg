#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: FBX scene traversal."""
import sys
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx

testName = "FBX mesh dump"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed'
dataPath1 = '/home/flux4/recent/p/data'
dataPath2 = dataPath0 + '/parts'
inFile0 = dataPath0 + '/unnamed.fbx'

nodes = [
## specify node to be extracted here.
## node_identifier is used as the output directory
#    [ 'NODE_NAME', 'node_identifier' ]
]

scale0 = 0.005
applyNodeTransform = True

m0 = fbx.FBXManager.create()
mm.addLocalRef(m0)
s0 = fbx.FBXScene.create()
mm.addLocalRef(s0)
s0.setFbxManager(m0)

clock0 = cg.Clock()

print("  Loading data from file '%s'..." % inFile0)

clock0.start()
s0.loadFromFile(inFile0)
clock0.stop()

t0 = clock0.getElapsedTime()

print("    Loaded data in %f secs." % t0)

print("  Dumping nodes...")

clock0.start()
numMeshes = 0

for it in nodes:
    nodeName0 = it[0]
    outDir0 = it[1]
    outFilePath0 = dataPath2 + '/' + outDir0
    
    print("  Looking for node '%s'..." % nodeName0)
    
    n0 = s0.findChildNodeByName(nodeName0)
    mm.addLocalRef(n0)
    
    if (n0 is None):
        print("    !!! Node not found.")
        sys.exit(-1)
    
    print("    found node: [%s]" % n0.getValueString())
    
    print("    Dumping meshes to '%s'..." % dataPath2)
    
    numMeshes += n0.dumpMesh(outFilePath0, True, None, 0, 
        scale0, applyNodeTransform)
    mm.removeLocalRef(n0)

clock0.stop()

t0 = clock0.getElapsedTime()

print("    Dumped %d meshes in %f secs." % (numMeshes, t0))

print("All done!")

