# -*- coding: utf-8 -*-
"""Blender GeoUtils initialization."""
import bpy
import sys, os

GEOUTILS_SVN_DIR = '/home/flux4/svn/stuff/trunk/geoutils'
"""GeoUtils SVN directory."""
GEOUTILS_SITE_DIR = '/home/flux4/usr/python3.2/lib/python3.2/site-packages'
"""GeoUtils site packages directory."""

def registerOperators():
    """Register operators."""
    import BGeoUtils.Operator as bop
    bpy.utils.register_class(bop.ShowPCABase)
    bpy.utils.register_class(bop.GetSelectedFaceIndices)
    bpy.utils.register_class(bop.MakeFacesPlanar)

def register():
    if (not hasattr(bpy, 'geoutils')):
        # Set up Python path.
        sys.path.append(GEOUTILS_SVN_DIR + os.path.sep + 'python')
        sys.path.append(GEOUTILS_SITE_DIR)
        ## Create GeoUtils data object.
        #import BGeoUTils.base
        #bpy.geoutils = BGeoUtils.base.Data()
        bpy.geoutils = {}
        registerOperators()
        print("GeoUtils for Blender initialized.")

def unregister():
    # Unregister operators.
    import BGeoUtils.Operator as bop
    bpy.utils.unregister_class(bop.ShowPCABase)
    bpy.utils.unregister_class(bop.GetSelectedFaceIndices)
    bpy.utils.unregister_class(bop.MakeFacesPlanar)

if __name__ == "__main__":
    register()

