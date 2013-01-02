#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Create random points for testing the geoutils JavaScript implementation."""

import random, sys, ifcolor

#random.seed(12)

def getRandomCoords(r = [-1., 1]):
    """Get random coordinates."""
    return [
        (r[1] - r[0]) * random.random() + r[0], 
        (r[1] - r[0]) * random.random() + r[0], 
        (r[1] - r[0]) * random.random() + r[0] 
    ]

if (len(sys.argv) >= 2):
    num = int(sys.argv[1])
else:
    num = 10

result = "var points0 = [\n"
for i in xrange(0, num):
    p = getRandomCoords()
    c = [ random.random(), random.random(), random.random() ]
    if (i > 0):
        result += ",\n"
    result += ("    new Point3(" + str(p[0]) + ", " + str(p[1]) + ", " 
        + str(p[2]) + ", \"#" + ifcolor.makeHexColor(*c)[0:6] + "\")")
result += "\n];"

print result
