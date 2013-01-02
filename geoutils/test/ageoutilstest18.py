#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test 34."""
import math, os
import IFObjectBase as ib
import CGeoUtils as cg
import Altjira as ai
import AltjiraGeoUtils as ag

inputImage0 = "test/images/map01.png"
outputImage0 = "temp/ag18_01.png"

markColor = ai.Color(0., 0., 1., 0.2)
P = cg.Vector3(151, 205, 0)
phi = -math.pi * 0.25
R0 = cg.Matrix3.rotate(phi)
U = R0 * cg.Vector3.E_X

print("Altjira/GeoUtils test 18.")

# memory management
mm = ib.IFObject()

print("  Loading image...")

img0 = ag.Image.create()
img0.loadFromFile(inputImage0)
mm.addLocalRef(img0)

print("    width = %d, height = %d" % (img0.getWidth(), img0.getHeight()))

print("  Creating AABB tree...")

print("    Creating voxels...")

bb0 = cg.BoundingBox.create()
mm.addLocalRef(bb0)
img0.getPixelTree(bb0)

numPixels = bb0.getNumItems()

print("    %d voxels created" % numPixels)

print("    Building hierarchy...")

sp0 = cg.SplitSet.create()
sp0.addSplits(cg.AXIS_X, 1)
sp0.addSplits(cg.AXIS_Y, 1)
mm.addLocalRef(sp0)

bb0.split(sp0, True, 4, 0, 0, cg.DEFAULT_TOLERANCE, True)

print("  Testing line intersection...")

l0 = cg.Line3.create()
l0.setP(P)
l0.setU(U)
mm.addLocalRef(l0)

print("    " + l0.getString())

bs0 = bb0.getItemsOnRay(l0)

print("  Processing results...")

bb1 = cg.BoundingBox.create()
mm.addLocalRef(bb1)
bb1.addItems(bs0)
bs1 = cg.BoxBoundsItemSet()
bb1.getLeaves(bs1)

img0.markPixels(bs1, markColor)

print("    Writing result image to '%s'..." % outputImage0)

img0.writeToFile(outputImage0)

pl0 = cg.Plane3.createFromNormal(l0.getU(), cg.Vector3.E_X, 
  cg.Vector3(3, 3, 0))

bv0 = cg.BoxBoundsItemVector()
cg.setToVector(bs1, bv0)
cmp0 = cg.BoxBoundsItemCompare()
cmp1 = cg.BoxBoundsItemCompareDistancePlane3.create(pl0)
cmp0.setTarget(cmp1)
cg.sort(bv0, cmp0)

#for i in range(0, bv0.size()):
#    it0 = bv0[i]
#    d0 = it0.getCenter().distanceToPlane(pl0)
#    print(("[%03d] " % i) + it0.getString() + ", d = " + str(d0))

print("All done!")
