#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFVG dump mesh.

This script can be used to dump meshes from a part of the FBX hierarchy 
into a single OBJ file.
"""
import IFObjectBase as ib
import CGeoUtils as cg
import GeoUtilsFBX as fbx
import CIFVG as vg
import sys, os
import ifvg_local_config as lc

# memory management
mm = ib.IFObject()

print("IFVG dump mesh.")

dataPath0 = lc.meshPath
dataSetName0 = lc.dataSetName
inFile0 = lc.fbxHierarchyFile

if (len(sys.argv) < 3):
    print("Usage: %s (<node_name> <target_name>)+ [<scale>]" % sys.argv[0])
    sys.exit(0)

print("Nodes:")

numNodes = int((len(sys.argv) - 1) / 2)
nodes = []
for i in range(0, numNodes):
    it0 = sys.argv[2 * i + 1]
    it1 = sys.argv[2 * i + 2]
    print("  [%03d] %s -> %s" % (i, it0, it1))
    nodes += [[ it0, it1 ]]

rescaleMeshes = True
if ((len(sys.argv) - 2 * numNodes - 1) > 0):
    meshScale = float(sys.argv[len(sys.argv) - 1])
else:
    meshScale = lc.meshOutputScale

if (meshScale == 1.):
    rescaleMeshes = False

print("Using mesh scale: %f" % meshScale)

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
            numFaces0 = 0
            numVerts0 = 0
            
            cm0 = vg.Mesh.create()
            mm.addLocalRef(cm0)
            cm0.setID(targetName0)
            cm0.setIDNum(k)
            
            for i in range(0, nm0):
                cn1 = ns0.getNode(i)
                cid0 = cn1.getID();
                
                print("      [%03d] mesh node: {%s}[%s]" % (i, cid0, 
                    cn1.getValueString()))
                
                fn0 = (dataPath0 + '/' + dataSetName0 + '/' + cid0 
                    + ".vgmesh")
                
                print("        Loading mesh from file '%s'..." % fn0)
                
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
                
                numVerts0 += nv0
                numFaces0 += nf0
                
                print("        %d vertices, %d faces" % (nv0, nf0))
                print(("        bounding box: [%s] [center = (%s), " 
                    + "scale = %f, extent = (%s)]") 
                        % (bb0.getValueString(), c0.getValueString(), s0, 
                            e0.getValueString()))
                
                if (rescaleMeshes):
                    print("        Rescaling mesh...")
                    
                    cm1.scale(sv0)
                    cm1.applyTransform(True)
                
                print("        Merging mesh...")
                
                cm0.merge(cm1)
                
                mm.removeLocalRef(cm1)
            
            print("    %d meshes merged (%d vertices, %d faces)" 
                % (nm0, numVerts0, numFaces0))
            
            if (cm0.useTransform() or cm0.useVI()):
                print("    !!! Mesh has pending transformations.")
            
            print("    Calculating mesh bounds...")
            
            cm0.update(False, False)
            
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
            
            fn1 = (dataPath0 + '/' + dataSetName0 + '/' + targetName0 
                + "." + lc.meshOutputFileFormat)
            
            print("    Writing mesh to file: %s" % fn1)
            
            ioCtx.clear()
            ioCtx.openFileForOutput(fn1)
            ioCtx.begin()
            
            if (lc.meshOutputFileFormat == 'obj'):
                cm0.writeOBJ(ioCtx)
            else:
                cm0.serialize(ioCtx)
            
            ioCtx.finish()
            
            mm.removeLocalRef(cm0)
            k += 1
        
    else:
        print("    !!! Node '%s' not found." % nodeName0)

print("All done!")

