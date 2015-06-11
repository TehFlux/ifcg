# -*- coding: utf-8 -*-
# ==========================================================================
# IFVG - Ionflux' Volumetric Graphics Library
# Copyright © 2014 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# __init__.py          Module initialization.
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
__all__ = [ "utils" ]

class IFVGError(Exception):
    """Exception base class for the IFVG module."""
    
    def __init__(self, value):
        self.value = value
    
    def __str__(self):
        return str(self.value)

