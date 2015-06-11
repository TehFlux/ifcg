#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG test: Octree #1."""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx
import CIFVG as vg

testName = "Mesh export"

# memory management
mm = ib.IFObject()

print("IFVG test: %s" % testName)

dataPath0 = '/home/flux4/recent/p/misc/unnamed'
dataPath1 = '/home/flux4/recent/p/data'
dataPath2 = dataPath1 + '/meshes'
dataPath3 = dataPath0 + '/parts'

dataSetName0 = 'unnamed'

inFile0 = dataPath1 + '/other/unnamed-01.xml'

nodes = [
    # list of nodes
    # target_name specifies the target file name
    [ 'NODE_NAME', 'target_name' ]
]

meshScale = 0.002

sv0 = cg.Vector3(meshScale, meshScale, meshScale)

print("Loading FBX hierarchy data from file '%s'..." % inFile0)

root0 = fbx.FBXNode.create()
mm.addLocalRef(root0)

root0.loadFromXMLFile(inFile0)

print("Processing nodes...")

ioCtx = ib.IFIOContext.create()
mm.addLocalRef(ioCtx)

ns0 = fbx.FBXNodeSet.create()
mm.addLocalRef(ns0)

k = 0
for it in nodes:
    nodeName0 = it[0]
    targetName0 = it[1]
    
    print("  Looking for node '%s'..." % nodeName0)
    
    cn0 = root0.findNodeByName(nodeName0)
    if (not cn0 is None):
        print("    {%s}[%s]" % (cn0.getID(), cn0.getValueString()))
        
        print("    Looking for mesh nodes...")
        
        ns0.clearNodes()
        cn0.findNodesByAttributeType(fbx.FBXNode.TYPE_MESH, ns0)
        nm0 = ns0.getNumNodes()
        
        print("    %d mesh nodes found" % nm0)
        print("    Merging meshes...")
        
        if (nm0 > 0):
            print("      Creating mesh '%s'..." % targetName0)
            
            cm0 = vg.Mesh.create()
            mm.addLocalRef(cm0)
            cm0.setID(targetName0)
            cm0.setIDNum(k)
            
            for i in range(0, nm0):
                cn1 = ns0.getNode(i)
                cid0 = cn1.getID();
                
                print("      mesh node: {%s}[%s]" % (cid0, 
                    cn1.getValueString()))
                
                fn0 = (dataPath2 + '/' + dataSetName0 + '/' + cid0 
                    + ".vgmesh")
                
                print("      Loading mesh from file '%s'..." % fn0)
                
                cm1 = vg.Mesh.create()
                mm.addLocalRef(cm1)
                
                ioCtx.clear()
                ioCtx.openFileForInput(fn0)
                ioCtx.begin()
                cm1.deserialize(ioCtx)
                ioCtx.finish()
                
                nv0 = cm1.getNumVertices()
                nf0 = cm1.getNumFaces()
                bb0 = cm1.getBounds()
                ao0 = bb0.getAxisOrder()
                s0 = bb0.getExtent(ao0.a0)
                e0 = bb0.getExtent()
                c0 = bb0.getCenter()
                
                print("      %d vertices, %d faces" % (nv0, nf0))
                print(("      bounding box: [%s] [center = (%s), " 
                    + "scale = %f, extent = (%s)]") 
                        % (bb0.getValueString(), c0.getValueString(), s0, 
                            e0.getValueString()))
                
                print("      Rescaling mesh...")
                
                cm1.scale(sv0)
                cm1.applyTransform(True)
                
                print("      Merging mesh...")
                
                cm0.merge(cm1)
                
                mm.removeLocalRef(cm1)
            
            print("    %d meshes merged" % nm0)
            
            cm0.update()
            
            nv0 = cm0.getNumVertices()
            nf0 = cm0.getNumFaces()
            bb0 = cm0.getBounds()
            ao0 = bb0.getAxisOrder()
            s0 = bb0.getExtent(ao0.a0)
            e0 = bb0.getExtent()
            c0 = bb0.getCenter()
            
            print("    %d vertices, %d faces" % (nv0, nf0))
            print(("    bounding box: [%s] [center = (%s), scale = %f, "
                + "extent = (%s)]") 
                    % (bb0.getValueString(), c0.getValueString(), s0, 
                        e0.getValueString()))
            
            fn1 = (dataPath2 + '/' + dataSetName0 + '/' + targetName0 
                + ".obj")
            
            print("    Writing mesh to file: %s" % fn1)
            
            ioCtx.clear()
            ioCtx.openFileForOutput(fn1)
            ioCtx.begin()
            cm0.writeOBJ(ioCtx)
            ioCtx.finish()
            
            mm.removeLocalRef(cm0)
            k += 1
        
    else:
        print("    !!! Node '%s' not found." % nodeName0)

print("All done!")

