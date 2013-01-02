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
        # Vertices.
        for v in bMesh.vertices:
            m.addVertex(cg.Vertex3.create(v.co[0], v.co[1], v.co[2]))
        # Faces.
        uvTex = None
        if (len(bMesh.uv_textures) > 0):
            uvTex = bMesh.uv_textures[0]
        i = 0
        for bf in bMesh.faces:
            f = cg.Face.create()
            for v in bf.vertices:
                f.addVertex(v)
            if (not uvTex is None):
                k = 0
                while (k < len(bf.vertices)):
                    tc0 = cg.TexCoords()
                    if (i >= len(uvTex.data)):
                        raise BGeoUtilsError("Not enough texture "
                            + "coordinates in UV texture.")
                    tc0.u = uvTex.data[i].uv[k][0]
                    tc0.v = uvTex.data[i].uv[k][1]
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
        # Vertices.
        numVerts0 = m.getNumVertices()
        numVerts1 = len(m0.vertices)
        if (numVerts1 < numVerts0):
            m0.vertices.add(numVerts0 - numVerts1)
        for i in range(0, numVerts0):
            v0 = m.getVertex(i)
            v1 = m0.vertices[i]
            v1.co[0] = v0.getX()
            v1.co[1] = v0.getY()
            v1.co[2] = v0.getZ()
        # Faces.
        numFaces = m.getNumFaces()
        m0.faces.add(numFaces)
        if (len(m0.faces) < numFaces):
            m0.faces.add(numFaces - len(m0.faces))
        for i in range(0, numFaces):
            f0 = m.getFace(i)
            f1 = m0.faces[i]
            vt0 = []
            nv0 = f0.getNumVertices()
            for k in range(0, nv0):
                vt0 += [f0.getVertex(k)]
            if (nv0 == 4):
                f1.vertices_raw = vt0
            else:
                f1.vertices = vt0
        # UV texture
        if (createUVTex):
            uv0 = m0.uv_textures.new()
            uv1 = uv0.data
            for i in range(0, numFaces):
                f0 = m.getFace(i)
                uv2 = uv1[i].uv
                numTexCoords = f0.getNumTexCoords()
                if (len(uv2) != numTexCoords):
                    raise BGeoUtilsError("Invalid number of texture "
                        "coordinates for face #" + str(i) + " (expected " 
                        + len(uv2) + ", got " + numTexCoords + ").")
                for k in range(0, numTexCoords):
                    uv3 = f0.getTexCoord(k)
                    uv2[k][0] = uv3.u
                    uv2[k][1] = uv3.v
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

