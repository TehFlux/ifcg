# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010-2012 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# Camera.py          Blender camera tools.
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
import BGeoUtils.utils as bgu
import bpy

class Camera:
    """Camera.
    
    A wrapper around a CGeoUtils.Camera for use with Blender."""
    
    def __init__(self, cgCam = None):
        # memory management
        self.mm = ib.IFObject()
        self.cgCam = cgCam
        if (not self.cgCam is None):
            self.mm.addLocalRef(cgCam)
    
    def setFromBCamera(self, bCam):
        """Initialize from Blender camera."""
        if (self.cgCam is None):
            self.cgCam = cg.Camera.create()
            self.mm.addLocalRef(cgCam)
        c = self.cgCam
        m0 = bCam.matrix_world
        m1 = cg.Matrix4()
        bgu.getCGMatrix(m0, m1)
        right = m1.getC0().getV3().copy()
        #cg.Vector3.create(*m[0][0:3])
        up = m1.getC1().getV3().copy()
        #cg.Vector3.create(*m[1][0:3])
        direction = m1.getC2().getV3().copy()
        direction.flipIP()
        #cg.Vector3.create(*m[2][0:3])
        location = m1.getC3().getV3().copy()
        #cg.Vector3.create(*m[3][0:3])
        lens = bCam.data.lens
        cs0 = cg.CameraSetupFlags()
        cs0.useDirection = True
        cs0.useRight = True
        cs0.useUp = True
        cs0.useLookAt = False
        cs0.useSky = False
        cs0.useAngle = False
        cs0.useLens = True
        c.setLocation(location)
        c.setRight(right)
        c.setUp(up)
        c.setDirection(direction)
        c.setLens(lens)
        c.initVectors()
        c.validate(cs0)
    
    def createBCamera(self, camName = None):
        """Create Blender camera.
        
        Create a new Blender camera from the current CGeoUtils camera."""
        if (self.cgCam is None):
            raise BGeoUtilsError("CGeoUtils camera not set.")
        c = self.cgCam
        if (camName is None):
            camName = c.getID()
        if (len(camName) == 0):
            camName = "unnamedCamera"
        c0 = bpy.data.cameras.new(camName)
        c0.lens = c.getLens()
    
    def getBMatrixWorld(self):
        """Get Blender camera world matrix.
        
        Returns a matrix that can be assigned to the matrix_world property 
        of a Blender camera object."""
        if (self.cgCam is None):
            raise BGeoUtilsError("CGeoUtils camera not set.")
        c = self.cgCam
        m0 = c.getExtrinsicMatrix()
        loc0 = m0.getC3()
        m1 = cg.Matrix4(cg.Matrix4.UNIT)
        m1.setElement(1, 1, -1.)
        m1.setElement(2, 2, -1.)
        m3 = cg.Matrix4(cg.Matrix4.UNIT)
        m0.multiply(m1, m3)
        m3.setC3(loc0)
        m3.transposeIP()
        return bgu.getBlenderMatrix(m3)
    
    def __str__(self):
        if (not self.cgCam is None):
            return str(self.cgCam)
            return "Camera"

