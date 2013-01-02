#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CGeoUtils test."""
import math, os
import IFObjectBase as ib
import CGeoUtils as cg

def vecToString(v):
    s = "("
    for i in range(0, len(v)):
        if (i > 0):
            s += ", "
        s += str(v[i])
    s += ")"
    return s

print("CGeoUtils test 33")

d = cg.createUIntVector3(3, 8, 2)
c = cg.createUIntVector3(1, 0, 1)

s0 = cg.coordsToSeq(c, d)
print("  coordsToSeq(%s, %s) = %d" % (vecToString(c), vecToString(d), s0))
r0 = ib.UIntVector()
#s0 = 47
cg.seqToCoords(s0, d, r0)
print("  seqToCoords(%d, %s) = %s" % (s0, vecToString(d), vecToString(r0)))

print("All tests finished!")
