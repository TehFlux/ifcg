#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math
import IFMapping as im
import CGeoUtils as cg

print "Testing Vector3 mappings..."

n = 20
im.initRandom(5)

ms0 = cg.Vector3MappingSet()

m0t0 = im.RandomNorm.create()
m0t0.setStdDev(1. / 3.)
m0t1 = im.Constant.create()
m0t1.setConstValue(0.)
m0 = cg.Compose3.create()
m0.setFuncX0(m0t0)
m0.setFuncX1(m0t0)
m0.setFuncX2(m0t1)
r0 = cg.Range(0., 1.)
m1 = cg.AcceptLength3.create()
m1.setSource(m0)
m1.setLengthRange(r0)
m2 = cg.Lookup3.create()
m2.setSource(m1)
m2.update(n)

mappings = [m0, m1, m2]

for m in mappings:
    ms0.addMapping(m)

for i in xrange(0, n):
    v0 = m2(float(i) / (n - 1))
    print ("  %02d: " % i) + str(v0) + ", " + str(v0.norm())

#print "  Average iterations for AcceptLength3: " + str(m3.getAverageIters())

print "All done!"
