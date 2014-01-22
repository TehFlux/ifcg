# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010-2012 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# Material.py          Blender material tools.
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
"""Blender materials."""
import bpy

def makeHexByte(value = 0.0):
    """Convert float value to hex byte value."""
    iv = int(round(value * 255.))
    if (iv > 255):
        iv = 255
    if (iv < 0):
        iv = 0
    return hex(iv)[2:].rjust(2, '0')

def makeHexColor(red = 0.0, green = 0.0, blue = 0.0, alpha = 1.0):
    """Convert color to hex representation."""
    return (makeHexByte(red) + makeHexByte(green) + makeHexByte(blue)  
        + makeHexByte(alpha))

def createSimpleMaterial(name = "UnnamedMaterial", red = 0.5, green = 0.5, 
    blue = 0.5, alpha = 1.0, spec = 0.1, hardness = 10, emit = 0.0, 
    rayTransp = False, zTransp = False, texture = None, mType = 'SURFACE', 
    recShadows = True, diffIntensity = 1.):
    """Create a simple material.
    
    Returns a material with the specified name, color, specular value and 
    specular hardness. If a Blender material with the specified name already 
    exists, that material will be returned instead."""
    m = bpy.data.materials.get(name)
    if (m is None):
        m = bpy.data.materials.new(name)
    m.diffuse_color[0] = red
    m.diffuse_color[1] = green
    m.diffuse_color[2] = blue
    m.specular_intensity = spec
    m.specular_hardness = int(round(511. * hardness))
    m.alpha = alpha
    m.emit = emit
    m.type = mType
    m.diffuse_intensity = diffIntensity
    if (rayTransp):
        m.use_transparency = True
        m.transparency_method = 'RAYTRACE'
    elif (zTransp):
        m.use_transparency = True
        m.transparency_method = 'Z_TRANSPARENCY'
    if (not recShadows):
        m.use_shadows = False
    if (not texture is None):
        # TODO: Add texture.
        pass
    return m

class MaterialMap:
    """Material map.
    
    A map of materials by name.
    
    materials  -- Dictionary of materials indexed by name."""
    
    def __init__(self):
        self.materials = {}
    
    def getSimpleMaterial(self, name = "UnnamedMaterial", red = 0.5, 
        green = 0.5, blue = 0.5, alpha = 1., spec = 0.1, hardness = 10, 
        emit = 0., rayTransp = False, zTransp = False, texture = None, 
        mType = 'SURFACE', recShadows = True, diffIntensity = 1.):
        """Get simple material.
        
        If a material with the specified name already exists in the map or as 
        a blender material, the material is returned. Otherwise, a new 
        material with the specified parameters is created."""
        m = bpy.data.materials.get(name)
        if (m is None):
            m = createSimpleMaterial(name, red, green, blue, alpha, spec, 
                hardness, emit, rayTransp, zTransp, texture, mType, 
                recShadows, diffIntensity)
        self.materials[name] = m
        return m
    
    def createMaterialsFromColors(self, colors, red = 0., green = 0., 
        blue = 0., alpha = 1., spec = 0.1, hardness = 10, emit = 0.):
        """Create materials from colors.
        
        Creates materials from a list of colors. Each element of the color 
        list specifies a color as a list of red, green, blue and alpha 
        components. It is also possible to specify a specular and hardness 
        value for the material which is created. Values which are not 
        explicitly specified are initialized to the default. Returns a list 
        of materials corresponding to the colors."""
        result = []
        for c in colors:
            if (len(c) >= 1):
                r = c[0]
            else:
                r = red
            if (len(c) >= 2):
                g = c[1]
            else:
                g = green
            if (len(c) >= 3):
                b = c[2]
            else:
                b = blue
            if (len(c) >= 4):
                a = c[3]
            else:
                a = alpha
            if (len(c) >= 5):
                s = c[4]
            else:
                s = spec
            if (len(c) >= 6):
                h = c[5]
            else:
                h = hardness
            if (len(c) >= 7):
                e = c[6]
            else:
                e = emit
            name = "MatColor_" + utils.makeHexColor(r, g, b, a)
            result += [self.getSimpleMaterial(name, r, g, b, a, s, h, e)]
        return result
    
    def addDefaultMaterials(self):
        """Add some default materials."""
        self.getSimpleMaterial('Red', 1., 0., 0.)
        self.getSimpleMaterial('Green', 0., 1., 0.)
        self.getSimpleMaterial('Blue', 0., 0., 1.)
        self.getSimpleMaterial('Magenta', 1., 0., 1.)
        self.getSimpleMaterial('Cyan', 0., 1., 1.)
        self.getSimpleMaterial('Yellow', 1., 1., 0.)
        self.getSimpleMaterial('GlowingRed', 1., 0., 0., emit = 1.)
        self.getSimpleMaterial('GlowingGreen', 0., 1., 0., emit = 1.)
        self.getSimpleMaterial('GlowingBlue', 0., 0., 1., emit = 1.)
        self.getSimpleMaterial('GlowingMagenta', 1., 0., 1., emit = 1.)
        self.getSimpleMaterial('GlowingCyan', 0., 1., 1., emit = 1.)
        self.getSimpleMaterial('GlowingYellow', 1., 1., 0., emit = 1.)
        self.getSimpleMaterial('GlowingRed3', 1., 0., 0., emit = 0.3)
        self.getSimpleMaterial('GlowingGreen3', 0., 1., 0., emit = 0.3)
        self.getSimpleMaterial('GlowingBlue3', 0., 0., 1., emit = 0.3)
        self.getSimpleMaterial('GlowingMagenta3', 1., 0., 1., emit = 0.3)
        self.getSimpleMaterial('GlowingCyan3', 0., 1., 1., emit = 0.3)
        self.getSimpleMaterial('GlowingYellow3', 1., 1., 0., emit = 0.3)
        self.getSimpleMaterial('WireGlowingRed', 1., 0., 0., emit = 1., 
            mType = 'WIRE')
        self.getSimpleMaterial('WireGlowingGreen', 0., 1., 0., emit = 1., 
            mType = 'WIRE')
        self.getSimpleMaterial('WireGlowingBlue', 0., 0., 1., emit = 1., 
            mType = 'WIRE')
        self.getSimpleMaterial('WireGlowingMagenta', 1., 0., 1., emit = 1., 
            mType = 'WIRE')
        self.getSimpleMaterial('WireGlowingYellow', 1., 1., 0., emit = 1., 
            mType = 'WIRE')
    
    def getMaterial(self, name):
        return self.materials[name]
    
    def __getitem__(self, name):
        return self.getMaterial(name)
    
    @classmethod
    def getDefault(cls):
        """Get the default material map."""
        if (not hasattr(MaterialMap, 'DEFAULT_MAP')):
            MaterialMap.DEFAULT_MAP = MaterialMap()
            MaterialMap.DEFAULT_MAP.addDefaultMaterials()
        return MaterialMap.DEFAULT_MAP

