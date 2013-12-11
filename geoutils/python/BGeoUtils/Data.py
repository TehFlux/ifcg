# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010-2013 Jörn P. Meier
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
import IFMapping as im
import CGeoUtils as cg
from BGeoUtils import BGeoUtilsError
import bpy
import bmesh

class DataNode:
    """Data node.
    
    Wrapper around a Blender data node.
    
    name    -- Name
    cgData  -- CGeoUtils data object
    """
    
    def __init__(self, name = "UnnamedData", cgData = None, 
        create = False):
        self.name = name
        # for memory management
        self.mm = ib.IFObject()
        if (not cgData is None):
            self.mm.addLocalRef(cgData)
        self.cgData = cgData
        if (create):
            self.createBData()
    
    def createBData(self, dataName = None):
        pass
    
    def getBData(self, dataName = None):
        pass
    
    def update(self):
        """Update the Blender data.
        
        Update the Blender data to reflect changes in the GeoUtils 
        data."""
        self.createBData()
    
    def __str__(self):
        if (not self.cgData is None):
            return "DataNode[" + str(self.cgData) + "]"
        return "DataNode"

class Mesh(DataNode):
    """Mesh.
    
    Wrapper around a CGeoUtils.Mesh for use with Blender."""
    
    def __init__(self, name = "UnnamedMesh", cgMesh = None, 
        create = False):
        DataNode.__init__(self, name, cgMesh, create)
    
    def setFromBMesh(self, bMesh):
        """Initialize from Blender mesh."""
        if (self.cgData is None):
            self.cgData = cg.Mesh.create()
            self.mm.addLocalRef(self.cgData)
        else:
            self.cgData.clearData()
        m = self.cgData
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
        if (self.cgData is None):
            raise BGeoUtilsError("CGeoUtils mesh not set.")
        m = self.cgData
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
    
    def createBData():
        self.createBMesh()
    
    def getBMesh(self, meshName = None):
        """Get Blender mesh."""
        if (self.cgData is None):
            raise BGeoUtilsError("CGeoUtils data object not set.")
        m = self.cgData
        if (meshName is None):
            meshName = self.name
        if (meshName is None):
            meshName = m.getID()
        if (len(meshName) == 0):
            meshName = "UnnamedMesh"
        m0 = bpy.data.meshes.get(meshName)
        if (m0 is None):
            m0 = bpy.data.meshes.new(meshName)
        if (m0 is None):
            raise BGeoUtilsError("Could not create Blender mesh.")
        return m0
    
    def getBData(self, dataName = None):
        return self.getBMesh(dataName)
    
    def __str__(self):
        if (not self.cgData is None):
            return "Mesh[" + str(self.cgData) + "]"
        return "Mesh"

class Polygon3(Mesh):
    """Polygon (3D).
    
    A wrapper around a CGeoUtils.Polygon3 for use with Blender."""
    
    def __init__(self, name = "UnnamedPolygon3", cgPoly = None, 
        create = False):
        Mesh.__init__(self, name, cgPoly, create)
    
    def setFromBMesh(self, bMesh):
        """Initialize from Blender mesh."""
        if (self.cgData is None):
            self.cgData = cg.Polygon3.create()
            self.mm.addLocalRef(self.cgData)
        else:
            self.cgData.clearData()
        p = self.cgData
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
        if (self.cgData is None):
            raise BGeoUtilsError("CGeoUtils mesh not set.")
        p = self.cgData
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
    
    def __str__(self):
        if (not self.cgData is None):
            return "Polygon3[" + str(self.cgData) + "]"
        return "Polygon3"

class BezierSpline(DataNode):
    """Bezier spline.
    
    Wrapper around an IFMapping.BezierSpline for use with Blender.
    """
    
    def __init__(self, name = "UnnamedCurve", cgCurve = None, 
        create = False):
        DataNode.__init__(self, name, cgCurve, create)
    
    def createBCurve(self, dataName):
        """Create Blender curve.
        
        Create a new Blender curve from the current IFMapping curve."""
        if (self.cgData is None):
            raise BGeoUtilsError("IFMapping curve not set.")
        c0 = self.cgData
        c1 = self.getBCurve(dataName)
        if (len(c1.splines) == 0):
            s0 = c1.splines.new(type = 'BEZIER')
        else:
            s0 = c1.splines[0]
        numCurves0 = c0.getNumSegments()
        numPoints0 = numCurves0 + 1
        numPoints1 = len(s0.bezier_points)
        if (numPoints1 < numPoints0):
            s0.bezier_points.add(numPoints0 - numPoints1)
        for i in range(0, numCurves0):
            cs0 = c0.getSegment(i)
            ps0 = cs0.getPoint(0)
            ps1 = cs0.getPoint(1)
            ps2 = cs0.getPoint(2)
            ps3 = cs0.getPoint(3)
            pt0 = s0.bezier_points[i]
            pt1 = s0.bezier_points[i + 1]
            if (i == 0):
                pt0.handle_left_type = 'AUTO'
            pt0.handle_right_type = 'FREE'
            pt0.co = [ ps0.getX(), ps0.getY(), ps0.getZ() ]
            pt0.handle_right = [ ps1.getX(), ps1.getY(), ps1.getZ() ]
            pt1.handle_left_type = 'FREE'
            pt1.handle_left = [ ps2.getX(), ps2.getY(), ps2.getZ() ]
            if (i == numCurves0 - 1):
                pt1.handle_right_type = 'AUTO'
                pt1.co = [ ps3.getX(), ps3.getY(), ps3.getZ() ]
        return c1
    
    def getBCurve(self, dataName):
        if (self.cgData is None):
            raise BGeoUtilsError("CGeoUtils data object not set.")
        c = self.cgData
        if (dataName is None):
            dataName = self.name
        if (dataName is None):
            dataName = c.getID()
        if (len(dataName) == 0):
            dataName = "UnnamedCurve"
        c0 = bpy.data.curves.get(dataName)
        if (c0 is None):
            c0 = bpy.data.curves.new(dataName, type = 'CURVE')
        if (c0 is None):
            raise BGeoUtilsError("Could not create Blender curve.")
        return c0
    
    def setFromBCurve(self, bCurve):
        """Initialize from Blender curve."""
        if (self.cgData is None):
            self.cgData = im.BezierSpline.create()
            self.mm.addLocalRef(self.cgData)
        else:
            self.cgData.clearSegments()
        c0 = self.cgData
        c0.setID(self.name)
        s0 = bCurve.splines[0]
        numPoints0 = len(s0.bezier_points)
        numCurves0 = numPoints0 - 1
        for i in range(0, numCurves0):
            ps0 = s0.bezier_points[i]
            ps1 = s0.bezier_points[i + 1]
            pt0 = im.Point(*ps0.co)
            pt1 = im.Point(*ps0.handle_right)
            pt2 = im.Point(*ps1.handle_left)
            pt3 = im.Point(*ps1.co)
            cs0 = im.BezierCurve.create(pt0, pt1, pt2, pt3)
            c0.addSegment(cs0)
    
    def createBData(self, dataName = None):
        self.createBCurve(dataName)
    
    def getBData(self, dataName = None):
        return self.getBCurve(dataName)
    
    def __str__(self):
        if (not self.cgData is None):
            return "BezierSpline[" + str(self.cgCurve) + "]"
        return "BezierSpline"

