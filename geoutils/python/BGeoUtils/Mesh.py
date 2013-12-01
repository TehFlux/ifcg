# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010-2012 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# Mesh.py          Blender mesh tools.
# ==========================================================================
# 
# This file is part of GeoUtils - Ionflux' Geometry Library.
# 
# GeoUtils - Ionflux' Geometry Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later version.
# 
# GeoUtils - Ionflux' Geometry Library is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GeoUtils - Ionflux' Geometry Library; if not, write to the 
# Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
# 02111-1307 USA
# 
# ==========================================================================
import IFObjectBase as ib
import CGeoUtils as cg
from BGeoUtils import BGeoUtilsError
import bpy
import bmesh

class Mesh:
    """Mesh.
    
    A wrapper around a CGeoUtils.Mesh for use with Blender."""
    
    def __init__(self, name = "UnnamedMesh", cgMesh = None, 
        create = False):
        self.name = name
        # for memory management
        self.mm = ib.IFObject()
        if (not cgMesh is None):
            self.mm.addLocalRef(cgMesh)
        self.cgMesh = cgMesh
        if (create):
            self.createBMesh()
    
    def setFromBMesh(self, bMesh):
        """Initialize from Blender mesh."""
        if (self.cgMesh is None):
            self.cgMesh = cg.Mesh.create()
            self.mm.addLocalRef(self.cgMesh)
        else:
            self.cgMesh.clearData()
        m = self.cgMesh
        m.setID(self.name)
        bm0 = bmesh.new()
        bm0.from_mesh(bMesh)
        # Vertices.
        for v in bm0.verts:
            m.addVertex(cg.Vertex3.create(v.co[0], v.co[1], v.co[2]))
        # Faces.
        uvTex = None
        vCol = None
        if (len(bm0.loops.layers.uv) > 0):
            uvTex = bm0.loops.layers.uv[0]
        if (len(bm0.loops.layers.color) > 0):
            vCol = bm0.loops.layers.color[0]
        for bf in bm0.faces:
            f = m.addFace()
            for v in bf.verts:
                f.addVertex(v.index)
            # Face data.
            tc0 = None
            vc0 = None
            if (not uvTex is None):
                tc0 = f.addFaceData(cg.FaceData.TYPE_TEX_COORD)
            if (not vCol is None):
                vc0 = f.addFaceData(cg.FaceData.TYPE_VERTEX_COLOR)
            if ((not uvTex is None) 
                or (not vCol is None)):
                k = 0
                numLoops = len(bf.loops)
                while (k < numLoops):
                    l0 = bf.loops[((numLoops - 1) + k) % numLoops]
                    if (not tc0 is None):
                        # Get texture coordinates.
                        uv0 = l0[uvTex].uv
                        tc0.addVector(cg.Vector2.create(
                            uv0[0], uv0[1]))
                    if (not vc0 is None):
                        # Get vertex colors.
                        c0 = l0[vCol]
                        vc0.addVector(cg.Vector3.create(
                            c0[0], c0[1], c0[2]))
                    k += 1
        bm0.free()
    
    def createBMesh(self, meshName = None, createUVTex = False, 
        createVertexColors = False):
        """Create Blender mesh.
        
        Create a new Blender mesh from the current CGeoUtils mesh."""
        if (self.cgMesh is None):
            raise BGeoUtilsError("CGeoUtils mesh not set.")
        m = self.cgMesh
        m0 = self.getBMesh(meshName)
        bm0 = bmesh.new()
        # Vertices.
        numVerts0 = m.getNumVertices()
        for i in range(0, numVerts0):
            v0 = m.getVertex(i)
            bm0.verts.new((v0.getX(), v0.getY(), v0.getZ()))
        bm0.verts.index_update()
        # Faces.
        numFaces0 = m.getNumFaces()
        for i in range(0, numFaces0):
            f0 = m.getFace(i)
            vt0 = []
            vt1 = []
            nv0 = f0.getNumVertices()
            for k in range(0, nv0):
                vk = f0.getVertex(k)
                vt1 += [ bm0.verts[vk] ]
            bm0.faces.new(vt1)
        bm0.faces.index_update()
        # Face data
        uvTex = None
        fTex = None
        vCol = None
        if (createUVTex):
            uvTex = bm0.loops.layers.uv.new()
            fTex = bm0.faces.layers.tex.new()
        if (createVertexColors):
            vCol = bm0.loops.layers.color.new()
        if (createUVTex 
            or createVertexColors):
            for i in range(0, numFaces0):
                f0 = m.getFace(i)
                f1 = bm0.faces[i]
                numLoops = len(f1.loops)
                tc0 = None
                if (createUVTex):
                    tc0 = f0.getTexCoords0()
                    numTexCoords0 = tc0.getNumVectors()
                    if (numTexCoords0 != numLoops):
                        bm0.free()
                        raise BGeoUtilsError("Invalid number of texture "
                            "coordinates for face #" + str(i) + " (expected "
                            + str(numLoops) + ", " + "got " 
                            + str(numTexCoords0) + ").")
                vc0 = None
                if (createVertexColors):
                    vc0 = f0.getVertexColors0()
                    numVertexColors0 = vc0.getNumVectors()
                    if (numVertexColors0 != numLoops):
                        bm0.free()
                        raise BGeoUtilsError("Invalid number of vertex "
                            "colors for face #" + str(i) + " (expected "
                            + str(numLoops) + ", " + "got " 
                            + str(numVertexColors0) + ").")
                for k in range(0, numLoops):
                    l0 = f1.loops[k]
                    if (not tc0 is None):
                        uv0 = tc0.getVector((k + 1) % numLoops)
                        l0[uvTex].uv[0] = uv0.getElement(0)
                        l0[uvTex].uv[1] = uv0.getElement(1)
                    if (not vc0 is None):
                        c0 = vc0.getVector((k + 1) % numLoops)
                        l0[vCol][0] = c0.getElement(0)
                        l0[vCol][1] = c0.getElement(1)
                        l0[vCol][2] = c0.getElement(2)
        bm0.to_mesh(m0)
        bm0.free()
        return m0
    
    def getBMesh(self, meshName = None):
        """Get Blender mesh."""
        if (self.cgMesh is None):
            raise BGeoUtilsError("CGeoUtils mesh not set.")
        m = self.cgMesh
        if (meshName is None):
            meshName = self.name
        if (meshName is None):
            meshName = m.getID()
        if (len(meshName) == 0):
            meshName = "unnamedMesh"
        m0 = bpy.data.meshes.get(meshName)
        if (m0 is None):
            m0 = bpy.data.meshes.new(meshName)
        if (m0 is None):
            raise BGeoUtilsError("Could not create Blender mesh.")
        return m0
    
    def update(self):
        """Update the Blender mesh.
        
        Update the Blender mesh to reflect changes in the GeoUtils 
        mesh."""
        self.createBMesh()
    
    def __str__(self):
        if (not self.cgMesh is None):
            return str(self.cgMesh)
        return "Mesh"

class Polygon3:
    """Polygon (3D).
    
    A wrapper around a CGeoUtils.Polygon3 for use with Blender."""
    
    def __init__(self, name = "UnnamedPolygon3", cgPoly = None, 
        create = False):
        self.name = name
        # for memory management
        self.mm = ib.IFObject()
        if (not cgPoly is None):
            self.mm.addLocalRef(cgPoly)
        self.cgPoly = cgPoly
        if (create):
            self.createBMesh()
    
    def setFromBMesh(self, bMesh):
        """Initialize from Blender mesh."""
        if (self.cgPoly is None):
            self.cgPoly = cg.Polygon3.create()
            self.mm.addLocalRef(self.cgPoly)
        else:
            self.cgPoly.clearData()
        p = self.cgPoly
        p.setID(self.name)
        bm0 = bmesh.new()
        bm0.from_mesh(bMesh)
        # Vertices.
        for v in bm0.verts:
            p.addVertex(cg.Vertex3.create(v.co[0], v.co[1], v.co[2]))
        # Edges.
        for be in bm0.edges:
            p.addEdge(be.verts[0].index, be.verts[1].index)
        bm0.free()
    
    def createBMesh(self, meshName = None):
        """Create Blender mesh.
        
        Create a new Blender mesh from the current CGeoUtils polygon."""
        if (self.cgPoly is None):
            raise BGeoUtilsError("CGeoUtils mesh not set.")
        p = self.cgPoly
        m0 = self.getBMesh(meshName)
        bm0 = bmesh.new()
        # Vertices.
        numVerts0 = p.getNumVertices()
        for i in range(0, numVerts0):
            v0 = p.getVertex(i)
            bm0.verts.new((v0.getX(), v0.getY(), v0.getZ()))
        bm0.verts.index_update()
        # Edges.
        numEdges0 = p.getNumEdges()
        for i in range(0, numEdges0):
            e0 = p.getEdge(i)
            vt0 = ( 
                bm0.verts[e0.getVertex(0)], 
                bm0.verts[e0.getVertex(1)] 
            )
            bm0.edges.new(vt0)
        bm0.edges.index_update()
        bm0.to_mesh(m0)
        bm0.free()
        return m0

    def getBMesh(self, meshName = None):
        """Get Blender mesh."""
        if (self.cgPoly is None):
            raise BGeoUtilsError("CGeoUtils polygon not set.")
        m = self.cgPoly
        if (meshName is None):
            meshName = self.name
        if (meshName is None):
            meshName = m.getID()
        if (len(meshName) == 0):
            meshName = "unnamedMesh"
        m0 = bpy.data.meshes.get(meshName)
        if (m0 is None):
            m0 = bpy.data.meshes.new(meshName)
        if (m0 is None):
            raise BGeoUtilsError("Could not create Blender mesh.")
        return m0
    
    def update(self):
        """Update the Blender mesh.
        
        Update the Blender mesh to reflect changes in the GeoUtils 
        mesh."""
        self.createBMesh()
    
    def __str__(self):
        if (not self.cgMesh is None):
            return str(self.cgMesh)
        return "Polygon3"

