#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# GeoUtils - Ionflux' Geometry Library
# Copyright © 2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# geoutils.py          Geometry utilities.
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
"""Geometry utilities.

This module provides functions to solve geometric problems in 2D and 3D 
space. Vectors are represented as lists and matrices as row-major lists of 
lists. All calculations are done in pure Python. There are special classes for 
geometric primitives like vertices, lines, planes and polygons."""

import math, copy

DEFAULT_TOLERANCE = 1.0e-6
"""Default tolerance for comparisons."""

E_X_3 = [1., 0., 0.]
"""Unit vector x (3D)."""
E_Y_3 = [0., 1., 0.]
"""Unit vector y (3D)."""
E_Z_3 = [0., 0., 1.]
"""Unit vector z (3D)."""

AXIS_X = 0
"""Axis ID: X."""
AXIS_Y = 1
"""Axis ID: Y."""
AXIS_Z = 2
"""Axis ID: Z."""

class GeoUtilsError(Exception):
    """Exception base class for the GeoUtils module."""
    
    def __init__(self, value):
        self.value = value
    
    def __str__(self):
        return str(self.value)

class SolveError(GeoUtilsError):
    """Exception which is thrown when a matrix equation cannot be solved."""
    
    def __init__(self, value):
        GeoUtilsError.__init__(self, value)
    
    def __str__(self):
        return str(self.value)

class IntersectionError(GeoUtilsError):
    """Exception which is thrown when an intersection calculation fails."""
    
    def __init__(self, value):
        GeoUtilsError.__init__(self, value)
    
    def __str__(self):
        return str(self.value)

class BoundingBoxError(GeoUtilsError):
    """Exception which is thrown when a bounding box is used improperly."""
    
    def __init__(self, value):
        GeoUtilsError.__init__(self, value)
    
    def __str__(self):
        return str(self.value)
    
    def __repr__(self):
        return 'BoundingBoxError(' + repr(self.value) + ')'

class FaceError(GeoUtilsError):
    """Exception which is thrown when a calculation fails for a face."""
    
    def __init__(self, value):
        GeoUtilsError.__init__(self, value)
    
    def __str__(self):
        return str(self.value)

class ItemSourceError(GeoUtilsError):
    """Exception which is thrown when an item source is used improperly."""
    
    def __init__(self, value):
        GeoUtilsError.__init__(self, value)
    
    def __str__(self):
        return str(self.value)

class InterpolationError(GeoUtilsError):
    """Exception which is thrown when interpolation fails."""
    
    def __init__(self, value):
        GeoUtilsError.__init__(self, value)
    
    def __str__(self):
        return str(self.value)

class RenderError(GeoUtilsError):
    """Exception which is thrown when rendering fails."""
    
    def __init__(self, value):
        GeoUtilsError.__init__(self, value)
    
    def __str__(self):
        return str(self.value)

def axisToString(axis):
    """Get string representation of axis."""
    if (axis == AXIS_X):
        return "X"
    if (axis == AXIS_Y):
        return "Y"
    if (axis == AXIS_Z):
        return "Z"
    return "<invalid>"

def add2(v0, v1):
    """Add two 2D vectors."""
    return [ v0[0] + v1[0], v0[1] + v1[1] ]

def sub2(v0, v1):
    """Subtract two 2D vectors."""
    return [ v0[0] - v1[0], v0[1] - v1[1] ]

def mult2(c, v):
    """Multiply 2D vector by a scalar."""
    return [ c * v[0], c * v[1] ]

def flip2(v):
    """Flip 2D vector around origin."""
    return mult2(-1., v)

def swap2(vec):
    """Swap elements of 2D vector."""
    return [vec[1], vec[0]]

def dot2(v0, v1):
    """Calculate dot product of 2D vectors."""
    return v0[0] * v1[0] + v0[1] * v1[1]

def norm2(v):
    """Calculate the norm of a 2D vector."""
    return math.sqrt(dot2(v, v))

def swapColumns2x2(mat):
    """Swap columns of 2x2 matrix."""
    return [swap2(mat[0]), swap2(mat[1])]

def transpose2x2(mat):
    """Transpose 2x2 matrix."""
    return [
        [ mat[0][0], mat[1][0] ],
        [ mat[0][1], mat[1][1] ]
    ]

def unit3x3():
    """Create 3x3 unit matrix."""
    return [
        [ 1., 0., 0. ],
        [ 0., 1., 0. ],
        [ 0., 0., 1. ]
    ]

def scale3x3(sx = 1., sy = 1.):
    """Create a 3x3 scale matrix."""
    r = unit3x3()
    r[0][0] = sx
    r[1][1] = sy
    return r

def translate3x3(tx = 0., ty = 0.):
    """Create a 3x3 translate matrix."""
    r = unit3x3()
    r[0][2] = tx
    r[1][2] = ty
    return r

def rotate3x3(phi = 0.):
    """Create a 3x3 rotation matrix."""
    return [
        [ math.cos(phi), -math.sin(phi), 0. ],
        [ math.sin(phi), math.cos(phi), 0. ],
        [ 0., 0., 1. ]
    ]

def permuteColumns3x3(mat, p):
    """Permute 3x3 matrix."""
    return [permute3(mat[0], p), permute3(mat[1], p), permute3(mat[2], p)]

def solve2x2(mat, vec):
    """Solve 2x2 matrix equation.
    
    Solve a 2x2 matrix equation with the specified result vector. Returns 
    the solution vector. Raises SolveError if the matrix equation cannot be 
    solved."""
    y11 = mat[0][0]
    y12 = mat[0][1]
    y21 = mat[1][0]
    y22 = mat[1][1]
    d = vec[0]
    e = vec[1]
    result = None
    if ((y11 != 0.0)
        and ((y22 * y11 - y12 * y21) != 0.0)):
        y = (e * y11 - d * y21) / (y22 * y11 - y12 * y21)
        x = (d - y * y12) / y11
        result = [x, y]
    elif ((y12 != 0)
        and ((y21 * y12 - y11 * y22) != 0.0)):
        result = swap2(solve2x2(swapColumns2x2(mat), vec))
    else:
        raise SolveError("[solve2x2] Cannot solve 2x2 matrix equation.")
    return result

def solve3x3(mat, vec):
    """Solve 3x3 matrix equation.
    
    Solve a 3x3 matrix equation with the specified result vector. Returns 
    the solution vector. Raises SolveError if the matrix equation cannot be 
    solved."""
    x11 = mat[0][0]
    x12 = mat[0][1]
    x13 = mat[0][2]
    x21 = mat[1][0]
    x22 = mat[1][1]
    x23 = mat[1][2]
    x31 = mat[2][0]
    x32 = mat[2][1]
    x33 = mat[2][2]
    a = vec[0]
    b = vec[1]
    c = vec[2]
    result = None
    if (x11 != 0.0):
        y11 = (x22 * x11 - x12 * x21) / x11
        y12 = (x23 * x11 - x13 * x21) / x11
        y21 = (x32 * x11 - x12 * x31) / x11
        y22 = (x33 * x11 - x13 * x31) / x11
        d = (b * x11 - a * x21) / x11
        e = (c * x11 - a * x31) / x11
        r0 = solve2x2([[y11, y12], [y21, y22]], [d, e])
        x = (a - r0[0] * x12 - r0[1] * x13) / x11
        result = [x, r0[0], r0[1]]
    elif (x12 != 0.0):
        p = [1, 0, 2]
        result = permute3(solve3x3(permuteColumns3x3(mat, p), vec), p)
    elif (x13 != 0.0):
        p = [2, 1, 0]
        result = permute3(solve3x3(permuteColumns3x3(mat, p), vec), p)
    else:
        raise SolveError("[solve3x3] Cannot solve 3x3 matrix equation.")
    return result

def invert3x3(mat):
    """Invert a 3x3 matrix.
    
    Returns the inverted matrix. Throws SolveError if the matrix cannot be 
    inverted."""
    x = solve3x3(mat, E_X_3)
    y = solve3x3(mat, E_Y_3)
    z = solve3x3(mat, E_Z_3)
    return [
        [ x[0], y[0], z[0] ],
        [ x[1], y[1], z[1] ],
        [ x[2], y[2], z[2] ]
    ]

def dot3(v0, v1):
    """Calculate dot product of 3D vectors."""
    return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2]

def norm3(v):
    """Calculate the norm of a 3D vector."""
    return math.sqrt(dot3(v, v))

def cross3(v0, v1):
    """Calculate the cross product of two 3D vectors."""
    return [
        v0[1] * v1[2] - v0[2] * v1[1],
        v0[2] * v1[0] - v0[0] * v1[2],
        v0[0] * v1[1] - v0[1] * v1[0]
    ]

def project3(v0, v1):
    """Calculate projection of v1 on v0 (3D)."""
    return mult3(1. / dot3(v0, v0), mult3(dot3(v0, v1), v0))

def ortho3(v0, v1):
    """Orthogonalize vector.
    
    Rotates v1 within the plane defined by v0, v1, so it is orthogonal 
    to v0."""
    return mult3(norm3(v1), normalize3(sub3(v1, project3(v0, v1))))

def transform3(mat, vec):
    """Transform a 3D vector by a 3x3 matrix."""
    return [
        dot3(mat[0], vec),
        dot3(mat[1], vec),
        dot3(mat[2], vec)
    ]

def permute3(vec, p):
    """Permute 3D vector."""
    return [vec[p[0]], vec[p[1]], vec[p[2]]]

def transpose3x3(mat):
    """Transpose 3x3 matrix."""
    return [
        [ mat[0][0], mat[1][0], mat[2][0] ],
        [ mat[0][1], mat[1][1], mat[2][1] ],
        [ mat[0][2], mat[1][2], mat[2][2] ]
    ]

def add3(v0, v1):
    """Add two 3D vectors."""
    return [ v0[0] + v1[0], v0[1] + v1[1], v0[2] + v1[2] ]

def sub3(v0, v1):
    """Subtract two 3D vectors."""
    return [ v0[0] - v1[0], v0[1] - v1[1], v0[2] - v1[2] ]

def mult3(c, v):
    """Multiply 3D vector by a scalar."""
    return [ c * v[0], c * v[1], c * v[2] ]

def flip3(v):
    """Flip 3D vector around origin."""
    return mult3(-1., v)

def normalize3(v):
    """Normalize a 3D vector."""
    return mult3(1. / norm3(v), v)

def mult3x3(m0, m2):
    """Multiply 3x3 matrices."""
    m2t = transpose3x3(m2)
    return transpose3x3([
        transform3(m0, m2t[0]),
        transform3(m0, m2t[1]),
        transform3(m0, m2t[2])
    ])

def lt(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison (with tolerance): less than."""
    if (v0 < (v1 - t)):
        return True
    return False

def gt(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison (with tolerance): greater than."""
    if (v0 > (v1 + t)):
        return True
    return False

def eq(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison (with tolerance): equal."""
    if (not (gt(v0, v1, t) or lt(v0, v1, t))):
        return True
    return False

def ltOrEq(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison (with tolerance): less than or equal."""
    if (not gt(v0, v1, t)):
        return True
    return False

def gtOrEq(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison (with tolerance): greater than or equal."""
    if (not lt(v0, v1, t)):
        return True
    return False

def eq2(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison (with tolerance): equal (2D)."""
    for i in range(0, 2):
        if (not eq(v0[i], v1[i], t)):
            return False
    return True

def eq3(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison (with tolerance): equal (3D)."""
    for i in range(0, 3):
        if (not eq(v0[i], v1[i], t)):
            return False
    return True

def addN(v0, v1):
    """Add two vectors."""
    result = []
    for i in range(0, len(v0)):
        result += [ v0[i] + v1[i] ]
    return result

def subN(v0, v1):
    """Subtract two vectors."""
    result = []
    for i in range(0, len(v0)):
        result += [ v0[i] - v1[i] ]
    return result

def multN(c, v):
    """Multiply 3D vector by a scalar."""
    result = []
    for i in range(0, len(v0)):
        result += [ c * v[i] ]
    return result

def flipN(v):
    """Flip 3D vector around origin."""
    return multN(-1., v)

class Vertex2:
    """Vertex (2D).
    
    x  -- X coordinate.
    y  -- Y coordinate."""
    
    def __init__(self, x = 0.0, y = 0.0):
        self.x = x
        self.y = y
    
    def __str__(self):
        return "Vertex2[" + str(self.x) + ", " + str(self.y) + "]"
    
    def __repr__(self):
        return "Vertex2(" + str(self.x) + ", " + str(self.y) + ")"
    
    def getVector(self):
        """Get vector representation."""
        return [ self.x, self.y ]
    
    @classmethod
    def createFromSeq(cls, l):
        """Create a vertex from a sequence of coordinates."""
        return cls(l[0], l[1])

class Intersection2:
    """Intersection (2D).
    
    The result of an intersection in two dimensions. The result attribute will 
    either be None or a result vector. The incidence flag will be True if the 
    intersection test revealed both objects to be incident.
    
    result    -- Intersection result.
    incident  -- Incidence flag."""
    
    def __init__(self, result = None, incident = False):
        self.result = result
        self.incident = incident
    
    def __str__(self):
        return ("Intersection2D[" + str(self.result) + ", " 
            + str(self.incident) + "]")
    
    def __repr__(self):
        return ("Intersection2D(" + repr(self.result) + ", " 
            + repr(self.incident) + "]")

class Line2:
    """Line (2D).
    
    A line in the two dimensional plane.
    
    p  -- Position vector.
    u  -- Direction vector."""
    
    def __init__(self, p = None, u = None):
        if (not p is None):
            self.p = p
        else:
            self.p = [0., 0.]
        if (not u is None):
            self.u = u
        else:
            self.u = [1., 0.]
    
    def intersectLine(self, other, t = DEFAULT_TOLERANCE):
        """Intersect line.
        
        Returns an Intersection2 object describing the intersection result."""
        # Incidence check.
        if ((eq(self.u[0], 0., t) and eq(other.u[0], 0., t))
            or (eq(self.u[0] * other.u[1] - self.u[1] * other.u[2], 0., t))):
            return Intersection2(None, True)
        try:
            r = solve2x2(transpose2x2(self.u, flip2(other.u)), sub2(other.p,
                self.p))
        except SolveError:
            return Intersection2()
        return Intersection2(add2(mult2(r[0], self.u), self.p))
    
    def intersectEdge(self, v0, v1, t = DEFAULT_TOLERANCE):
        """Intersect edge.
        
        Find the intersection of the line and the edge defined by the two 
        vertices. Returns an Intersection2 object describing the intersection 
        result."""
        vv0 = v0.getVector()
        vv1 = v1.getVector()
        other = Line2(vv0, sub2(vv1, vv0))
        ir = self.intersectLine(other)
        if ((ir.result is None) or ir.inicident):
            # The simple case.
            return ir
        ip = ir.result
        if (eq2(vv0, ip, t)):
            # Intersection at v0.
            return Intersection2(vv0)
        if (eq2(vv1, ip, t)):
            # Intersection at v1.
            return Intersection2(vv1)
        if (not (lt(ip[0], min(v0.x, v1.x)) or gt(ip[0], max(v0.x, v1.x))
            or lt(ip[1], min(v0.y, v1.y)) or gt(ip[1], max(v0.y, v1.y)))):
            # Intersection is within edge range.
            return ip
        return Intersection2()
    
    def __str__(self):
        return "Line3[" + str(self.p) + ", " + str(self.u) + "]"
    
    def __repr__(self):
        return "Line3(" + repr(self.p) + ", " + repr(self.u) + ")"

class Polygon2:
    """Polygon (2D).
    
    A Polygon in the two-dimensional plane.
    
    vertices  -- Vertices (list of Vertex2).
    edges     -- Edges (list of vertex index pairs)."""
    
    def __init__(self, vertices = None, edges = None):
        if (not vertices is None):
            self.vertices = vertices
        else:
            self.vertices = []
        if (not edges is None):
            self.edges = edges
        else:
            self.edges = []
    
    def createEdges(self):
        """Create edges from vertex list.
        
        Takes two subsequent vertices from the list to create edges. Returns 
        the number of edges created."""
        self.edges = []
        if (len(self.vertices) < 2):
            return 0
        for i in range(1, len(self.vertices)):
            self.edges += [[i - 1, i]]
        if (len(self.vertices) >= 3):
            # Close the polygon.
            self.edges += [[len(self.vertices) - 1, 0]]
        return len(self.edges)
    
    def checkVertex(self, v, t = DEFAULT_TOLERANCE):
        """Check whether a vertex is inside the polygon."""
        # TODO: Test again, make this robust!
        intersections = 0
        for e in self.edges:
            a = self.vertices[e[0]]
            b = self.vertices[e[1]]
            vt = Vertex2(v.x, v.y)
            #if (debug):
            #    # <---- DEBUG -----
            #    print ("[Polygon2.checkVertex] DEBUG: v = " + str(v) + ", a = " 
            #      + str(a) + ", b = " + str(b))
            #    # ----- DEBUG ---->
            if (eqVertex2(vt, a, t) or eqVertex2(vt, b, t)):
                ## <---- DEBUG -----
                #if (debug):
                #    print ("[Polygon2.checkVertex] DEBUG: "
                #        "Test vertex incident to poly vertex.")
                ## ----- DEBUG ---->
                return True
            if (eq(vt.y, a.y, t) and eq(vt.y, b.y, t)):
                # Horizontal edge.
                #if (debug):
                #    # <---- DEBUG -----
                #    print "[Polygon2.checkVertex] DEBUG: Horizontal edge."
                #    # ----- DEBUG ---->
                if (gtOrEq(vt.x, min(a.x, b.x), t) 
                    and ltOrEq(vt.x, max(a.x, b.x), t)):
                    # Vertex lies on horizontal edge.
                    #if (debug):
                    #    # <---- DEBUG -----
                    #    print "[Polygon2.checkVertex] DEBUG: Vertex on horizontal edge."
                    #    # ----- DEBUG ---->
                    return True
                #elif (debug):
                #    # <---- DEBUG -----
                #    print "[Polygon2.checkVertex] DEBUG: Vertex not on horizontal edge."
                #    # ----- DEBUG ---->
            else:
                # Check intersection.
                # Rather ugly: Offset the point so it will not have the same 
                # y-coordinate as any polygon vertex as this situation makes 
                # correct intersection counts difficult.
                if (eq(vt.y, a.y, t)):
                    vt.y -= 1.1 * t
                if (eq(vt.y, b.y, t)):
                    vt.y -= 1.1 * t
                if (not ((gt(vt.x, a.x, t) and gt(vt.x, b.x, t))
                    or (lt(vt.y, a.y, t) and lt(vt.y, b.y, t))
                    or (gt(vt.y, a.y, t) and gt(vt.y, b.y, t)))):
                    # Find intersection in vertex space.
                    r = solve2x2([[ b.x - a.x, -1. ], [ b.y - a.y, 0.]], 
                        [ vt.x - a.x, vt.y - a.y ])
                    iv = Vertex2(r[1], 0.)
                    ## <---- DEBUG -----
                    #if (debug):
                    #    print ("[Polygon2.checkVertex] DEBUG: intersection: iv = " 
                    #        + str(iv))
                    ## ----- DEBUG ---->
                    if (eq(iv.x, 0., t) and eq(iv.y, 0., t)):
                        # Vertex lies on an edge of the poly.
                        ## <---- DEBUG -----
                        #if (debug):
                        #    print "[Polygon2.checkVertex] DEBUG: Vertex on edge."
                        ## ----- DEBUG ---->
                        return True
                    elif (gt(iv.x, 0., t)):
                        intersections += 1
        ## <---- DEBUG -----
        #if (debug):
        #    print ("[Polygon2.checkVertex] DEBUG: Intersections: " 
        #        + str(intersections))
        ## ----- DEBUG ---->
        if ((intersections % 2) == 0):
            return False
        return True
    
    def interpolate(self, v, data, t = DEFAULT_TOLERANCE):
        """Interpolate data.
        
        v     -- Vertex for which data should be interpolated.
        data  -- List of data, one item per vertex. Each item is a list of 
                 vectors of arbitrary size which describe data points at the 
                 vertex.
        t     -- Tolerance for intersection tests.
        
        Interpolate data across the polygon at the specified vertex. Returns 
        a list of interpolated data points. Raises InterpolationError if the 
        interpolation fails for some reason."""
        it = []
        for e in self.edges:
            a = self.vertices[e[0]]
            b = self.vertices[e[1]]
            if (eqVertex2(v, a, t)):
                # Vertex is equal to edge vertex A.
                return data[e[0]]
            elif (eqVertex2(v, b, t)):
                # Vertex is equal to edge vertex B.
                return data[e[1]]
            elif (eq(v.y, a.y, t) and eq(v.y, b.y, t)):
                # Horizontal edge.
                if (gtOrEq(v.x, min(a.x, b.x), t) 
                    and ltOrEq(v.x, max(a.x, b.x), t)):
                    # Vertex lies on horizontal edge.
                    return interpolateLinear2(a.getVector(), b.getVector(), 
                        data[e[0]], data[e[1]], v.getVector())
            elif (not ((gt(v.x, a.x, t) and gt(v.x, b.x, t))
                or (lt(v.y, a.y, t) and lt(v.y, b.y, t))
                or (gt(v.y, a.y, t) and gt(v.y, b.y, t)))):
                # Find intersection.
                r = solve2x2([[ b.x - a.x, -1. ], [ b.y - a.y, 0.]], 
                    [ v.x - a.x, v.y - a.y ])
                ip = add3(v, [r[1], 0., 0.])
                it += [[e[0], e[1], ip]]
                if (len(it) == 2):
                    break
        if (len(it) != 2):
            raise InterpolationError("Exactly two edge intersections are "
                "required for polygon interpolation.")
        # Interpolation for first edge.
        r0 = self.vertices[it[0][0]].getVector()
        r1 = self.vertices[it[0][1]].getVector()
        d0 = data[it[0][0]]
        d1 = data[it[0][1]]
        v0 = self.vertices[it[0][2]].getVector()
        d3 = interpolateLinear2(r0, r1, d0, d1, v0)
        # Interpolation for second edge.
        r2 = self.vertices[it[1][0]].getVector()
        r3 = self.vertices[it[1][1]].getVector()
        d2 = data[it[1][0]]
        d3 = data[it[1][1]]
        v1 = self.vertices[it[1][2]].getVector()
        d4 = interpolateLinear2(r2, r3, d2, d3, v1)
        return interpolateLinear2(v0, v1, d3, d4, v)
    
    def render(self, renderFunc, uvStep = [ 1., 1. ], data = None, 
        userData = None, t = DEFAULT_TOLERANCE):
        """Render polygon.
        
        renderFunc  -- Callback function which is invoked at each UV 
                       coordinate step.
        uvStep      -- List of two coordinates specifying the UV coordinate 
                       step size.
        data        -- Data to be interpolated.
        userData    -- Constant user data which will be passed to renderFunc.
        t           -- Tolerance used for interscetion tests.
        
        Renders the polygon by calling renderFunc with the current UV 
        coordinates, the interpolated data (if available) and the constant 
        userData. Returns True if the rendering succeeds. Raises RenderError 
        if the rendering fails for some reason."""
        if ((not data is None)
            and (len(data) != len(self.vertices))):
            raise RenderError("Data must be either None or have the same "
                "length as the number of vertices of the polygon.")
        # Determine range of v coordinate.
        vRange = Range()
        vRange.rMin = self.vertices[0].y
        vRange.rMax = self.vertices[0].y
        for tv in self.vertices:
            vRange.extend(tv.y)
        v = vRange.rMin
        uRange = Range()
        while (v <= vRange.rMax):
            # Determine the two source vertices and data points for 
            # interpolation at the current v coordinate. We do this by finding 
            # intersections between a horizontal line and the edges of the 
            # polygon.
            vl = Line2([0., v], [1., 0.])
            v0 = None
            v1 = None
            d0 = None
            d1 = None
            for e in self.edges:
                a = self.vertices[e[0]]
                b = self.vertices[e[1]]
                ir = vl.intersectEdge(a, b, t)
                if (ir.incident):
                    # Horizontal edge.
                    # Just use the vertices of the edge as the interpolation 
                    # sources.
                    v0 = a.getVector()
                    v1 = b.getVector()
                    if (not data is None):
                        d0 = data[e[0]]
                        d1 = data[e[1]]
                    break
                elif (not ir.result is None):
                    # Edge intersection.
                    # Find the source data points by interpolation along the 
                    # current edge.
                    if (v0 is None):
                        # First vertex.
                        v0 = ir.result
                        if (not data is None):
                            d0 = interpolateLinear2(
                                a.getVector(), b.getVector(), 
                                data[e[0]], data[e[1]], ir.result)
                    elif (v1 is None):
                        # Second vertex.
                        v1 = ir.result
                        if (not data is None):
                            d1 = interpolateLinear2(
                                a.getVector(), b.getVector(), 
                                data[e[0]], data[e[1]], ir.result)
                    else:
                        # We already have a second vertex but here is another 
                        # one. This vertex is preferred if it is different 
                        # from the first.
                        if (not eq2(v0, ir.result)):
                            v1 = ir.result
                            if (not data is None):
                                d1 = interpolateLinear2(
                                    a.getVector(), b.getVector(), 
                                    data[e[0]], data[e[1]], ir.result)
            # Now we have two vertices for interpolation.
            if (v0 is None):
                # No intersection. This should not happen, since we are 
                # within the valid v range for the polygon which has been 
                # determined before.
                raise RenderError("Test line does not intersect polygon "
                    "(v = " + str(v) + ").")
            if (v1 is None):
                # This should not happen either. Even if just one vertex has 
                # been intersected at the current v, it should have occured 
                # for two of the edges.
                raise RenderError("Only one intersection has been found "
                    "(v = " + str(v) + ").")
            if (v0[0] >  v1[0]):
                # Put vertices and data in the right u order.
                vt = v0
                v0 = v1
                v1 = vt
                dt = d0
                d0 = d1
                d1 = d0
            uRange.rMin = v0[0]
            uRange.rMax = v1[0]
            u = uRange.rMin
            while (u <= uRange.rMax):
                d = interpolateLinear2(v0, v1, d0, d1, [u, v])
                renderFunc([u, v], d, userData)
                u += uvStep[0]
            v += uvStep[1]
        return True
    
    def __str__(self):
        return "Polygon2[" + str(self.vertices) + ", " + str(self.edges) + "]"
    
    def __repr__(self):
        return "Polygon2(" + repr(self.vertices) + ", " + repr(self.edges) + ")"

def eqVertex2(v0, v1, t = DEFAULT_TOLERANCE):
    """Comparison: equal (2D vertices)."""
    if (eq(v0.x, v1.x, t) and eq(v0.y, v1.y, t)):
        return True
    return False

def interpolateLinear2(r0, r1, d0, d1, v):
    """Linear interpolation (2D).
    
    Return a linear interpolation of the data vectors at the specified vertex. 
    Weights are calculated according to the distance of the vertex to each of 
    the reference points."""
    if ((d0 is None) or (d1 is None)):
        return None
    w0 = norm2(sub2(r0, v))
    w1 = norm2(sub2(r1, v))
    if ((w0 == 0.) and (w1 == 0.)):
        w0 = .5
        w1 = .5
    result = []
    for i in range(0, len(d0)):
        result += [ addN(multN(1. - w0 / (w0 + w1), d0), 
            multN(1. - w1 / (w0 + w1), d1)) ]
    return result

def interpolateLinear3(r0, r1, d0, d1, v):
    """Linear interpolation (3D).
    
    Return a linear interpolation of the data vectors at the specified vertex. 
    Weights are calculated according to the distance of the vertex to each of 
    the reference points."""
    if ((d0 is None) or (d1 is None)):
        return None
    w0 = norm3(sub3(r0, v))
    w1 = norm3(sub3(r1, v))
    if ((w0 == 0.) and (w1 == 0.)):
        w0 = .5
        w1 = .5
    result = []
    for i in range(0, len(d0)):
        result += [ addN(multN(1. - w0 / (w0 + w1), d0), 
            multN(1. - w1 / (w0 + w1), d1)) ]
    return result

class Vertex3:
    """Vertex (3D).
    
    A vertex in 3D space.
    
    x  -- X coordinate.
    y  -- Y coordinate.
    z  -- Z coordinate."""
    
    def __init__(self, x = 0.0, y = 0.0, z = 0.0):
        self.x = x
        self.y = y
        self.z = z
    
    def transform(self, mat):
        """Transform vertex using the specified 3x3 matrix.
        
        Returns a new, transformed vertex."""
        r = transform3(mat, [self.x, self.y, self.z])
        return Vertex3(r[0], r[1], r[2])
    
    def getVector(self):
        """Return a vector corresponding to the vertex location."""
        return [ self.x, self.y, self.z ]
    
    def distanceToPlane(self, plane):
        """Calculate distance to plane."""
        return dot3(self.getVector(), plane.getNormal())
    
    def __str__(self):
        return ("Vertex3[" + str(self.x) + ", " + str(self.y) + ", " 
            + str(self.z) + "]")
    
    def __repr__(self):
        return ("Vertex3(" + str(self.x) + ", " + str(self.y) + ", " 
            + str(self.z) + ")")
    
    @classmethod
    def createFromSeq(cls, l):
        """Create a vertex from a sequence of coordinates."""
        return cls(l[0], l[1], l[2])

class Polygon3(Polygon2):
    """Polygon (3D).
    
    A polygon in 3D space."""
    
    def __init__(self, vertices = None, edges = None):
        Polygon2.__init__(self, vertices, edges)
    
    def transform(self, mat):
        """Transform vertices using the specified 3x3 matrix.
        
        Returns a new, transformed polygon. The polygon will be translated so 
        its origin (the first vertex) is at the center of the coordinate system 
        before the transformation is applied."""
        origin = self.vertices[0].getVector()
        nv = []
        for v in self.vertices:
            vt = Vertex3.createFromSeq(sub3(v.getVector(), origin))
            nv += [vt.transform(mat)]
        return Polygon3(nv, copy.copy(self.edges))
    
    def getPlane(self, vertices = None):
        """Get plane spanned by vertices.
        
        Get the plane spanned by the specified three vertex indices. If the 
        vertices parameter is not specified, the first two and the last 
        vertices are used."""
        if (not vertices is None):
            a = self.vertices[vertices[0]].getVector()
            b = self.vertices[vertices[1]].getVector()
            c = self.vertices[vertices[2]].getVector()
        else:
            a = self.vertices[0].getVector()
            b = self.vertices[1].getVector()
            c = self.vertices[len(self.vertices) - 1].getVector()
        return Plane3(a, sub3(b, a), sub3(c, a))
    
    def getBarycenter(self):
        """Get barycenter.
        
        Returns the barycenter vector for the polygon."""
        vSum = [0., 0., 0.]
        for v in self.vertices:
            vSum = add3(vSum, v.getVector())
        return mult3(1. / len(self.vertices), vSum)
    
    def interpolate(self, v, data, t = DEFAULT_TOLERANCE):
        """Interpolate data.
        
        Interpolate data across the polygon at the specified vertex. This 
        requires the polygon to be planar and the vertex to lie in the plane 
        of the polygon. Returns an interpolated data point. Raises 
        InterpolationError if the interpolation fails for some reason."""
        p = self.getPlane()
        # Transform polygon and intersection point to tangent space.
        tm = p.getTangentBase()
        tmInv = invert3x3(tm)
        # NOTE: The transform() function is expected to translate the polygon 
        # vertices into the origin coordinate system. Otherwise this will not 
        # work as expected.
        tp = self.transform(tmInv)
        # Check planarity.
        for pv in tp.vertices:
            if (not eq(pv.z, 0., t)):
                raise InterpolationError(
                    "Polygon is not planar (pv = " + str(pv) + ").")
        origin = self.vertices[0]
        iv = Vertex3.createFromSeq(sub3(v.getVector(),
            origin.getVector())).transform(tmInv)
        if (not eq(iv.z, 0., t)):
            raise InterpolationError(
                "Vertex is not in polygon plane (iv = " + str(iv) + ").")
        return Polygon2.interpolate(tp, iv, data)
    
    def __str__(self):
        return "Polygon3[" + str(self.vertices) + ", " + str(self.edges) + "]"
    
    def __repr__(self):
        return "Polygon3(" + repr(self.vertices) + ", " + repr(self.edges) + ")"

class Plane3:
    """Plane (3D).
    
    A plane in 3D space.
    
    p  -- Position vector.
    u  -- Direction vector (u).
    v  -- Direction vector (v)."""
    
    def __init__(self, p = None, u = None, v = None):
        if (not p is None):
            self.p = p
        else:
            self.p = [0., 0., 0.]
        if (not u is None):
            self.u = u
        else:
            self.u = [1., 0., 0.]
        if (not v is None):
            self.v = v
        else:
            self.v = [0., 1., 0.]
    
    def getTangent(self):
        """Get tangent vector."""
        return normalize3(self.u)
    
    def getBinormal(self):
        """Get binormal vector."""
        return normalize3(ortho3(self.getTangent(), self.v))
    
    def getNormal(self):
        """Get normal vector."""
        return normalize3(cross3(self.u, self.v))
    
    def getTangentBase(self):
        """Calculate tangent space base matrix.
        
        Calculates the (orthogonal) base matrix of the tangent space for the 
        plane."""
        return transpose3x3([
            self.getTangent(), 
            self.getBinormal(),
            self.getNormal()])
    
    def __str__(self):
        return ("Plane3[" + str(self.p) + ", " + str(self.u) + ", " 
            + str(self.v) + "]")
    
    def __repr__(self):
        return ("Plane3(" + repr(self.p) + ", " + repr(self.u) + ", " 
            + repr(self.v) + ")")
    
    @classmethod
    def createFromNormal(cls, n = [0., 0., 1.], t = [1., 0., 0.], 
        p = [0., 0., 0.]):
        """Create plane from normal vector.
        
        Create a plane from the specified normal vector. If a linearly 
        independent tangent vector is specified as well, that vector will be 
        orthonormalized and then used to construct the binormal vector. If no 
        tangent vector is specified or the tangent vector is not linearly 
        independent, the tangent and binormal will be determined by the 
        implementation."""
        u = copy.copy(t)
        # If n and t are not linearly independent, modify t.
        i = 0
        while ((eq(norm3(cross3(n, u)), 0.))
            and (i < 2)):
            if (i == 0):
                u = copy.copy(E_Y_3)
            elif (i == 1):
                u = copy.copy(E_Z_3)
            i += 1
        u = normalize3(ortho3(n, u))
        v = normalize3(cross3(n, u))
        return Plane3(p, u, v)

class Line3:
    """Line (3D).
    
    A line in 3D space.
    
    p  -- Position vector.
    u  -- Direction vector."""
    
    def __init__(self, p = None, u = None):
        if (not p is None):
            self.p = p
        else:
            self.p = [0., 0., 0.]
        if (not u is None):
            self.u = u
        else:
            self.u = [1., 0., 0.]
    
    def intersectPlane(self, plane):
        """Intersect plane.
        
        Returns the intersection point, or None if no intersection exists."""
        try:
            r = solve3x3(transpose3x3([plane.u, plane.v, flip3(self.u)]), 
                sub3(self.p, plane.p))
        except SolveError:
            return None
        return add3(mult3(r[2], self.u), self.p)
    
    def intersectionInPoly(self, poly, t = DEFAULT_TOLERANCE):
        """Polygon intersection test.
        
        Returns True if the intersection point of the line and the plane 
        defined by the first three vertices of the polygon is within the 
        polygon. Returns False otherwise. Raises IntersectionError if the 
        polygon is not planar."""
        p = poly.getPlane()
        ip = self.intersectPlane(p)
        if (ip is None):
            return False
        # Transform polygon and intersection point to tangent space.
        tm = p.getTangentBase()
        tmInv = invert3x3(tm)
        # NOTE: The transform() function is expected to translate the polygon 
        # vertices into the origin coordinate system. Otherwise this will not 
        # work as expected.
        tp = poly.transform(tmInv)
        # Check planarity.
        for v in tp.vertices:
            if (not eq(v.z, 0., t)):
                raise IntersectionError(
                    "Polygon is not planar (v = " + str(v) + ").")
        origin = poly.vertices[0]
        iv = Vertex3.createFromSeq(sub3(ip,
            origin.getVector())).transform(tmInv)
        ## <---- DEBUG -----
        #if (debug):
        #    print "[Line.intersectionInPoly] DEBUG: Poly: " + str(tp)
        #    print ("[Line.intersectionInPoly] DEBUG: Point: " 
        #        + str(iv.getVector()))
        ## Add and pass drawingArea parameter to use this debugging feature.
        #if (not drawingArea is None):
        #    drawingArea.drawPolygon(tp)
        #    drawingArea.drawPoint(iv.getVector())
        #    return Polygon2.checkVertex(iv, tp, t, True)
        # ----- DEBUG ---->
        return tp.checkVertex(iv, t)
    
    def __str__(self):
        return "Line3[" + str(self.p) + ", " + str(self.u) + "]"
    
    def __repr__(self):
        return "Line3(" + repr(self.p) + ", " + repr(self.u) + ")"

class Sphere3:
    """Sphere (3D).
    
    A Sphere in 3D space.
    
    p  -- Position vector.
    r  -- Radius."""
    
    def __init__(self, p = None, r = 1.):
        if (not p is None):
            self.p = p
        else:
            self.p = [0., 0., 0.]
        self.r = r
    
    def __str__(self):
        return ("Sphere3[" + str(self.p) + ", " + str(self.r) + "]")
    
    def __repr__(self):
        return ("Sphere3(" + repr(self.p) + ", " + repr(self.r) + ")")

RANGE_EQUAL = 0
"""Range comparison result: ranges are equal"""
RANGE_OTHER_CONTAINS = -1
"""Range comparison result: other range contains first range"""
RANGE_FIRST_CONTAINS = 1
"""Range comparison result: first range contains other range"""
RANGE_OVERLAP = 2
"""Range comparison result: ranges overlap"""
RANGE_DISJOINT = 3
"""Range comparison result: ranges are disjoint"""

class Range:
    """Range of values.
    
    rMin  -- Minimum value.
    rMax  -- Maximum value."""
    
    def __init__(self, rMin = 0., rMax = 0.):
        self.rMin = rMin
        self.rMax = rMax
    
    def extend(self, value):
        """Extend range to contain value."""
        if (value < self.rMin):
            self.rMin = value
        if (value > self.rMax):
            self.rMax = value
    
    def getCenter(self):
        """Get center of range."""
        return 0.5 * (self.rMin + self.rMax)
    
    def getRadius(self):
        """Get radius of range."""
        return 0.5 * (self.rMax - self.rMin)
    
    def getValue(self, s):
        """Get range value.
        
        Get the value inside the range corresponding to the parameter s, 
        where s = 0 returns the minimum value and s = 1 returns the maximum 
        value."""
        return self.rMin + s * (self.rMax - self.rMin)
    
    def compare(self, other, t = DEFAULT_TOLERANCE):
        """Compare ranges.
        
        DEPRECATED: This does not cover all possibilities. Use compareX1 
        instead.
        
        Returns 0 if the ranges are equal within the tolerance, i.e. they have 
        the same rMin and rMax values. Returns -1 if the range on which the 
        method is called is contained within the other range, and 1 if the 
        other range is contained within the range on which the method is 
        called. Returns 2 if the ranges overlap."""
        if (eq(self.rMin, other.rMin, t) and eq(self.rMax, other.rMax, t)):
            return 0
        if (ltOrEq(other.rMin, self.rMin) and gtOrEq(other.rMax, self.rMax)):
            return -1
        if (ltOrEq(self.rMin, other.rMin) and gtOrEq(self.rMax, other.rMax)):
            return 1
        return 2
    
    def compareX1(self, other, t = DEFAULT_TOLERANCE):
        """Compare ranges.
        
        New range comparison function which reports all possibilities.
        TODO: Always use this and get rid of compare().
        
        Returns RANGE_EQUAL if the ranges are equal within the tolerance, i.e. 
        they have the same rMin and rMax values. Returns RANGE_OTHER_CONTAINS 
        if the range on which the method is called is contained within the 
        other range, and RANGE_FIRST_CONTAINS if the other range is contained 
        within the range on which the method is called. Returns RANGE_OVERLAP 
        if the ranges overlap. Returns RANGE_DISJOINT if the ranges are 
        disjoint."""
        if (eq(self.rMin, other.rMin, t) and eq(self.rMax, other.rMax, t)):
            return RANGE_EQUAL
        if (lt(self.rMax, other.rMin, t) or gt(self.rMin, other.rMax, t)):
            return RANGE_DISJOINT
        if (ltOrEq(other.rMin, self.rMin, t) 
            and gtOrEq(other.rMax, self.rMax, t)):
            return RANGE_OTHER_CONTAINS
        if (ltOrEq(self.rMin, other.rMin, t) 
            and gtOrEq(self.rMax, other.rMax, t)):
            return RANGE_FIRST_CONTAINS
        return RANGE_OVERLAP
    
    def isInRange(self, v, t = DEFAULT_TOLERANCE):
        """Range check.
        
        Returns True if the value is within the range, False otherwise."""
        if (lt(v, self.rMin, t) or gt(v, self.rMax, t)):
            return False
        return True
    
    def __str__(self):
        return "Range[" + str(self.rMin) + ", " + str(self.rMax) + "]"
    
    def __repr__(self):
        return "Range(" + repr(self.rMin) + ", " + repr(self.rMax) + ")"

class Range3:
    """Range of values (3D).
    
    A range of values in 3D space.
    
    x  -- X range.
    y  -- Y range.
    z  -- Z range."""
    
    def __init__(self, vec = None):
        if (vec is None):
            self.x = Range()
            self.y = Range()
            self.z = Range()
        else:
            self.x = Range(vec[0], vec[0])
            self.y = Range(vec[1], vec[1])
            self.z = Range(vec[2], vec[2])
    
    def extend(self, vec):
        """Extend range to contain values from vector."""
        self.x.extend(vec[0])
        self.y.extend(vec[1])
        self.z.extend(vec[2])
    
    def getCenter(self):
        """Get center of range."""
        return [
            self.x.getCenter(),
            self.y.getCenter(),
            self.z.getCenter()
        ]
    
    def getRadius(self):
        """Get radius vector of range."""
        return [self.x.getRadius(), self.y.getRadius(), self.z.getRadius()]
    
    def getAxisRange(self, axis):
        """Get range for specified axis."""
        if (axis == AXIS_X):
            return self.x
        if (axis == AXIS_Y):
            return self.y
        if (axis == AXIS_Z):
            return self.z
        raise GeoUtilsError("Invalid axis: " + str(axis))
    
    def compare(self, other, t = DEFAULT_TOLERANCE):
        """Compare ranges.
        
        DEPRECATED: This does not cover all possibilities. Use compareX1 
        instead.
        
        Returns 0 if the ranges are equal within the tolerance, i.e. they have 
        the same rMin and rMax values in each dimension. Returns -1 if the 
        range on which the method is called is contained within the other 
        range, and 1 if the other range is contained within the range on which 
        the method is called. Returns 2 if the ranges overlap in some dimension."""
        xc = self.x.compare(other.x, t)
        yc = self.y.compare(other.y, t)
        zc = self.z.compare(other.z, t)
        if ((xc == yc) and (xc == zc)):
            return xc
        c = [ xc, yc, zc ]
        # Check whether the first range contains the other range with equal 
        # ranges in some dimension(s).
        result = True
        for v in c:
            if ((v < 0) or (v == 2)):
                result = False
                break
        if (result):
            return 1
        # Check whether the other range contains the first range with equal 
        # ranges in some dimension(s).
        result = True
        for v in c:
            if ((v > 0) or (v == 2)):
                result = False
                break
        if (result):
            return -1
        return 2
    
    def compareX1(self, other, t = DEFAULT_TOLERANCE):
        """Compare ranges.
        
        New range comparison function which reports all possibilities.
        TODO: Always use this and get rid of compare().
        
        Returns RANGE_EQUAL if the ranges are equal within the tolerance, 
        i.e. they have the same rMin and rMax values in each dimension. 
        Returns RANGE_OTHER_CONTAINS if the range on which the method is 
        called is contained within the other range, and 1 if the other range 
        is contained within the range on which the method is called. Returns 
        RANGE_OVERLAP if the ranges overlap in some dimension. Returns 
        RANGE_DISJOINT if the ranges are disjoint."""
        xc = self.x.compareX1(other.x, t)
        yc = self.y.compareX1(other.y, t)
        zc = self.z.compareX1(other.z, t)
        if ((xc == yc) and (xc == zc)):
            # This covers the equality and disjoint cases.
            return xc
        c = [ xc, yc, zc ]
        # Check whether the first range contains the other range with equal 
        # ranges in some dimension(s).
        result = True
        for v in c:
            if (v == RANGE_DISJOINT):
                # Disjoint on one axis means disjoint ranges.
                return RANGE_DISJOINT
            elif ((v != RANGE_FIRST_CONTAINS) 
                and (v != RANGE_EQUAL)):
                result = False
                break
        if (result):
            return RANGE_FIRST_CONTAINS
        # Check whether the other range contains the first range with equal 
        # ranges in some dimension(s).
        result = True
        for v in c:
            if ((v != RANGE_OTHER_CONTAINS) 
                and (v != RANGE_EQUAL)):
                result = False
                break
        if (result):
            return RANGE_OTHER_CONTAINS
        return RANGE_OVERLAP
    
    def isInRange(self, v, t = DEFAULT_TOLERANCE):
        """Range check.
        
        Returns True if the value is within the range, False otherwise."""
        return (self.x.isInRange(v[0], t) 
            and self.y.isInRange(v[1], t) 
            and self.z.isInRange(v[2], t))
    
    # <---- DEBUG -----
    def compare3(self, other, t = DEFAULT_TOLERANCE):
        """Compare ranges.
        
        Compare ranges and return the individual result for each dimension as 
        a list."""
        xc = self.x.compare(other.x, t)
        yc = self.y.compare(other.y, t)
        zc = self.z.compare(other.z, t)
        return [xc, yc, zc]
    
    @classmethod
    def comparisonToString(cls, c):
        """Convert range comparison result to string."""
        if (c == -1):
            return "contained_in_other"
        if (c == 0):
            return "equal"
        if (c == 1):
            return "contained_in_first"
        if (c == 2):
            return "overlap"
        return "<unknown>"
    
    @classmethod
    def comparisonToString3(cls, c):
        """Convert range comparison result to string (3D)."""
        return (cls.comparisonToString(c[0]) 
            + ", " + cls.comparisonToString(c[1])
            + ", " + cls.comparisonToString(c[2]))
    # ----- DEBUG ---->
    
    def __str__(self):
        return ("Range3[" + str(self.x) + ", " + str(self.y) + ", " 
            + str(self.z) + "]")
    
    def __repr__(self):
        return ("Range3(" + repr(self.x) + ", " + repr(self.y) + ", " 
            + repr(self.z) + ")")

class BoxBoundsItem:
    """An item with box bounds.
    
    This class already supplies much of the bounding box functionality, but 
    does not deal with other items that may be contained inside the bounding 
    box.
    
    center  -- Bounding box center.
    rVec    -- Radius vector of the bounding box (positive x, y, z corner).
    radius  -- Length of radius vector.
    bounds  -- Value range of bounds.
    bVerts  -- Vertices of the bounding box (list of vectors).
    bFaces  -- Faces of the bounding box (list of polygons).
    itemID  -- ID of the item."""
    
    def __init__(self, center = [0., 0., 0.], rVec = [0., 0., 0.], 
        itemID = None):
        self.center = center
        self.rVec = rVec
        self.bVerts = None
        self.bFaces = None
        self.itemID = itemID
        self.updateBounds()
    
    def updateBounds(self):
        """Update bounds.
        
        After changes to the radius vector and center, this method should be 
        called to update the bounds of the object. This will also update the 
        scalar radius value."""
        self.bounds = Range3(self.center)
        self.bounds.extend(add3(self.center, self.rVec))
        self.bounds.extend(sub3(self.center, self.rVec))
        self.radius = norm3(self.rVec)
    
    def updateRadiusAndCenter(self):
        """Update radius and center.
        
        After changes to the bounds of the object, this method should be 
        called to update the radius and center of the object."""
        self.center = self.bounds.getCenter()
        self.rVec = self.bounds.getRadius()
        self.radius = norm3(self.rVec)
    
    def clear(self):
        """Clear item."""
        self.center = [0., 0., 0.]
        self.rVec = [0., 0., 0.]
        self.updateBounds()
    
    def getVertices(self):
        """Get vertices.
        
        Get the vertices of the bounding box in the global coordinate 
        system. Returns a list of vectors."""
        if (not self.bVerts is None):
            return self.bVerts
        tVerts = [
            # Top vertices.
            [ self.rVec[0], self.rVec[1], self.rVec[2] ],
            [ -self.rVec[0], self.rVec[1], self.rVec[2] ],
            [ -self.rVec[0], -self.rVec[1], self.rVec[2] ],
            [ self.rVec[0], -self.rVec[1], self.rVec[2] ],
            # Bottom vertices.
            [ self.rVec[0], self.rVec[1], -self.rVec[2] ],
            [ -self.rVec[0], self.rVec[1], -self.rVec[2] ],
            [ -self.rVec[0], -self.rVec[1], -self.rVec[2] ],
            [ self.rVec[0], -self.rVec[1], -self.rVec[2] ]
        ]
        self.bVerts = []
        for v in tVerts:
            self.bVerts += [ add3(self.center, v) ]
        return self.bVerts
    
    def getFaces(self):
        """Get faces.
        
        Get the faces of the bounding box in the global coordinate system. 
        Returns a list of Polygon3 objects."""
        if (not self.bFaces is None):
            return self.bFaces
        verts = []
        vt = self.getVertices()
        for v in vt:
            verts += [ Vertex3.createFromSeq(v) ]
        self.bFaces = [
            Polygon3([ verts[0], verts[1], verts[2], verts[3] ]),
            Polygon3([ verts[4], verts[7], verts[6], verts[5] ]),
            Polygon3([ verts[0], verts[3], verts[7], verts[4] ]),
            Polygon3([ verts[1], verts[5], verts[6], verts[2] ]),
            Polygon3([ verts[2], verts[6], verts[7], verts[3] ]),
            Polygon3([ verts[0], verts[4], verts[5], verts[1] ])
        ]
        for f in self.bFaces:
            f.createEdges()
        return self.bFaces
    
    def checkPlane(self, plane, t = DEFAULT_TOLERANCE):
        """Check position relative to plane.
        
        Check the bounding box position relative to a plane. Returns 1 if the 
        bounding box is above the plane (in direction of the normal of the 
        plane), 0 if the box intersects the plane, and -1 if the bounding box 
        is below the plane."""
        d = dot3(plane.getNormal(), sub3(self.center, plane.p))
        ## <---- DEBUG -----
        #if (debug):
        #    print ("[BoxBoundsItem.checkPlane] DEBUG: d = " + str(d) 
        #        + ", radius = " + str(self.radius))
        ## ----- DEBUG ---->
        if (gt(d, self.radius, t)):
            return 1
        if (lt(d, -self.radius, t)):
            return -1
        # The bounding box may intersect the plane, we have to check 
        # individual vertices. If all of them are above or below the plane, 
        # so is the bounding box. Otherwise, there is an intersection.
        verts = self.getVertices()
        # Reference value.
        c = 0
        # Current vertex result.
        s = 0
        for v in verts:
            # <---- DEBUG -----
            #print "[BoxBoundsItem.checkPlane] DEBUG: v = " + str(v)
            # ----- DEBUG ---->
            d = dot3(plane.getNormal(), sub3(v, plane.p))
            if (eq(d, 0., t)):
                # Vertex lies on plane.
                return 0
            elif (gt(d, 0., t)):
                # Vertex is above the plane.
                s = 1
            elif (lt(d, 0., t)):
                # Vertex is below the plane.
                s = -1
            if (c == 0):
                # First vertex initializes the reference.
                c = s
            elif (c != s):
                # Some are above, some below.
                return 0
        return c
    
    def checkSphere(self, sphere, t = DEFAULT_TOLERANCE):
        """Check position relative to sphere.
        
        Check the bounding box position relative to a sphere. Returns 1 if the 
        bounding box is inside the sphere, 0 if the box intersects the sphere, 
        and -1 if the bounding box is outside the sphere."""
        d = norm3(sub3(self.center, sphere.p))
        if (gt(d, self.radius + sphere.r, t)):
            return -1
        if (lt(d + self.radius, sphere.r, t)):
            return 1
        return 0
    
    def checkLine(self, line, t = DEFAULT_TOLERANCE):
        """Check line intersection.
        
        Check whether the specified line intersects the bounding box. Returns 
        True if the line intersects the bounding box, False otherwise."""
        faces = self.getFaces()
        for f in faces:
            if (line.intersectionInPoly(f, t)):
                return True
            # <---- DEBUG -----
            #elif (debug):
            #    print ("[BoxBoundsItem.checkLine] No intersection for face: " 
            #        + str(f))
            # ----- DEBUG ---->
        return False
    
    def compare(self, other, t = DEFAULT_TOLERANCE):
        """Compare bounding boxes.
        
        DEPRECATED: This does not cover all possibilities. Use compareX1 
        instead.
        
        Returns 0 if the bounding boxes are equal within the tolerance, i.e. 
        they have the same range in each dimension. Returns -1 if the 
        bounding box on which the method is called is contained within the 
        other bounding box, and 1 if the other bounding box is contained within 
        the bounding box on which the method is called. Returns 2 if the 
        bounding boxes overlap in some dimension."""
        #result = self.bounds.compare(other.bounds, t)
        # <---- DEBUG -----
        #if ((result == 0)
        #    and (not eq3(self.center, other.center)
        #        or not eq3(self.rVec, other.rVec))):
        #    print ("[BoxBoundsItem.compare] DEBUG: "
        #        "Bounding boxes for " + str(self) + ", " + str(other) 
        #        + " are considered equal, but their center and radius "
        #        + "vectors do not match.")
        # ----- DEBUG ---->
        return self.bounds.compare(other.bounds, t)
    
    def compareX1(self, other, t = DEFAULT_TOLERANCE):
        """Compare bounding boxes.
        
        New range comparison function which reports all possibilities.
        TODO: Always use this and get rid of compare().
        
        Returns RANGE_EQUAL if the bounding boxes are equal within the 
        tolerance, i.e. they have the same range in each dimension. Returns 
        RANGE_OTHER_CONTAINS if the bounding box on which the method is called 
        is contained within the other bounding box, and RANGE_FIRST_CONTAINS 
        if the other bounding box is contained within the bounding box on 
        which the method is called. Returns RANGE_OVERLAP if the bounding 
        boxes overlap in some dimension. Returns RANGE_DISJOINT if the 
        bounding boxes are disjoint."""
        #result = self.bounds.compare(other.bounds, t)
        # <---- DEBUG -----
        #if ((result == 0)
        #    and (not eq3(self.center, other.center)
        #        or not eq3(self.rVec, other.rVec))):
        #    print ("[BoxBoundsItem.compare] DEBUG: "
        #        "Bounding boxes for " + str(self) + ", " + str(other) 
        #        + " are considered equal, but their center and radius "
        #        + "vectors do not match.")
        # ----- DEBUG ---->
        return self.bounds.compareX1(other.bounds, t)
    
    # <---- DEBUG -----
    def compare3(self, other, t = DEFAULT_TOLERANCE):
        """Compare ranges.
        
        Compare bounding boxes and return the individual result for each 
        dimension as a list."""
        return self.bounds.compare3(other.bounds, t)
    # ----- DEBUG ---->
    
    def __str__(self):
        return ("BoxBoundsItem[" + str(self.center) + ", " + str(self.rVec) 
            + ", " + str(self.itemID) + "]")
    
    def __repr__(self):
        return ("BoxBoundsItem(" + repr(self.center) + ", " + repr(self.rVec) 
            + ", " + repr(self.itemID) + ")")

class ItemSource:
    """Source for items.
    
    This can be used to restore bounding box hierarchies in which the items 
    have been replaced by dummy items with only IDs."""
    
    def __init__(self):
        pass
    
    def getItem(self, itemID):
        """Return item.
        
        Return the item with the specified ID. Raises ItemSourceError if no 
        valid BoxBoundsItem can be returned."""
        raise ItemSourceError("Not implemented.")

class Split:
    """Axis split.
    
    A split object specifies an axis and a parameter for determining a 
    position on the axis where a split occurs.
    
    axis  -- Split axis.
    s     -- Split parameter (0 <= s <= 1)."""
    
    def __init__(self, axis = AXIS_X, s = 0.5):
        self.axis = axis
        self.s = s
    
    def __repr__(self):
        return "Split(" + repr(self.axis) + ", " + repr(self.s) + ")"
    
    def __str__(self):
        return "Split[" + axisToString(self.axis) + ", " + str(self.s) + "]"
    
    @classmethod
    def createSplits(cls, axis, num = 1):
        """Create splits.
        
        Creates the specified number of splits along the axis. Returns a list 
        of splits."""
        if (num <= 0):
            return []
        step = 1. / (num + 1)
        s = step
        result = []
        while (s < 1.):
            result += [ cls(axis, s) ]
            s += step
        return result

class BoundingBox(BoxBoundsItem):
    """Bounding box.
    
    A bounding box which can contain other BoxBoundsItems.
    
    items   -- Items contained within the bounding box.
    parent  -- Parent bounding box.
    level   -- Level (only used for hierarchical bounding boxes)."""
    
    def __init__(self, center = [0., 0., 0.], rVec = [0., 0., 0.], 
        itemID = None, level = 0, items = None, parent = None):
        if (items is None):
            self.items = set()
        else:
            self.items = items
        self.level = level
        self.parent = parent
        BoxBoundsItem.__init__(self, center, rVec, itemID)
    
    def addItem(self, item, maxRadius = 0.):
        """Add an item to the bounding box.
        
        The dimensions of the bounding box will be updated to reflect the new 
        bounds. If maxRadius is specified, the item will not be added if adding 
        the item would make the radius of the bounding box larger than 
        maxRadius. Returns True if the item has been added, False otherwise."""
        if (len(self.items) == 0):
            self.bounds = copy.deepcopy(item.bounds)
        if (maxRadius > 0):
            b = copy.deepcopy(self.bounds)
            b.extend(add3(item.center, item.rVec))
            b.extend(sub3(item.center, item.rVec))
            if (norm3(b.getRadius()) > maxRadius):
                return False
        self.bounds.extend(add3(item.center, item.rVec))
        self.bounds.extend(sub3(item.center, item.rVec))
        self.items.add(item)
        item.parent = self
        self.updateRadiusAndCenter()
        return True
    
    def removeItem(self, item):
        """Remove an item from the bounding box.
        
        Remove an item from the bounding box. Returns True if the item has 
        been removed, False if the item is not contained in the bounding box."""
        if (not item in self.items):
            return False
        self.items.remove(item)
        self.update()
        return True
    
    def addItems(self, items, maxItems = 0, maxRadius = 0.):
        """Add items to the bounding box.
        
        Add items from the specified set to the bounding box. If maxItems is 
        specified, items will not be added if the number of items in the 
        bounding box would exceed maxItems. If maxRadius is specified, items 
        will not be added if the radius of the bounding box would exceed 
        maxRadius. Returns the set of items that have not been added."""
        remaining = set()
        for it in items:
            # Check for maximum number of items.
            if ((maxItems > 0) 
                and (len(self.items) >= maxItems)):
                remaining.add(it)
            elif (not self.addItem(it, maxRadius)):
                remaining.add(it)
        return remaining
    
    def takeItems(self, items, maxItems = 0, maxRadius = 0.):
        """Add items to the bounding box.
        
        Add items from the specified set to the bounding box. This method 
        removes the items which are added to the bounding box from the source 
        set. If maxItems is specified, items will not be added if the number 
        of items in the bounding box would exceed maxItems. If maxRadius is 
        specified, items will not be added if the radius of the bounding box 
        would exceed maxRadius. Returns the number of items that have been 
        added."""
        numTaken = 0
        putBack = set()
        while (len(items) > 0):
            # Check for maximum number of items.
            if ((maxItems > 0) 
                and (len(self.items) >= maxItems)):
                items.update(putBack)
                return numTaken
            it = items.pop()
            if (self.addItem(it, maxRadius)):
                numTaken += 1
            else:
                putBack.add(it)
        items.update(putBack)
        return numTaken
    
    def splitTest(self, split, t = DEFAULT_TOLERANCE):
        """Test bounding box split.
        
        Split the bounding box along the specified axis, but do not change 
        the actual structure of the bounding box contents. The split parameter 
        s is used to determine the position where the split should occur. 
        If s is 0.5, the split occurs at the center of the axis. If 
        0 < s < 0.5, the split occurs in the lower coordinate half of the 
        axis. If 0.5 > s > 0, the split occurs in the upper coordinate half 
        of the axis. Returns two sets of items."""
        b = self.bounds.getAxisRange(split.axis)
        sc = b.getValue(split.s)
        b0 = set()
        b1 = set()
        for it in self.items:
            if (ltOrEq(it.center[split.axis], sc, t)):
                b0.add(it)
            else:
                b1.add(it)
        return (b0, b1)
    
    def getBestSplit(self, splits, minItems = 0, t = DEFAULT_TOLERANCE):
        """Determine best split.
        
        Tests all of the specified splits and returns the one where the difference between item counts in both sets is minimal. Returns None 
        if none of the splits results in two sets with at least minItems 
        items per set."""
        best = None
        for s in splits:
            sr = self.splitTest(s, t)
            if ((len(sr[0]) >= minItems)
                and (len(sr[1]) >= minItems)):
                # Both sets have enough elements.
                d = abs(len(sr[0]) - len(sr[1]))
                ## <---- DEBUG -----
                #print ("[BoundingBox.getBestSplit] DEBUG: Testing "
                #    + str(s) + ": (" + str(len(sr[0])) + ", " + str(len(sr[1])) 
                #    + ") " + str(d))
                ## ----- DEBUG ---->
                if (best is None):
                    best = (s, d)
                else:
                    if (d < best[1]):
                        best = (s, d)
                    elif (d == best[1]):
                        # Take the split that is more balanced.
                        d0 = abs(best[0].s - 0.5)
                        d1 = abs(s.s - 0.5)
                        ## <---- DEBUG -----
                        #print ("[BoundingBox.getBestSplit] DEBUG: "
                        #    "Testing balance for " + str(s) + ": (" 
                        #    + str(d0) + ", " + str(d1) 
                        #    + ") " + str(d))
                        ## ----- DEBUG ---->
                        if (d1 < d0):
                            best = (s, d)
            #else:
            #    # <---- DEBUG -----
            #    print ("[BoundingBox.getBestSplit] DEBUG: Split "
            #        + str(s) + ": (" + str(len(sr[0])) + ", " + str(len(sr[1])) 
            #        + ") not usable (minItems = " + str(minItems) + ").")
            #    # ----- DEBUG ---->
        if (not best is None):
            ## <---- DEBUG -----
            #print ("[BoundingBox.getBestSplit] DEBUG: Best split: "
            #    + str(best[0]))
            ## ----- DEBUG ---->
            return best[0]
        ## <---- DEBUG -----
        #print ("[BoundingBox.getBestSplit] DEBUG: No suitable split found.")
        ## ----- DEBUG ---->
        return None
    
    def split(self, splits, recursive = False, minItems = 1, maxLevel = 0, 
        t = DEFAULT_TOLERANCE, splitLevel = 0):
        """Split bounding box.
        
        Split the bounding box along the specified axis. The splits argument 
        can be either a single split or a list of splits. If it is a list of 
        splits, the best split will be determinded and used. The split 
        parameter s is used to determine the position where the split should 
        occur. If s is 0.5, the split occurs at the center of the axis. If 
        0 < s < 0.5, the split occurs in the lower coordinate half of the 
        axis. If 0.5 > s > 0, the split occurs in the upper coordinate half 
        of the axis. If recursive is set to True, the contained boxes will be split recursively until the split boxes contain either less than minItems items or maxDepth is reached. Returns two bounding boxes, 
        which are the new items contained in the bounding box. Returns None 
        if the box cannot be split because it does not contain any items, 
        or one of the recursion limits is reached."""
        if (len(self.items) == 0):
            # Nothing to split.
            return None
        if (recursive):
            # Check the abort conditions for recursive splitting.
            if ((minItems > 0) 
                and (len(self.items) <= minItems)):
                return None
            if ((maxLevel > 0)
                and (splitLevel >= maxlevel)):
                return None
        if (isinstance(splits, list)):
            split = self.getBestSplit(splits, minItems, t)
        else:
            split = splits
        if (split is None):
            # There is no split that does anything useful.
            return None
        ## <---- DEBUG -----
        #print ("[BoundingBox.split] DEBUG: Splitting box with " 
        #    + str(len(self.items)) + " items using " + str(split) + ".")
        ## ----- DEBUG ---->
        b = self.bounds.getAxisRange(split.axis)
        sc = b.getValue(split.s)
        b0 = BoundingBox(level = splitLevel + 1)
        b1 = BoundingBox(level = splitLevel + 1)
        for it in self.items:
            if (ltOrEq(it.center[split.axis], sc, t)):
                b0.addItem(it)
            else:
                b1.addItem(it)
        ## <---- DEBUG -----
        #b = None
        #if (self.compare(b0) != 1):
        #    b = b0
        #if (self.compare(b1) != 1):
        #    b = b1
        #if (not b is None):
        #    raise BoundingBoxError("Box not contained before splitting (" 
        #        + str(self.compare(b)) + "): " + str(b) + " (" + str(self) 
        #        + "), [" + Range3.comparisonToString3(
        #            self.bounds.compare3(b.bounds)) + "]")
        ## ----- DEBUG ---->
        if (recursive):
            # Split recursively.
            b0.split(splits, recursive, minItems, maxLevel, t, splitLevel + 1)
            b1.split(splits, recursive, minItems, maxLevel, t, splitLevel + 1)
        ## <---- DEBUG -----
        #b = None
        #if (self.compare(b0) != 1):
        #    b = b0
        #if (self.compare(b1) != 1):
        #    b = b1
        #if (not b is None):
        #    raise BoundingBoxError("Box not contained after splitting (" 
        #        + str(self.compare(b)) + "): " + str(b) + " (" + str(self) 
        #        + "), [" + Range3.comparisonToString3(
        #            self.bounds.compare3(b.bounds)) + "]")
        ## ----- DEBUG ---->
        # Add the new boxes.
        self.clear()
        ## <---- DEBUG -----
        #print ("[BoundingBox.split] DEBUG: Adding box with " 
        #    + str(len(b0.items)) + " items.")
        ## ----- DEBUG ---->
        self.addItem(b0)
        ## <---- DEBUG -----
        #print ("[BoundingBox.split] DEBUG: Adding box with " 
        #    + str(len(b1.items)) + " items.")
        ## ----- DEBUG ---->
        self.addItem(b1)
        return (b0, b1)
    
    def buildHierarchical(self, maxItems = 10, guessMaxRadius = True, 
        fMaxRadius = 0., base = 2.):
        """Build hierarchical bounding boxes.
        
        DEPRECATED: Use split() instead.
        
        Build a hierarchy of bounding boxes containing the items of the 
        bounding box on which the method is called, with the bounding box on 
        which the method is called as the root of the hierarchy. If maxItems 
        is specified, at most maxItems bounding boxes will be contained in 
        each bounding box. If fMaxRadius is specified (as a fraction of the 
        current radius of the bounding box), it will be used for bounding 
        boxes on the deepest level (index 0) and multiplied with base raised 
        to the power of the level index on each level above the deepest. If 
        guessMaxRadius is True (the default), the system will attempt to guess 
        a suitable maximum radius based on the total and maximum number of 
        items."""
        print ("[BoundingBox.buildHierarchical] DEPRECATED: "
            "Use split() instead.")
        if (len(self.items) == 0):
            return
        if (guessMaxRadius):
            # The idea is to assume the items are distributed uniformly 
            # throughout space and we want about maxItems items per neatly 
            # stacked bounding box on the lowest level. Thus we calculate the 
            # radius of the smallest bounding box for this case.
            fMaxRadius = (pow(float(maxItems) / len(self.items), 1. / 3.) 
                * math.sqrt(3.) * 0.5)
            # <---- DEBUG -----
            print ("[BoundingBox.buildHierarchical] DEBUG: "
                "Using fMaxRadius =  " + str(fMaxRadius))
            # ----- DEBUG ---->
        maxRadius = fMaxRadius * self.radius
        current = self.items.copy()
        level = 0
        while (len(current) > 1):
            # Build a set for the next level.
            next = set()
            # <---- DEBUG -----
            numCurrent = len(current)
            print ("[BoundingBox.buildHierarchical] DEBUG: Processing " 
                + str(numCurrent) + " items on level " + str(level) + " ...")
            # ----- DEBUG ---->
            lastDone = 0
            while (len(current) > 0):
                # <---- DEBUG -----
                done = int(float(numCurrent - len(current)) / numCurrent * 100)
                if (done > lastDone):
                    print ("[BoundingBox.buildHierarchical] DEBUG: " 
                        + str(done) + "% done.")
                    lastDone = done
                # ----- DEBUG ---->
                # Process the next item from the current set.
                it = current.pop()
                bb = BoundingBox()
                bb.level = level
                bb.addItem(it)
                # Try to add as many of the other items on the current level 
                # as possible.
                numTaken = bb.takeItems(current, maxItems, maxRadius)
                if ((level > 0) and (numTaken == 0)):
                    # No items could be added. Try again on the next level.
                    it.level += 1
                    next.add(it)
                else:
                    # Move the bounding box to the next level.
                    # <---- DEBUG -----
                    #print ("[BoundingBox.buildHierarchical] DEBUG: "
                    #    + str(numTaken) + " items added to bounding box.")
                    # ----- DEBUG ---->
                    bb.level += 1
                    next.add(bb)
            # Make the next level set the current set.
            current = next
            maxRadius *= base
            level += 1
        # Take items from the highest level bounding box.
        last = current.pop()
        self.clear()
        self.addItems(last.items)
    
    def update(self):
        """Update.
        
        Update all state according to the items contained in the bounding 
        box. If the bounding box has a parent, the parent will also be 
        updated to reflect the changes."""
        if ((self.items is None)
            or (len(self.items) == 0)):
            return
        self.bounds = None
        for it in self.items:
            if (self.bounds is None):
                self.bounds = Range3(it.center)
            self.bounds.extend(add3(it.center, it.rVec))
            self.bounds.extend(sub3(it.center, it.rVec))
        self.updateRadiusAndCenter()
        if (not self.parent is None):
            self.parent.update()
    
    def clear(self):
        """Clear bounding box.
        
        Removes all items and resets state."""
        self.items.clear()
        BoxBoundsItem.clear(self)
        ## This seems to interfere with split().
        #if (not self.parent is None):
        #    self.parent.update()
    
    def getItemsAbovePlane(self, plane, t = DEFAULT_TOLERANCE):
        """Get items above plane.
        
        Get the items which are above the specified plane (in direction of 
        the normal of the plane). Returns two sets of items, the 'surely' and 
        'maybe' sets. The 'surely' set contains items which are surely above 
        the specified plane. These can be leaves or bounding boxes containing 
        other items which are above the plane. The 'maybe' set contains only 
        leaf items with bounding boxes that intersect the plane, so the caller 
        has to determine if the items themselves are above the plane."""
        surely = set()
        maybe = set()
        r = self.checkPlane(plane, t)
        if (r == 1):
            # Everything in this bounding box is above the plane.
            surely.add(self)
            return [surely, maybe]
        elif (r == -1):
            # Nothing in this bounding box is above the plane.
            return [surely, maybe]
        if (len(self.items) == 0):
            raise BoundingBoxError("Bounding box used as a leaf.")
        # There is some intersection, so we need to go into the details.
        for it in self.items:
            r = it.checkPlane(plane, t)
            if (r == 1):
                surely.add(it)
            elif (r == 0):
                if (isinstance(it, BoundingBox)):
                    # If this is a bounding box, check the items contained 
                    # within recursively.
                    ts = it.getItemsAbovePlane(plane, t)
                    surely.update(ts[0])
                    maybe.update(ts[1])
                else:
                    # Leaf item, which is not a bounding box.
                    maybe.add(it)
        return [surely, maybe]
    
    def getItemsOnLine(self, line, t = DEFAULT_TOLERANCE):
        """Get items which intersect line.
        
        Get the leaf items from the bounding box hierarchy which may be 
        intersected by the specified line. Returns a set of leaf items. For 
        leaf items which do not have a checkLine method, it is up to the 
        caller to determine if there are actual intersections."""
        result = set()
        if (not self.checkLine(line, t)):
            # If this bounding box is not intersected, nothing in it will be.
            return result
        if (len(self.items) == 0):
            raise BoundingBoxError("Bounding box used as a leaf.")
        for it in self.items:
            if (it.checkLine(line, t)):
                if (isinstance(it, BoundingBox)):
                    # Bounding box is intersected, check contained items.
                    result.update(it.getItemsOnLine(line, t))
                elif (hasattr(it, 'checkLine')):
                    # Leaf item, which supports checkLine.
                    if (it.checkLine(line, t)):
                        result.add(it)
                else:
                    # Leaf item, which is not a bounding box.
                    result.add(it)
        return result
    
    def getItemsInSphere(self, sphere, t = DEFAULT_TOLERANCE):
        """Get items in sphere.
        
        Get the items which are inside the specified sphere. Returns two sets 
        of items, the 'surely' and 'maybe' sets. The 'surely' set contains 
        items which are surely inside the specified sphere. These can be 
        leaves or bounding boxes containing other items which are inside the 
        sphere. The 'maybe' set contains only leaf items with bounding boxes 
        that intersect the sphere, so the caller has to determine if the 
        items themselves are inside the sphere."""
        surely = set()
        maybe = set()
        r = self.checkSphere(sphere, t)
        ## <---- DEBUG -----
        #print ("[BoundingBox.getItemsInSphere] DEBUG: " + str(self) 
        #    + " (check: " + str(r) + ").")
        ## ----- DEBUG ---->
        if (r == 1):
            # Everything in this bounding box is inside the sphere.
            surely.add(self)
            return [surely, maybe]
        elif (r == -1):
            # Nothing in this bounding box is inside the sphere.
            return [surely, maybe]
        if (len(self.items) == 0):
            raise BoundingBoxError("Bounding box used as a leaf.")
        # There is some intersection, so we need to go into the details.
        for it in self.items:
            r = it.checkSphere(sphere, t)
            if (r == 1):
                surely.add(it)
            elif (r == 0):
                if (isinstance(it, BoundingBox)):
                    # If this is a bounding box, check the items contained 
                    # within recursively.
                    ts = it.getItemsInSphere(sphere, t)
                    surely.update(ts[0])
                    maybe.update(ts[1])
                else:
                    # Leaf item, which is not a bounding box.
                    maybe.add(it)
        return [surely, maybe]
    
    def getItemsInBox(self, box, t = DEFAULT_TOLERANCE):
        """Get items in box.
        
        Get the items which are inside the specified bounding box (which can 
        be simply a BoxBoundsItem). Returns two sets of items, the 'surely' 
        and 'maybe' sets. The 'surely' set contains items which are surely 
        inside the specified bounding box. These can be leaves or bounding 
        boxes containing other items which are inside the bounding box. The 
        'maybe' set contains only leaf items with bounding boxes that 
        intersect the bounding box, so the caller has to determine if the 
        items themselves are inside the box."""
        surely = set()
        maybe = set()
        r = self.compareX1(box, t)
        ## <---- DEBUG -----
        #print ("[BoundingBox.getItemsInBox] DEBUG: " + str(self) 
        #    + " (check: " + str(r) + ").")
        ## ----- DEBUG ---->
        if (r == RANGE_OTHER_CONTAINS):
            # Everything in this bounding box is inside the other box.
            surely.add(self)
            return [surely, maybe]
        elif (r == RANGE_DISJOINT):
            # Nothing in this bounding box is inside the other box.
            return [surely, maybe]
        if (len(self.items) == 0):
            raise BoundingBoxError("Bounding box used as a leaf.")
        # There is some intersection, so we need to go into the details.
        for it in self.items:
            r = it.compareX1(box, t)
            if (r == RANGE_OTHER_CONTAINS):
                surely.add(it)
            elif (r == RANGE_OVERLAP):
                if (isinstance(it, BoundingBox)):
                    # If this is a bounding box, check the items contained 
                    # within recursively.
                    ts = it.getItemsInBox(box, t)
                    surely.update(ts[0])
                    maybe.update(ts[1])
                else:
                    # Leaf item, which is not a bounding box.
                    maybe.add(it)
        return [surely, maybe]
    
    def getContainingLeaf(self, item, t = DEFAULT_TOLERANCE):
        """Get containing leaf.
        
        Return the leaf item that contains the speified item, or None if none 
        of the leaf items contains that item."""
        r = self.compareX1(item, t)
        # <---- DEBUG -----
        print ("[BoundingBox.getContainingLeaf] DEBUG: " + str(self) 
            + " (check: " + str(r) + ").")
        # ----- DEBUG ---->
        if ((r != RANGE_FIRST_CONTAINS)
            and (r != RANGE_EQUAL)):
            # This box does not contain the item.
            return None
        if (len(self.items) == 0):
            # This box contains the item.
            return self
        # Check children.
        for it in self.items:
            r = it.compareX1(item, t)
            if ((r == RANGE_FIRST_CONTAINS)
                or (r == RANGE_EQUAL)):
                # Child box contains the item.
                if (isinstance(it, BoundingBox)):
                    # Check boxes recursively.
                    rb = it.getContainingLeaf(item, t)
                else:
                    # We have found the containing leaf item.
                    rb = it
                if (not rb is None):
                    return rb
        return None
    
    def getGraph(self, level = 0):
        """Get graph of the bounding box hierarchy.
        
        Returns a string containing a human-readable representation of the 
        bounding box hierarchy."""
        prefix = '  ' * level + '+ '
        result = prefix + str(self) + ':\n'
        for it in self.items:
            if (isinstance(it, BoundingBox)):
                result += it.getGraph(level + 1)
            else:
                prefix = '  ' * (level + 1) + '* '
                result += prefix + str(it) + '\n'
        return result
    
    def getBoundingBoxes(self):
        """Get bounding boxes.
        
        Get the bounding boxes from the hierarchy of which the bounding box is 
        the root."""
        boxes = set()
        boxes.add(self)
        for it in self.items:
            if (isinstance(it, BoundingBox)):
                boxes.update(it.getBoundingBoxes())
        return boxes
    
    def getLeaves(self):
        """Get leaves.
        
        Get the leaf items from the hierarchy of which the bounding box is the 
        root."""
        leaves = set()
        for it in self.items:
            if (isinstance(it, BoundingBox)):
                leaves.update(it.getLeaves())
            else:
                leaves.add(it)
        return leaves
    
    def getItemPath(self, item):
        """Get item path.
        
        Get the path for a leaf item in the hierarchy. Returns a list of 
        bounding boxes, from bottom to top, which contain the specified item. 
        Returns an empty list if the item is not contained in the hierarchy."""
        result = []
        for it in self.items:
            if (it == item):
                # We are the bottommost container of the item, no need to 
                # check any other boxes..
                result += [self]
                break
            elif (isinstance(it, BoundingBox)):
                rx = it.getItemPath(item)
                result += rx
                if (len(rx) > 0):
                    result += [self]
                    break
        return result
    
    def getHierarchyRepr(self, boxIndex = 0, itemIndex = 0, level = 0, 
        defaultBoxClassName = 'BoundingBox', 
        rootBoxClassName = 'BoundingBox', addHeader = None):
        """Get representation of hierarchy.
        
        Gets a representation of the hierarchy (as a Python script) which can 
        be used to recreate the hierarchy. Returns a list containing a string 
        for the representation, the current bounding box index, and the 
        current item index."""
        if (level > 0):
            result = ""
        else:
            result = ("#!/usr/bin/python\n"
                "# -*- coding: utf-8 -*-\n\n"
                "from geoutils import *\n")
            if (not addHeader is None):
                result += (addHeader + "\n")
            result += "\n"
        items = []
        for it in self.items:
            if (isinstance(it, BoundingBox)):
                r = it.getHierarchyRepr(boxIndex, itemIndex, level + 1, 
                    defaultBoxClassName, rootBoxClassName, addHeader)
                result += r[0]
                boxIndex = r[1]
                itemIndex = r[2]
                items += [ 'b' + str(boxIndex - 1).rjust(6, '0') ]
            elif(isinstance(it, BoxBoundsItem)):
                result += ('i' + str(itemIndex).rjust(6, '0') + " = " 
                    + BoxBoundsItem.__repr__(it) + '\n')
                items += [ 'i' + str(itemIndex).rjust(6, '0') ]
                itemIndex += 1
        self.level = level
        if (level > 0):
            name = 'b' + str(boxIndex).rjust(6, '0')
            boxClassName = defaultBoxClassName
            boxIndex += 1
        else:
            name = 'rootBox'
            boxClassName = rootBoxClassName
        result += (name + " = " + boxClassName + "(" 
            + repr(self.center) + ', ' + repr(self.rVec) + ', ' 
            + repr(self.itemID) + ', ' + repr(self.level) + ', set([')
        for i in range(0, len(items)):
            it = items[i]
            if (i > 0):
                result += ', '
            result += it
        result += ']))\n'
        return [ result, boxIndex, itemIndex ]
    
    def initFromSource(self, source):
        """Initialize hierarchy from source.
        
        Initialize the bounding box hierarchy from the specified source. This 
        walks through the hierarchy recursively and replaces BoxBoundsItems 
        with whatever is returned from calling the getItem method on the 
        source with the item ID of the BoxBoundsItem as an argument."""
        newItems = set()
        while (len(self.items) > 0):
            it = self.items.pop()
            if (isinstance(it, BoundingBox)):
                it.initFromSource(source)
                newItems.add(it)
            elif (isinstance(it, BoxBoundsItem)):
                newItems.add(source.getItem(it.itemID))
        self.items = newItems
    
    def compareHierarchy(self, other, t = DEFAULT_TOLERANCE):
        """Compare bounding box hierarchies.
        
        Returns True if the hierarchies are equal, i.e. they contain equal 
        bounding boxes and the same leaf items in each node. Returns False if 
        there is some difference."""
        if (self.compare(other, t) != 0):
            # <---- DEBUG -----
            print ("[BoundingBox.compareHierarchy] DEBUG: "
                "Root boxes of the hierarchy are not equal.")
            # ----- DEBUG ---->
            return False
        for it in self.items:
            matching = None
            otherItems = other.items.copy()
            # <---- DEBUG -----
            #print ("[BoundingBox.compareHierarchy] DEBUG: "
            #    "Searching match for " + str(it) + ". Available items:")
            #for oi in otherItems:
            #    print '    ' + str(oi)
            # ----- DEBUG ---->
            # Find a matching item in the other bounding box.
            while((matching is None)
                and (len(otherItems) > 0)):
                oi = otherItems.pop()
                # <---- DEBUG -----
                #print ("[BoundingBox.compareHierarchy] DEBUG: "
                #    "Comparing " + str(it) + " to " 
                #    + str(oi) + ": " + str(it.compare(oi, t))
                #    + " (bounds: " + str(it.bounds) + ", " + str(oi.bounds) 
                #    + ")")
                # ----- DEBUG ---->
                if (it.compare(oi, t) == 0):
                    # If the current item is a leaf item, the matching 
                    # item must be equal. If the current item is a bounding 
                    # box, the matching item must be a bounding box as well.
                    if (not isinstance(it, BoundingBox)):
                        if (it == oi):
                            matching = oi
                    elif (isinstance(oi, BoundingBox)):
                        matching = oi
            if (matching is None):
                # <---- DEBUG -----
                print ("[BoundingBox.compareHierarchy] DEBUG: "
                    "No matching item found for " + str(it) + " [" 
                    + str(id(it)) + "] (comparing " + str(self) + " to " 
                    + str(other) + ").")
                print ("[BoundingBox.compareHierarchy] DEBUG: "
                    "Equality check results:")
                for oi in other.items:
                    print ("[BoundingBox.compareHierarchy] DEBUG: "
                        + str(oi) + " [" + str(id(oi)) + "]: " 
                        + str(it == oi))
                # ----- DEBUG ---->
                return False
            # We have an item with matching bounds, now go into the details.
            if (isinstance(it, BoundingBox)
                and not it.compareHierarchy(matching, t)):
                return False
        # This level is equal for all practical purposes.
        return True
    
    def getItemsAbovePlaneCompare(self, other, plane, t = DEFAULT_TOLERANCE):
        """Get items above plane.
        
        Get the items which are above the specified plane (in direction of 
        the normal of the plane). Returns two sets of items, the 'surely' and 
        'maybe' sets. The 'surely' set contains items which are surely above 
        the specified plane. These can be leaves or bounding boxes containing 
        other items which are above the plane. The 'maybe' set contains only 
        leaf items with bounding boxes that intersect the plane, so the caller 
        has to determine if the items themselves are above the plane.
        
        This method attempts to get the items above the plane synchronously 
        from self and other and aborts with a report if there are any 
        differences."""
        surely = set()
        maybe = set()
        rs = self.checkPlane(plane, t)
        ro = other.checkPlane(plane, t)
        if (rs != ro):
            # <---- DEBUG -----
            raise BoundingBoxError(
                "[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                "Different plane check results for bounding boxes " 
                + str(self) + ", " + str(other) + " (" + str(rs) + ", " 
                + str(ro) + ")")
            # ----- DEBUG ---->
        if (rs == 1):
            # Everything in this bounding box is above the plane.
            if (not self.compareHierarchy(other, t)):
                # <---- DEBUG -----
                raise BoundingBoxError(
                    "[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                    "Plane check result matches, but hierarchies are not "
                    "equal for " + str(self) + ", " + str(other) + " (" 
                    + str(rs) + ", " + str(ro) + ")")
                # ----- DEBUG ---->
            surely.add(self)
            return [surely, maybe]
        elif (rs == -1):
            # Nothing in this bounding box is above the plane.
            if (not self.compareHierarchy(other, t)):
                # <---- DEBUG -----
                raise BoundingBoxError(
                    "[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                    "Plane check result matches, but hierarchies are not "
                    "equal for " + str(self) + ", " + str(other) + " (" 
                    + str(rs) + ", " + str(ro) + ")")
                # ----- DEBUG ---->
            return [surely, maybe]
        if (len(self.items) == 0):
            raise BoundingBoxError("Bounding box used as a leaf.")
        # There is some intersection, so we need to go into the details.
        for it in self.items:
            # Find matching items.
            matching = None
            otherItems = other.items.copy()
            # <---- DEBUG -----
            #print ("[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
            #    "Searching match for " + str(it) + ". Available items:")
            #for oi in otherItems:
            #    print '    ' + str(oi)
            # ----- DEBUG ---->
            # Find a matching item in the other bounding box.
            while((matching is None)
                and (len(otherItems) > 0)):
                oi = otherItems.pop()
                # <---- DEBUG -----
                #print ("[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                #    "Comparing " + str(it) + " to " 
                #    + str(oi) + ": " + str(it.compare(oi, t))
                #    + " (bounds: " + str(it.bounds) + ", " + str(oi.bounds) 
                #    + ")")
                # ----- DEBUG ---->
                if (it.compare(oi, t) == 0):
                    # If the current item is a leaf item, the matching 
                    # item must be equal. If the current item is a bounding 
                    # box, the matching item must be a bounding box as well.
                    if (not isinstance(it, BoundingBox)):
                        if (it == oi):
                            matching = oi
                    elif (isinstance(oi, BoundingBox)):
                        matching = oi
            if (matching is None):
                # <---- DEBUG -----
                raise BoundingBoxError(
                    "[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                    "No matching item found for " + str(it) + " (comparing " 
                    + str(self) + " to " + str(other) + ").")
                # ----- DEBUG ---->
                return False
            rs = it.checkPlane(plane, t)
            ro = matching.checkPlane(plane, t)
            if (rs != ro):
                # <---- DEBUG -----
                print ("[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                    "Plane check for " + str(it) + ":")
                it.checkPlane(plane, t, True)
                print ("[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                    "Plane check for " + str(matching) + ":")
                matching.checkPlane(plane, t, True)
                raise BoundingBoxError(
                    "[BoundingBox.getItemsAbovePlaneCompare] DEBUG: "
                    "Different plane check results for items " + str(it) + ", " 
                    + str(matching) + " (" + str(rs) + ", " + str(ro) + ")")
                # ----- DEBUG ---->
            if (r == 1):
                surely.add(it)
            elif (r == 0):
                if (isinstance(it, BoundingBox)):
                    # If this is a bounding box, check the items contained 
                    # within recursively.
                    ts = it.getItemsAbovePlaneCompare(matching, plane, t)
                    surely.update(ts[0])
                    maybe.update(ts[1])
                else:
                    # Leaf item, which is not a bounding box.
                    maybe.add(it)
        return [surely, maybe]
    
    def validate(self):
        """Validate.
        
        Recursively check that all items are contained within the bounds. 
        Returns True if that is the case. Raises an exception if it is not 
        the case."""
        for it in self.items:
            if (self.compare(it) != 1):
                raise BoundingBoxError("Item not contained within "
                    "bounding box: " + str(it) + " (" + str(self) + ")")
            if (hasattr(it, 'validate')):
                it.validate()
        return True
    
    def __str__(self):
        return ("BoundingBox[" + str(self.center) + ", " + str(self.rVec) 
            + ", " + str(self.level) + "]")
    
    def __repr__(self):
        return ("BoundingBox(" + repr(self.center) + ", " + repr(self.rVec) 
            + ", " + repr(self.level) + ")")

class Vertex(Vertex3):
    """Mesh vertex.
    
    In addition to the vertex coordinates, this vertex class also supports a 
    normal vector.
    
    n  -- Normal vector."""
    
    def __init__(self, x = 0.0, y = 0.0, z = 0.0, n = [1., 0., 0.]):
        Vertex3.__init__(self, x, y, z)
        self.n = n
    
    def __str__(self):
        return ("Vertex[" + str(self.x) + ", " + str(self.y) + ", " 
            + str(self.z) + ", " + str(self.n) + "]")
    
    def __repr__(self):
        return ("Vertex(" + repr(self.x) + ", " + repr(self.y) + ", " 
            + repr(self.z) + ", " + repr(self.n) + ")")

class Face(BoxBoundsItem):
    """Mesh face.
    
    vertexSource  -- List of vertices into which the indices point.
    verts         -- Vertex indices.
    uv            -- Texture coordinates.
    t             -- Tangent vector.
    b             -- Binormal vector.
    n             -- Normal vector."""
    
    def __init__(self, verts = None, uv = None, vertexSource = None):
        BoxBoundsItem.__init__(self)
        self.verts = verts
        self.uv = uv
        self.vertexSource = vertexSource
        self.t = None
        self.n = None
        self.b = None
        self.update()
    
    def update(self):
        """Update.
        
        Update state according to the vertices of the face."""
        if ((self.vertexSource is None)
            or (self.verts is None)
            or (len(self.verts) == 0)):
            return
        self.bounds = Range3(self.vertexSource[self.verts[0]].getVector())
        for vi in self.verts:
            v = self.vertexSource[vi].getVector()
            self.bounds.extend(v)
        self.updateRadiusAndCenter()
    
    def getTangent(self):
        """Get tangent vector."""
        if (not self.t is None):
            return self.t
        if (self.vertexSource is None):
            raise FaceError("Vertex source is not set.")
        if ((self.verts is None) 
            or (len(self.verts) < 3)):
            raise FaceError("Face does not have enough vertices.")
        if ((self.uv is None)
            or (len(self.uv) < 3)):
            raise FaceError("Face does not have enough texture coordinates.")
        pv0 = self.vertexSource[self.verts[0]]
        p0 = pv0.getVector()
        pv1 = self.vertexSource[self.verts[1]]
        p1 = pv1.getVector()
        u0 = self.uv[0][0]
        v0 = self.uv[0][1]
        u1 = self.uv[1][0]
        v1 = self.uv[1][1]
        b = self.getBinormal()
        self.t = mult3(1. / (u1 - u0), sub3(sub3(p1, p0), mult3(v1 - v0, b)))
        return self.t
    
    def getBinormal(self):
        """Get binormal vector."""
        if (not self.b is None):
            return self.b
        if (self.vertexSource is None):
            raise FaceError("Vertex source is not set.")
        if ((self.verts is None) 
            or (len(self.verts) < 3)):
            raise FaceError("Face does not have enough vertices.")
        if ((self.uv is None)
            or (len(self.uv) < 3)):
            raise FaceError("Face does not have enough texture coordinates.")
        pv0 = self.vertexSource[self.verts[0]]
        p0 = pv0.getVector()
        pv1 = self.vertexSource[self.verts[1]]
        p1 = pv1.getVector()
        pv2 = self.vertexSource[self.verts[2]]
        p2 = pv2.getVector()
        u0 = self.uv[0][0]
        v0 = self.uv[0][1]
        u1 = self.uv[1][0]
        v1 = self.uv[1][1]
        u2 = self.uv[2][0]
        v2 = self.uv[2][1]
        # <---- DEBUG -----
        #print ("[Face.getBinormal] DEBUG: p0 = " + str(pv0) + ", p1 = " 
        #    + str(pv1) + ", p2 = " + str(pv2))
        # ----- DEBUG ---->
        self.b = mult3( 1. / ((v2 - v0) * (u1 - u0) - (v1 - v0) * (u2 - u0)),
            sub3(mult3(u1 - u0, sub3(p2, p0)), mult3(u2 - u0, sub3(p1, p0))))
        return self.b
    
    def getNormal(self):
        """Get normal vector."""
        if (not self.n is None):
            return self.n
        t = self.getTangent()
        b = self.getBinormal()
        self.n = normalize3(cross3(t, b))
        return self.n
    
    def getTangentBase(self):
        """Get tangent space base matrix.
        
        Calculates the base matrix of the tangent space for the face."""
        return transpose3x3([
            self.getTangent(), 
            self.getBinormal(),
            self.getNormal()])
    
    def getBarycenter(self):
        """Get barycenter.
        
        Returns the barycenter vector for the face."""
        if (self.vertexSource is None):
            raise FaceError("Vertex source is not set.")
        if ((self.verts is None) 
            or (len(self.verts) < 1)):
            raise FaceError("Face does not have enough vertices.")
        vSum = [0., 0., 0.]
        for vi in self.verts:
            v = self.vertexSource[vi].getVector()
            vSum = add3(vSum, v)
        return mult3(1. / len(self.verts), vSum)
    
    def getPolygon(self):
        """Get polygon.
        
        Returns a polygon corresponding to the face."""
        if (self.vertexSource is None):
            raise FaceError("Vertex source is not set.")
        verts = []
        for vi in self.verts:
            verts += [ self.vertexSource[vi] ]
        p = Polygon3(verts)
        p.createEdges()
        return p
    
    def checkLine(self, line, t = DEFAULT_TOLERANCE):
        """Check line intersection.
        
        Return True if the face intersects the line, False otherwise."""
        return line.intersectionInPoly(self.getPolygon(), t)
    
    def getTris(self):
        """Get triangle faces.
        
        Create triangles for a quad face."""
        if (self.vertexSource is None):
            raise FaceError("Vertex source is not set.")
        if ((self.verts is None) 
            or (len(self.verts) != 4)):
            raise FaceError("Face is not a quad.")
        v0 = [ self.verts[0], self.verts[1], self.verts[2] ]
        v1 = [ self.verts[0], self.verts[2], self.verts[3] ]
        uv0 = None
        uv1 = None
        if ((self.uv != None) 
            and (len(self.uv) == len(self.verts))):
            uv0 = [ self.uv[0], self.uv[1], self.uv[2] ]
            uv1 = [ self.uv[0], self.uv[2], self.uv[3] ]
        return [
            Face(v0, uv0, self.vertexSource),
            Face(v1, uv1, self.vertexSource)
        ]
    
#    def render(self, renderFunc, image, samples = [ 1.0, 1.0 ]):
#        """Render to image.
#        
#        Render the face to an image. This function samples the UV coordinates 
#        of the face and calls renderFunc with the face, the current UV 
#        coordinates and the (interpolated) normal to yield a RGBA color value. 
#        The result is then used to update the image at the current UV 
#        coordinates. The number of samples per pixel and the size of the image 
#        determine the sampling step for the UV coordinates across the face, 
#        according to the equations:
#        
#        UVstepX = 1. / (imageSizeX * samples[0])
#        UVstepY = 1. / (imageSizeY * samples[1])
#        
#        The function currently only supports triangle or quad faces."""
#        if (self.vertexSource is None):
#            raise FaceError("Vertex source is not set.")
#        if ((self.verts is None) 
#            or (len(self.verts) < 3)
#            or (len(self.verts) > 4)):
#            raise FaceError("Face is not a triangle or quad.")
#        if (len(self.verts) == 4):
#            # Convert quad to tris, then render the tris.
#            tFaces = self.getTris()
#            tFaces[0].render(renderFunc, image, samples)
#            tFaces[1].render(renderFunc, image, samples)
#            return True
#        # Render triangle.
#        # Transform into tangent space.
#        p = self.getPolygon()
#        tm = self.getTangentBase()
#        tmInv = invert3x3(tm)
#        pt = self.transform(tmInv)
#        uRange = Range(min(self.uv[0][0], self.uv[1][0], self.uv[2][0]))
#        vRange = Range(min(self.uv[0][0], self.uv[1][0], self.uv[2][0]))
#        
#        uv0 = [ self.uv[0][0], self.uv[0][1], 0. ]
#        uv1 = [ self.uv[1][0], self.uv[1][1], 0. ]
#        uv2 = [ self.uv[2][0], self.uv[2][1], 0. ]
#        duv1 = sub3(uv1, uv0)
#        duv2 = sub3(uv2, uv0)
#        uvStep = 
#        for (
#        
#        vn = [
#            self.vertexSource[self.verts[0]].n,
#            self.vertexSource[self.verts[1]].n,
#            self.vertexSource[self.verts[2]].n
#        ]
#        n = p.interpolate(
    
    def __str__(self):
        return ("Face[" + str(self.verts) + ", " + str(self.uv) + "]")
    
    def __repr__(self):
        return ("Face(" + repr(self.verts) + ", " + repr(self.uv) + ")")

class Mesh(BoxBoundsItem, ItemSource):
    """Mesh.
    
    verts  -- Vertices.
    faces  -- Faces."""
    
    def __init__(self, verts = None, faces = None):
        BoxBoundsItem.__init__(self)
        self.setVertices(verts)
        self.faces = faces
        self.update()
    
    def update(self):
        """Update.
        
        Update state according to the faces of the mesh."""
        if (self.faces is None):
            return
        self.bounds = None
        for f in self.faces:
            if (f.vertexSource is None):
                # If the vertex source is not defined for the face, set it 
                # to the vertices of this mesh.
                f.vertexSource = self.verts
                f.update()
            if (self.bounds is None):
                self.bounds = Range3(f.center)
            self.bounds.extend(add3(f.center, f.rVec))
            self.bounds.extend(sub3(f.center, f.rVec))
        self.updateRadiusAndCenter()
    
    def setFaceIDs(self):
        """Set face IDs.
        
        Set the item IDs of the faces. This is useful for saving and restoring 
        the bounding box hierarchy, if one has been created."""
        i = 0
        for f in self.faces:
            f.itemID = 'face' + str(i).rjust(6, '0')
            i += 1
    
    def setVertices(self, verts):
        """Set vertices.
        
        Sets the vertices for the mesh. They are converted to class Vertex if 
        necessary."""
        self.verts = []
        for v in verts:
            nv = v
            if (not isinstance(v, Vertex)):
                nv = Vertex(v.x, v.y, v.z)
            self.verts += [nv]
    
    def writeToFile(self, fileName, meshName = 'unnamedMesh'):
        """Write mesh to file.
        
        Writes the mesh data to a Python file which can be used to instance 
        the mesh."""
        f = open(fileName, 'w')
        f.write("#!/usr/bin/python\n"
            "# -*- coding: utf-8 -*-\n\n"
            "from geoutils import *\n\n"
            + meshName + "Verts = [\n")
        for i in range(0, len(self.verts)):
            if ((i % 5) == 0):
                f.write('  # ' + str(i).rjust(3, '0') + '\n')
            f.write('    ' + repr(self.verts[i]))
            if (i < (len(self.verts) - 1)):
                f.write(',')
            f.write('\n')
        f.write(']\n\n' + meshName + 'Faces = [\n')
        for i in range(0, len(self.faces)):
            if ((i % 5) == 0):
                f.write('  # ' + str(i).rjust(3, '0') + '\n')
            f.write('    ' + repr(self.faces[i]))
            if (i < (len(self.faces) - 1)):
                f.write(',')
            f.write('\n')
        f.write(']\n\n' + meshName + ' = Mesh(' + meshName + 'Verts, ' 
            + meshName + 'Faces)\n')
        f.close()
    
    def getItem(self, itemID):
        """Return face.
        
        Return the face with the specified ID."""
        if ((len(itemID) < 10)
            or not (itemID[:4] == 'face')):
            raise ItemSourceError("Bad item ID for mesh: '" + str(itemID) 
                + "'")
        fi = int(itemID[4:])
        if (fi >= len(self.faces)):
            raise ItemSourceError("Invalid face index: " + str(fi))
        return self.faces[fi]
    
    def __str__(self):
        return ("Mesh")
    
    def __repr__(self):
        return self.__str__()

