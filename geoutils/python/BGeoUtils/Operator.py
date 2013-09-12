# -*- coding: utf-8 -*-
"""Blender operators.

These operators provide functionality of GeoUtils from within the 
Blender UI. They can be accessed by pressing space and typing some characters 
of the operator label.
"""
#import IFMapping as im
import IFObjectBase as ib
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
#import BGeoUtils.Object as bgo
#import BGeoUtils.Material as bgMat
import BGeoUtils.utils as bgu
import bpy

class ShowPCABase(bpy.types.Operator):
    """Show PCA base."""
    bl_idname = "geoutils.showpcabase"
    bl_label = "GeoUtils Show PCA base"
    
    name = bpy.props.StringProperty(name = "Name", 
        default = "")
    scale = bpy.props.FloatProperty(name = "Scale", 
        default = 1.)
    
    def execute(self, context):
        if (self.name == ""):
            o0 = bpy.context.active_object
            n0 = o0.name
        else:
            o0 = bpy.data.objects.get(self.name)
            n0 = self.name
        m0 = o0.data
        m1 = bgm.Mesh(n0)
        m1.setFromBMesh(m0)
        vs0 = m1.cgMesh.getVertexSource()
        pca0 = vs0.getPCABase()
        b0 = vs0.getBarycenter()
        tm = o0.matrix_basis
        tr0 = cg.Vector3(tm[3][0], tm[3][1], tm[3][2])
        t0 = bgu.visualizeTransform(pca0, tr0 + b0, n0 + "_PCA", self.scale)
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)

class GetSelectedFaceIndices(bpy.types.Operator):
    """Get selected face indices."""
    bl_idname = "geoutils.getselectedfaceindices"
    bl_label = "GeoUtils Get selected face indices"
    
    name = bpy.props.StringProperty(name = "Name", 
        default = "")
    
    def execute(self, context):
        if (self.name == ""):
            o0 = bpy.context.active_object
            n0 = o0.name
        else:
            o0 = bpy.data.objects.get(self.name)
            n0 = self.name
        m0 = o0.data
        sf = []
        for i in range(0, len(m0.faces)):
            f = m0.faces[i]
            if (f.select):
                sf += [i]
        bpy.geoutils['selected_faces'] = sf
        print("selected faces: " + str(sf))
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)

class MakeFacesPlanar(bpy.types.Operator):
    """Make faces planar."""
    bl_idname = "geoutils.makefacesplanar"
    bl_label = "GeoUtils Make faces planar"
    
    name = bpy.props.StringProperty(name = "Name", 
        default = "")
    maxIterations = bpy.props.IntProperty(name = "Max iterations", 
        default = 10000)
    strength = bpy.props.FloatProperty(name = "Strength", 
        default = 1.)
    tolerance = bpy.props.FloatProperty(name = "Tolerance", 
        default = 1e-5)
    
    def execute(self, context):
        if (self.name == ""):
            o0 = bpy.context.active_object
            n0 = o0.name
        else:
            o0 = bpy.data.objects.get(self.name)
            n0 = self.name
        m0 = o0.data
        n1 = m0.name
        sf = ib.UIntVector()
        for i in range(0, len(m0.faces)):
            f = m0.faces[i]
            if (f.select):
                sf.push_back(i)
        m1 = bgm.Mesh(n1)
        m1.setFromBMesh(m0)
        m2 = m1.cgMesh
        m2.update()
        nonPlanar = m2.makePlanar(sf, self.maxIterations, self.strength, 
            self.tolerance)
        m1.update()
        self.report({'INFO'}, "Non-planar faces remaining: " 
            + str(nonPlanar))
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)

class SaveMesh(bpy.types.Operator):
    """Save mesh."""
    bl_idname = "geoutils.savemesh"
    bl_label = "GeoUtils Save mesh"
    
    filepath = bpy.props.StringProperty(name = "File path", 
        subtype="FILE_PATH", default = "mesh.xml")
    name = bpy.props.StringProperty(name = "Name", 
        default = "")
    
    def execute(self, context):
        o0 = bpy.context.active_object
        bm0 = o0.data
        if (self.name != ""):
            n0 = str(self.name)
        else:
            n0 = o0.name
        gm0 = bgm.Mesh(n0)
        gm0.setFromBMesh(bm0)
        gm0.cgMesh.writeToXMLFile(self.filepath)
        return {'FINISHED'}
    
    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

