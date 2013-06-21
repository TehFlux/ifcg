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
    
    def __init__(self, name = "UnnamedMesh", cgMesh = None, create = False):
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
            self.cgMesh.clear()
        m = self.cgMesh
        bm0 = bmesh.new()
        bm0.from_mesh(bMesh)
        # Vertices.
        for v in bm0.verts:
            m.addVertex(cg.Vertex3.create(v.co[0], v.co[1], v.co[2]))
        # Faces.
        uvTex = None
        if (len(bm0.loops.layers.uv) > 0):
            uvTex = bm0.loops.layers.uv[0]
        i = 0
        for bf in bm0.faces:
            f = cg.Face.create()
            for v in bf.verts:
                f.addVertex(v.index)
            if (not uvTex is None):
                k = 0
                while (k < len(bf.loops)):
                    tc0 = cg.TexCoords()
                    l1 = bf.loops[k]
                    tc0.u = l1[uvTex].uv[0]
                    tc0.v = l1[uvTex].uv[1]
                    f.addTexCoord(tc0)
                    k += 1
            m.addFace(f)
            i += 1
    
    def createBMesh(self, meshName = None, createUVTex = False):
        """Create Blender mesh.
        
        Create a new Blender mesh from the current CGeoUtils mesh. If 
        createUVTex is set to True, an UV texture layer will be created for 
        the mesh. This will only work if the correct number of texture 
        coordinates are specified in the CGeoUtils mesh."""
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
        # UV texture
        if (createUVTex):
            uv1 = bm0.loops.layers.uv.new()
            for i in range(0, numFaces0):
                f0 = m.getFace(i)
                f1 = bm0.faces[i]
                numTexCoords0 = f0.getNumTexCoords()
                numTexCoords1 = len(f1.loops)
                if (numTexCoords0 != numTexCoords1):
                    bm0.free()
                    raise BGeoUtilsError("Invalid number of texture "
                        "coordinates for face #" + str(i) + " (expected "
                        + str(numTexCoords1) + ", " + "got " 
                        + str(numTexCoords0) + ").")
                for k in range(0, numTexCoords0):
                    uv0 = f0.getTexCoord(k)
                    l1 = f1.loops[k]
                    l1[uv0].uv[0] = uv3.u
                    l1[uv0].uv[1] = uv3.v
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
        mesh.."""
        self.createBMesh()
    
    def __str__(self):
        if (not self.cgMesh is None):
            return str(self.cgMesh)
            return "Mesh"

