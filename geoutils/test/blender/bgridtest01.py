# -*- coding: utf-8 -*-
import IFMapping as im
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Object as bgo
import BGeoUtils.Material as bm

def createGrid(gridName, direction, mat1, mat2, mat3, gridStart, gridStep1, gridStep2, 
    gridStop, axis1, axis2, emphasizeAxes = True, emphasizePlane = True):
    cp = cg.Vector3(gridStart)
    i = 0
    j = 0
    while (not im.gt(cp[axis2], gridStop[axis2])):
        while (not im.gt(cp[axis1], gridStop[axis1])):
            width = 0.001
            mat = mat1
            if (im.eq(cp[axis2], 0.) 
                and emphasizePlane):
                width = width * 2
                mat = mat2
            if (im.eq(cp[axis1], 0.) and im.eq(cp[axis2], 0.) 
                and emphasizeAxes):
                width = width * 2.5
                mat = mat3
            cyl = bgo.Cylinder("Cyl_" + gridName + ("_%03d_%03d" % (i, j)), 
                10, 10., width)
            cyl.createBObject()
            cyl.setDirection(direction)
            cyl.setLocation(cp)
            cyl.setMaterial(mat)
            cp = cp + gridStep1
            i += 1
        cp.setElement(axis1, gridStart[axis1])
        cp = cp + gridStep2
        i = 0
        j += 1

mm = bm.MaterialMap()
mm.addDefaultMaterials()

gridStep = 1.

blueMat = mm.getMaterial('Blue')
redMat = mm.getMaterial('Red')
greenMat = mm.getMaterial('Green')
cyanMat = mm.getMaterial('Cyan')
glowingBlueMat = mm.getMaterial('GlowingBlue')
glowingRedMat = mm.getMaterial('GlowingRed')
glowingGreenMat = mm.getMaterial('GlowingGreen')
glowingCyanMat = mm.getMaterial('GlowingCyan')
glowingMagentaMat = mm.getMaterial('GlowingMagenta')
glowingBlueMat3 = mm.getMaterial('GlowingBlue3')
glowingRedMat3 = mm.getMaterial('GlowingRed3')
glowingGreenMat3 = mm.getMaterial('GlowingGreen3')
glowingCyanMat3 = mm.getMaterial('GlowingCyan3')

axis10 = cg.AXIS_X
axis20 = cg.AXIS_Y

gridStart0 = cg.Vector3(-5., -5., 0.)
gridStep10 = cg.Vector3(gridStep, 0., 0.)
gridStep20 = cg.Vector3(0., gridStep, 0.)
gridStop0 = cg.Vector3(5., 5., 0.)
direction0 = cg.Vector3.E_Z

createGrid("XY", direction0, glowingRedMat3, glowingRedMat3, 
    glowingMagentaMat,  gridStart0, gridStep10, gridStep20, gridStop0, 
    axis10, axis20, True, False)

axis11 = cg.AXIS_X
axis21 = cg.AXIS_Z

gridStart1 = cg.Vector3(-5., 0., -5.)
gridStep11 = cg.Vector3(gridStep, 0., 0.)
gridStep21 = cg.Vector3(0., 0., gridStep)
gridStop1 = cg.Vector3(5., 0., 5.)
direction1 = cg.Vector3.E_Y

createGrid("XZ", direction1, glowingBlueMat3, glowingCyanMat, 
    glowingCyanMat, gridStart1, gridStep11, gridStep21, gridStop1, 
    axis11, axis21, True, True)

axis12 = cg.AXIS_Y
axis22 = cg.AXIS_Z

gridStart2 = cg.Vector3(0., -5., -5.)
gridStep12 = cg.Vector3(0., gridStep, 0.)
gridStep22 = cg.Vector3(0., 0., gridStep)
gridStop2 = cg.Vector3(0., 5., 5.)
direction2 = cg.Vector3.E_X

createGrid("YZ", direction2, glowingGreenMat3, glowingCyanMat, 
    glowingCyanMat, gridStart2, gridStep12, gridStep22, gridStop2, axis12, 
    axis22, True, True)

