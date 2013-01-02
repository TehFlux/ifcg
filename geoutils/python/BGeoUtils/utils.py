# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010-2012 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# utils.py          Blender utility funtions.
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
import BGeoUtils.Object as bgo
import BGeoUtils.Material as bgMat

def visualizeTransform(m, t = cg.Vector3.ZERO, name = "UnnamedT", 
    scale0 = 1.):
    """Visualize a transform.
    
    Create Blender objects that visualize a transformation, consisting of a 
    matrix and a translation vector.
    """
    mm = bgMat.MaterialMap.getDefault()
    r0 = mm.getMaterial('Red')
    g0 = mm.getMaterial('Green')
    b0 = mm.getMaterial('Blue')
    a0 = bgo.Arrow(name + "U", scale = scale0, create = True)
    u = m.getC0()
    a0.setDirection(u)
    if (not t is None):
        a0.setBasePoint(t)
    a0.setMaterial(r0)
    a1 = bgo.Arrow(name + "V", scale = scale0, create = True)
    v = m.getC1()
    a1.setDirection(v)
    if (not t is None):
        a1.setBasePoint(t)
    a1.setMaterial(g0)
    a2 = bgo.Arrow(name + "W", scale = scale0, create = True)
    w = m.getC2()
    a2.setDirection(w)
    if (not t is None):
        a2.setBasePoint(t)
    a2.setMaterial(b0)
    return (a0, a1, a2)

