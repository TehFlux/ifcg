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
import CGeoUtils as cg
from BGeoUtils import BGeoUtilsError
import bpy

class Camera:
    """Camera.
    
    A wrapper around a CGeoUtils.Camera for use with Blender."""
    
    def __init__(self, cgCam = None):
        self.cgCam = cgCam
    
    def setFromBCamera(self, bCam):
        """Initialize from Blender mesh."""
        if (self.cgCam is None):
            self.cgCam = cg.Camera()
        c = self.cgCam
        m = bCam.matrix_world
        right = cg.Vector3(*m[0][0:3])
        up = cg.Vector3(*m[1][0:3])
        direction = cg.Vector3(*m[2][0:3]).flip()
        location = cg.Vector3(*m[3][0:3])
        lens = bCam.data.lens
        cs0 = cg.CameraSetupFlags()
        cs0.useDirection = True
        cs0.useRight = True
        cs0.useUp = True
        cs0.useLookAt = False
        cs0.useSky = False
        cs0.useAngle = False
        cs0.useLens = True
        self.cgCam.setRight(right)
        self.cgCam.setUp(up)
        self.cgCam.setDirection(direction)
        self.cgCam.setLocation(location)
        self.cgCam.setLens(lens)
        self.cgCam.validate(cs0)
    
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
        # TODO: Implementation.
        return c0
    
    def __str__(self):
        if (not self.cgCam is None):
            return str(self.cgCam)
            return "Camera"

