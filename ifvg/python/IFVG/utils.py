# -*- coding: utf-8 -*-
# ==========================================================================
# IFVG - Ionflux' Volumetric Graphics Library
# Copyright © 2014 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# utils.py          Utility functions.
# ==========================================================================
# 
# This file is part of IFVG - Ionflux' Volumetric Graphics Library.
# 
# IFVG - Ionflux' Volumetric Graphics Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later version.
# 
# IFVG - Ionflux' Volumetric Graphics Library is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with IFVG - Ionflux' Volumetric Graphics Library; if not, write 
# to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
# Boston, MA 02111-1307 USA
# 
# ==========================================================================
import os
import CGeoUtils as cg
import CIFVG as vg

def loadMesh(fileName):
    """Load a mesh."""
    pp0 = os.path.splitext(fileName)
    ext0 = pp0[1]
    
    if (ext0 == '.vgmesh'):
        # load vgmesh
        mesh0 = vg.Mesh.create()
        ioCtx.clear()
        ioCtx.openFileForInput(fileName)
        
        ioCtx.begin()
        mesh0.deserialize(ioCtx)
        ioCtx.finish()
    elif (ext0 == '.xml'):
        # load from xml file
        
        # register XML object factories
        cg.Vector2.getXMLObjectFactory()
        cg.Vector3.getXMLObjectFactory()
        cg.FaceData.getXMLObjectFactory()
        vg.Mesh.getXMLObjectFactory()
        
        xf0 = cg.MeshXMLFactory.upcast(cg.Mesh.getXMLObjectFactory())
        
        mesh0 = xf0.loadFromXMLFile(fileName)
    
    return mesh0

