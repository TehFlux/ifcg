#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import os, math
import CGeoUtils as cg
import AltjiraGeoUtils as ag

print("Altjira/GeoUtils test 16.")

prefix = 'test' + os.path.sep + 'images' + os.path.sep
inFile0 = 'jetmage01.png'

c0 = cg.Clock()
c0.start()

print ("  Testing ImageLoader (not using cache)...")

l0 = ag.ImageLoader()
l0.setPrefix(prefix)
l0.addImageID('image01', inFile0)
img0 = l0.getImage('image01')
c0.addLocalRef(img0)
is0 = img0.getSize()
print("    image01 (mapped):   " + str(img0) + ", size = " + str(is0))
img1 = l0.getImage(inFile0)
c0.addLocalRef(img1)
is1 = img1.getSize()
print("    image02 (unmapped): " + str(img1) + ", size = " + str(is1))

print ("  Testing ImageLoader (using cache)...")
cacheSize = 2 * is0
l0.initCache(cacheSize)
cache0 = l0.getCache()

img0 = l0.getImage('image01')
print("    image01 (mapped):   " + str(img0) + ", size = " + str(is0))
print("    cache state:")
print(cache0.getDebugInfo())

img1 = l0.getImage(inFile0)
print("    image02 (unmapped): " + str(img1) + ", size = " + str(is1))
print("    cache state:")
print(cache0.getDebugInfo())

l0.addImageID('image03', inFile0)
img2 = l0.getImage('image03')
is2 = img2.getSize()
print("    image03 (mapped):   " + str(img2) + ", size = " + str(is2))
print("    cache state:")
print(cache0.getDebugInfo())

print("    Fetching images...")
img1 = l0.getImage(inFile0)
img2 = l0.getImage('image03')
img0 = l0.getImage('image01')
print("      cache state:")
print(cache0.getDebugInfo())

c0.stop()
print ("  Done (elapsed time " + str(c0.getElapsedTime()) + " secs).")

print("All done!")
