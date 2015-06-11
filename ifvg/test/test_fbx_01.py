#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: FBX scene traversal."""
import IFObjectBase as ib
import GeoUtilsFBX as fbx

testName = "FBX scene traversal"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed/'
inFile0 = dataPath0 + 'unnamed_part.fbx'

m0 = fbx.FBXManager.create()
mm.addLocalRef(m0)
s0 = fbx.FBXScene.create()
mm.addLocalRef(s0)
s0.setFbxManager(m0)

print("  Loading data from file '%s'..." % inFile0)

s0.loadFromFile(inFile0)

print("  Nodes:")

s0.listNodes(True, 2)

print("All done!")

