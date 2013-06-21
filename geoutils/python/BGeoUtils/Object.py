#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010-2012 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# Object.py          Blender mesh tools.
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
import CGeoUtils as cg
from BGeoUtils import BGeoUtilsError
import BGeoUtils.Mesh as bm
import CGeoUtils as cg
import bpy

def createBObject(objectName, mesh):
    """Create a Blender object for a a mesh."""
    o0 = bpy.data.objects.new(objectName, mesh)
    o1 = bpy.context.scene.objects.link(o0)
    return o1

class Object:
    """Object.
    
    Convenience class for creating a Blender object from a GeoUtils Mesh.
    
    name     -- object name
    mesh     -- BGeoUtils.Mesh
    bObject  -- Blender object
    """
    
    def __init__(self, name = "Unnamed", mesh = None, create = False):
        self.name = name
        self.mesh = mesh
        o0 = bpy.data.objects.get(self.name)
        if (not o0 is None):
            # Use existing Blender object.
            self.bObject = o0
        else:
            self.bObject = None
        if (create and not (mesh is None)):
            self.createBObject()
    
    def moveToLayer(self, layer):
        """Move object to layer."""
        o0 = bpy.data.objects.get(self.name)
        l0 = o0.layers
        l0[layer] = True
        for i in range(0, len(l0)):
            if (i != layer):
                l0[i] = False
    
    def getBObject(self):
        """Get Blender object."""
        o0 = bpy.data.objects.get(self.name)
        if (o0 is None):
            o0 = bpy.data.objects.new(self.name, self.mesh.getBMesh())
        if (o0 is None):
            raise BGeoUtilsError("Could not create Blender object.")
        return o0
    
    def createBObject(self, layer = 0):
        """Create a Blender object for a a mesh."""
        b0 = self.getBObject()
        b1 = bpy.context.scene.objects.link(b0)
        self.bObject = b0
        self.moveToLayer(layer)
        return self.bObject
    
    def removeBObject(self):
        """Remove Blender object."""
        if (not self.bObject is None):
            o0 = bpy.data.objects.get(self.name)
            m0 = o0.data
            bpy.context.scene.objects.unlink(o0)
            bpy.data.objects.remove(o0)
            bpy.data.meshes.remove(m0)
            self.mesh = None
            self.bObject = None
    
    def setMaterial(self, material):
        """Set the material of the object."""
        o0 = bpy.data.objects.get(self.name)
        m0 = o0.data
        m0.materials.append(material)
        o0.update_tag({'OBJECT', 'DATA'})
    
    def setLocation(self, v):
        """Set object location."""
        o0 = bpy.data.objects.get(self.name)
        o0.location = [v[0], v[1], v[2]]
        o0.update_tag({'OBJECT', 'DATA'})
    
    def translate(self, v):
        """Translate."""
        o0 = bpy.data.objects.get(self.name)
        l0 = o0.location
        o0.location = [
            l0[0] + v[0], 
            l0[1] + v[1], 
            l0[2] + v[2]
        ]
        o0.update_tag({'OBJECT', 'DATA'})
    
    def setTransform(self, m, t = [0., 0., 0.]):
        """Set object transformation.
        
        m  -- transform matrix (3x3)
        t  -- location vector"""
        c0 = m.getC0()
        c1 = m.getC1()
        c2 = m.getC2()
        o0 = bpy.data.objects.get(self.name)
        o0.matrix_basis = [
            [ c0[0], c0[1], c0[2], 0. ], 
            [ c1[0], c1[1], c1[2], 0. ], 
            [ c2[0], c2[1], c2[2], 0. ], 
            [ t[0], t[1], t[2], 1. ]
        ]
        o0.update_tag({'OBJECT', 'DATA'})
    
    def __str__(self):
        return "Object['" + str(self.name) + "]"

class PointingObject(Object):
    """Pointing object.
    
    Base class for objects that have a base point and can point in some 
    direction."""
    
    def __init__(self, name = "Unnamed", mesh = None, create = False):
        Object.__init__(self, name, mesh, create)
    
    def setDirection(self, d):
        """Set direction.
        
        Set the direction in which the object is pointing."""
        n = d.normalize()
        t = n.ortho().normalize()
        b = n.cross(t).normalize()
        TM = cg.Matrix3()
        TM.setC0(t)
        TM.setC1(b)
        TM.setC2(n)
        self.setTransform(TM)
    
    def setBasePoint(self, p):
        """Set base point.
        
        Set the point from which the object starts."""
        b = self.mesh.cgMesh.getBounds()
        l0 = b.getExtent(cg.AXIS_Z)
        o0 = bpy.data.objects.get(self.name)
        m = o0.matrix_basis
        v0 = cg.Vector3(m[0][2], m[1][2], m[2][2])
        self.setLocation(p + v0.normalize() * 0.5 * l0)

class Arrow(PointingObject):
    """Arrow.
    
    Arrow object."""
    
    def __init__(self, name = "UnnamedArrow", subDivs = 10, length = 1., 
        radius = 0.005, headLength = 0.1, headRadius = 4., scale = 1.,
        mesh = None, create = False):
        if (mesh is None):
            m0 = cg.Mesh.arrow(subDivs, length * scale, radius * scale, 
                headLength, headRadius)
            m1 = bm.Mesh(name + "M", m0, True)
            mesh = m1
        Object.__init__(self, name, mesh, create)

class Cylinder(PointingObject):
    """Cylinder.
    
    Cylinder object."""
    
    def __init__(self, name = "UnnamedCylinder", subDivs = 10, length = 1., 
        radius = 0.5, scale = 1., mesh = None, create = False):
        if (mesh is None):
            m0 = cg.Mesh.cylinder(subDivs, length * scale, radius * scale)
            m1 = bm.Mesh(name + "M", m0, True)
            mesh = m1
        Object.__init__(self, name, mesh, create)

