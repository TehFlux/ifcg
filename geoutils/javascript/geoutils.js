/**
 * ==========================================================================
 * Copyright © 2009 Jörn P. Meier
 * All rights reserved.
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * geoutils.js          Geometry utilities.
 * ==========================================================================
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 *  - Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of the copyright holders nor the names of the 
 *    contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * ==========================================================================
 */

// GeoUtils namespace.
var GeoUtils = {
    
    // Default tolerance for comparisons.
    DEFAULT_TOLERANCE: 1.0e-6, 
    
    // Unit vector x (3D).
    E_X_3: [1., 0., 0.], 
    // Unit vector y (3D).
    E_Y_3: [0., 1., 0.], 
    // Unit vector z (3D).
    E_Z_3: [0., 0., 1.], 
    
    // Axis ID: X.
    AXIS_X: 0, 
    // Axis ID: Y.
    AXIS_Y: 1, 
    // Axis ID: Z.
    AXIS_Z: 2, 
    
    // Range comparison result: ranges are equal.
    RANGE_EQUAL: 0, 
    // Range comparison result: other range contains first range.
    RANGE_OTHER_CONTAINS: -1, 
    // Range comparison result: first range contains other range.
    RANGE_FIRST_CONTAINS: 1, 
    // Range comparison result: ranges overlap.
    RANGE_OVERLAP: 2, 
    // Range comparison result: ranges are disjoint.
    RANGE_DISJOINT: 3,
    
    // Length for unique IDs.
    UID_LENGTH: 20,
    
    // Source for unique IDs.
    uidSource: null
};

// Undefined check.
GeoUtils.isUndefined = function(v)
{
    if (typeof(v) == 'undefined')
        return true;
    return false;
}

/**
 * Default argument support.
 *
 * v             -- Value.
 * defaultValue  -- Default value.
 *
 * Returns the default value if the argument is not defined.
 */
GeoUtils.defaultArg = function(v, defaultValue)
{
    if (typeof(v) == 'undefined')
        return defaultValue;
    return v;
}

/**
 * Update hash.
 * 
 * h0  -- Hash to be updated.
 * h1  -- Update source hash.
 * 
 * Updates the hash h0 with entries from hash h1. Returns the updated version 
 * of h0.
 */
GeoUtils.hashUpdate = function(h0, h1)
{
    var h1k = h1.keys();
    for (var i = 0; i < h1k.length; i++)
    {
        var k = h1k[i];
        h0.set(k, h1[k]);
    }
    return h0;
}

/**
 * Pop entry from a hash.
 * 
 * h0  -- Hash.
 * 
 * Removes and returns an entry from a hash. Returns the entry, or null if the 
 * hash is empty.
 */
GeoUtils.hashPop = function(h0)
{
    var keys = h0.keys();
    if (keys.length == 0)
        return null;
    return h0.unset(keys[0]);
}

// Get range comparison result string representation.
GeoUtils.rangeCompToString = function(r)
{
    if (r == GeoUtils.RANGE_EQUAL)
        return "RANGE_EQUAL";
    if (r == GeoUtils.RANGE_OTHER_CONTAINS)
        return "RANGE_OTHER_CONTAINS";
    if (r == GeoUtils.RANGE_FIRST_CONTAINS)
        return "RANGE_FIRST_CONTAINS";
    if (r == GeoUtils.RANGE_OVERLAP)
        return "RANGE_OVERLAP";
    if (r == GeoUtils.RANGE_DISJOINT)
        return "RANGE_DISJOINT";
    return "<unknown>";
}

// Get range comparison result string representation (3D).
GeoUtils.rangeCompToString3 = function(r)
{
    return [
        GeoUtils.rangeCompToString(r[0]), 
        GeoUtils.rangeCompToString(r[1]), 
        GeoUtils.rangeCompToString(r[2])
    ];
}

// Get axis string representation.
GeoUtils.axisToString = function(a)
{
    if (a == GeoUtils.AXIS_X)
        return "AXIS_X";
    if (a == GeoUtils.AXIS_Y)
        return "AXIS_Y";
    if (a == GeoUtils.AXIS_Z)
        return "AXIS_Z";
    return "<unknown>";
}

// Debug output.
GeoUtils.debug = function(msg, source, debugItemClass, debugElementID)
{
    var s0 = GeoUtils.defaultArg(source, null);
    var de0 = GeoUtils.defaultArg(debugElementID, 'debug');
    var dc0 = GeoUtils.defaultArg(debugItemClass, 'guDebugItem');
    var d = $(de0);
    if (d == null)
        return;
    var e = new Element('div', { 'class' : dc0 });
    if (s0 != null)
        e.insert('[' + s0 + '] DEBUG: ' + msg);
    else
        e.insert('DEBUG: ' + msg);
    d.insert(e, { position: 'top' });
}

// Assertion.
GeoUtils.assert = function(msg, source, assertion, assertItemClassOK, 
    assertItemClassFailed, assertElementID)
{
    var s0 = GeoUtils.defaultArg(source, null);
    var ae0 = GeoUtils.defaultArg(assertElementID, 'debug');
    var ac0 = GeoUtils.defaultArg(assertItemClassOK, 'guAssertItemOK');
    var ac1 = GeoUtils.defaultArg(assertItemClassFailed, 'guAssertItemFailed');
    if (assertion)
        GeoUtils.debug(msg + ' (OK)', s0, ac0, ae0);
    else
        GeoUtils.debug(msg + ' (FAILED)', s0, ac1, ae0);
}

// Get string representation for a vector.
GeoUtils.vectorToString = function(v, precision)
{
    var p0 = GeoUtils.defaultArg(precision, GeoUtils.DEFAULT_TOLERANCE);
    var r = '[';
    for (var i = 0; i < v.length; i++)
    {
        if (i > 0)
            r += ', '
        r += (Math.round(v[i] / p0) * p0);
    }
    r += ']';
    return r;
}

// Copy a vector.
GeoUtils.copyVector = function(v)
{
    var v0 = [];
    for (var i = 0; i < v.length; i++)
        v0.push(v[i]);
    return v0;
}

// Copy a matrix.
GeoUtils.copyMatrix = function(mat)
{
    var m0 = [];
    for (var i = 0; i < mat.length; i++)
        m0.push(GeoUtils.copyVector(mat[i]));
    return m0;
}

// Get string representation for a matrix.
GeoUtils.matrixToString = function(mat, precision)
{
    var p0 = GeoUtils.defaultArg(precision, GeoUtils.DEFAULT_TOLERANCE);
    var r = '[';
    for (var i = 0; i < mat.length; i++)
    {
        if (i > 0)
            r += ', '
        r += GeoUtils.vectorToString(mat[i], p0);
    }
    r += ']';
    return r;
}

/**
 * Get random character.
 * 
 * useChars  -- Characters to be used.
 * 
 * Get a random character from the specified range. If no range is specified, 
 * a random alphanumeric character or underscore will be returned.
 */
GeoUtils.randomChar = function(useChars)
{
    var c0 = GeoUtils.defaultArg(useChars, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        + "abcdefghijklmnopqrstuvwxyz_0123456789");
    var i = Math.floor(Math.random() * c0.length);
    return c0.charAt(i);
}

/**
 * Get random string.
 * 
 * l         -- Length.
 * useChars  -- Characters to be used.
 * 
 * Get a random string of the specified length from the specified character 
 * range. If no range is specified, alphanumeric characters and the underscore 
 * will be used.
 */
GeoUtils.randomString = function(l, useChars)
{
    var l0 = GeoUtils.defaultArg(l, 20);
    var c0 = GeoUtils.defaultArg(useChars, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        + "abcdefghijklmnopqrstuvwxyz_0123456789");
    var r = "";
    for (var i = 0; i < l; i++)
        r += GeoUtils.randomChar(c0);
    return r;
}

/**
 * UID source.
 *
 * A source for unique IDs.
 */
GeoUtils.UIDSource = Class.create({
    
    // Constructor.
    initialize: function(uidLength)
    {
        this.uidLength = GeoUtils.defaultArg(uidLength, GeoUtils.UID_LENGTH);
        this.uids = new Hash();
    }, 
    
    getUID: function()
    {
        var uid = GeoUtils.randomString(this.uidLength);
        var maxTries = 100;
        var i = 0;
        while ((this.uids.get(uid) != null)
            && (i < maxTries))
        {
            uid = GeoUtils.randomString(this.uidLength);
            i++;
        }
        if (i >= maxTries)
            throw new Error("[GeoUtils.UIDSource.getUID] " 
                + "Maximum number of attempts to generate a UID exceeded!");
        this.uids.set(uid, true);
        return uid;
    }
    
});

// Get UID from the default source.
GeoUtils.getUID = function()
{
    if (GeoUtils.uidSource == null)
        GeoUtils.uidSource = new GeoUtils.UIDSource();
    return GeoUtils.uidSource.getUID();
}

/**
 * Identifiable object.
 *
 * An object that can be uniquely identified.
 */
GeoUtils.Identifiable = Class.create({
    
    // Constructor.
    initialize: function()
    {
        this.uniqueID = GeoUtils.getUID();
    },
    
    toString: function()
    {
        return "Identifiable[" + this.uniqueID + "]";
    }
});

/**
 * Set.
 *
 * A set of objects. Objects which are added to the set need to have an 
 * uniqueID property that uniquely identifies the object.
 */
GeoUtils.Set = Class.create({
    
    // Constructor.
    initialize: function()
    {
        this.entries = new Hash();
    },
    
    // Add object.
    add: function(obj)
    {
        if (GeoUtils.isUndefined(obj.uniqueID))
            throw Error("[GeoUtils.Set.add] "
                + "Object does not have a unique ID!");
        this.entries.set(obj.uniqueID, obj);
    },
    
    // Remove object.
    remove: function(obj)
    {
        if (GeoUtils.isUndefined(obj.uniqueID))
            throw Error("[GeoUtils.Set.remove] "
                + "Object does not have a unique ID!");
        this.entries.unset(obj.uniqueID);
    },
    
    // Pop object.
    pop: function()
    {
        var keys = this.entries.keys();
        if (keys.length == 0)
            return null;
        return this.entries.unset(keys[0]);
    },
    
    // Check whether the set contains an object.
    contains: function(obj)
    {
        if (GeoUtils.isUndefined(obj.uniqueID))
            throw Error("[GeoUtils.Set.contains] "
                + "Object does not have a unique ID!");
        if (GeoUtils.isUndefined(this.entries.get(obj.uniqueID)))
            return false;
        return true;
    },
    
    // Update set with another set.
    update: function(other)
    {
        var e0 = other.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            this.add(it);
        }
    },
    
    // Get number of entries.
    getNumEntries: function()
    {
        return this.entries.keys().length;
    },
    
    // Get entries.
    getEntries: function()
    {
        return this.entries.values();
    },
    
    // Clear entries.
    clear: function()
    {
        this.entries = new Hash();
    },
    
    toString: function()
    {
        var r = "";
        var keys = this.entries.keys();
        for (var i = 0; i < keys.length; i++)
        {
            var k = keys[i];
            if (i > 0)
                r += ', ';
            var it = this.entries.get(k);
            r += it;
        }
        return "Set[" + r + "]";
    }
});

// Comparison (with tolerance): less than.
GeoUtils.lt = function(v0, v1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    if (v0 < (v1 - t0))
        return true;
    return false;
}

// Comparison (with tolerance): greater than.
GeoUtils.gt = function(v0, v1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    if (v0 > (v1 + t0))
        return true;
    return false;
}

// Comparison (with tolerance): equal.
GeoUtils.eq = function(v0, v1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    if (!(GeoUtils.gt(v0, v1, t0) || GeoUtils.lt(v0, v1, t0)))
        return true;
    return false;
}

// Comparison (with tolerance): less than or equal.
GeoUtils.ltOrEq = function(v0, v1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    if (!GeoUtils.gt(v0, v1, t0))
        return true;
    return false;
}

// Comparison (with tolerance): greater than or equal.
GeoUtils.gtOrEq = function(v0, v1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    if (!GeoUtils.lt(v0, v1, t0))
        return true;
    return false;
}

// Comparison (with tolerance): equal (2D).
GeoUtils.eq2 = function(v0, v1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    for (var i = 0; i < 2; i++)
        if (!GeoUtils.eq(v0[i], v1[i], t0))
            return false;
    return true;
}

// Add two 2D vectors.
GeoUtils.add2 = function(v0, v1)
{
    return [ v0[0] + v1[0], v0[1] + v1[1] ];
}

// Subtract two 2D vectors.
GeoUtils.sub2 = function(v0, v1)
{
    return [ v0[0] - v1[0], v0[1] - v1[1] ];
}

// Multiply 2D vector by a scalar.
GeoUtils.mult2 = function(c, v)
{
    return [ c * v[0], c * v[1] ];
}

// Flip 2D vector around origin.
GeoUtils.flip2 = function(v)
{
    return [ -v[0], -v[1] ];
}

// Swap elements of 2D vector.
GeoUtils.swap2 = function(vec)
{
    return [ vec[1], vec[0] ];
}

// Calculate dot product of 2D vectors.
GeoUtils.dot2 = function(v0, v1)
{
    return v0[0] * v1[0] + v0[1] * v1[1];
}

// Calculate the norm of a 2D vector.
GeoUtils.norm2 = function(v)
{
    return Math.sqrt(GeoUtils.dot2(v, v));
}

// Swap columns of 2x2 matrix.
GeoUtils.swapColumns2x2 = function(mat)
{
    return [ GeoUtils.swap2(mat[0]), GeoUtils.swap2(mat[1]) ];
}

/**
 * Solve 2x2 matrix equation.
 * 
 * Solve a 2x2 matrix equation with the specified result vector. Returns 
 * the solution vector. Throws an exception if the matrix equation cannot be 
 * solved.
 */
GeoUtils.solve2x2 = function(mat, vec)
{
    var y11 = mat[0][0];
    var y12 = mat[0][1];
    var y21 = mat[1][0];
    var y22 = mat[1][1];
    var d = vec[0];
    var e = vec[1];
    var result = null;
    if ((y11 != 0.0)
        && ((y22 * y11 - y12 * y21) != 0.0))
    {
        y = (e * y11 - d * y21) / (y22 * y11 - y12 * y21);
        x = (d - y * y12) / y11;
        result = [x, y];
    } else
    if ((y12 != 0)
        && ((y21 * y12 - y11 * y22) != 0.0))
        result = GeoUtils.swap2(GeoUtils.solve2x2(
            GeoUtils.swapColumns2x2(mat), vec));
    else
        throw new Error("[solve2x2] Cannot solve 2x2 matrix equation.");
    return result;
}

// Comparison (with tolerance): equal (3D).
GeoUtils.eq3 = function(v0, v1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    for (var i = 0; i < 3; i++)
        if (!GeoUtils.eq(v0[i], v1[i], t0))
            return false;
    return true;
}

// Add two 3D vectors.
GeoUtils.add3 = function(v0, v1)
{
    return [ v0[0] + v1[0], v0[1] + v1[1], v0[2] + v1[2] ];
}

// Subtract two 3D vectors.
GeoUtils.sub3 = function(v0, v1)
{
    return [ v0[0] - v1[0], v0[1] - v1[1], v0[2] - v1[2] ];
}

// Multiply 3D vector by a scalar.
GeoUtils.mult3 = function(c, v)
{
    return [ c * v[0], c * v[1], c * v[2] ];
}

// Flip 3D vector around origin.
GeoUtils.flip3 = function(v)
{
    return [ -v[0], -v[1], -v[2] ];
}

// Calculate dot product of 3D vectors.
GeoUtils.dot3 = function(v0, v1)
{
    return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}

// Calculate the norm of 3D vectors.
GeoUtils.norm3 = function(v)
{
    return Math.sqrt(GeoUtils.dot3(v, v));
}

// Calculate the cross product of two 3D vectors.
GeoUtils.cross3 = function(v0, v1)
{
    return [ 
        v0[1] * v1[2] - v0[2] * v1[1],
        v0[2] * v1[0] - v0[0] * v1[2],
        v0[0] * v1[1] - v0[1] * v1[0]
    ];
}

// Calculate projection of v1 on v0 (3D).
GeoUtils.project3 = function(v0, v1)
{
    return GeoUtils.mult3(1. / GeoUtils.dot3(v0, v0), 
        GeoUtils.mult3(GeoUtils.dot3(v0, v1), v0));
}

// Normalize 3D vector.
GeoUtils.normalize3 = function(v)
{
    return GeoUtils.mult3(1. / GeoUtils.norm3(v), v);
}

/**
 * Orthogonalize vector.
 * 
 * Rotates v1 within the plane defined by v0, v1, so it is orthogonal to v0. 
 * Returns the orthogonalized vector.
 */
GeoUtils.ortho3 = function(v0, v1)
{
    return GeoUtils.mult3(GeoUtils.norm3(v1), 
        GeoUtils.normalize3(GeoUtils.sub3(v1, GeoUtils.project3(v0, v1))));
}

/**
 * Transform vector (3D).
 *
 * Transform a vector using the specified 3x3 matrix. Returns the transformed 
 * vector.
 */
GeoUtils.transform3 = function(mat, vec)
{
    return [
        GeoUtils.dot3(mat[0], vec), 
        GeoUtils.dot3(mat[1], vec), 
        GeoUtils.dot3(mat[2], vec)
    ];
}

// Permute 3D vector.
GeoUtils.permute3 = function(vec, p)
{
    return [ vec[p[0]], vec[p[1]], vec[p[2]] ];
}

// Create 3x3 unit matrix.
GeoUtils.unit3x3 = function()
{
    return [
        [ 1., 0., 0. ], 
        [ 0., 1., 0. ], 
        [ 0., 0., 1. ]
    ];
}

// Create a 3x3 scale matrix.
GeoUtils.scale3x3 = function(sx, sy, sz)
{
    var sx0 = GeoUtils.defaultArg(sx, 1.);
    var sy0 = GeoUtils.defaultArg(sy, 1.);
    var sz0 = GeoUtils.defaultArg(sz, 1.);
    var r = GeoUtils.unit3x3();
    r[0][0] = sx0;
    r[1][1] = sy0;
    r[2][2] = sz0;
    return r;
}

// Create a 3x3 translate matrix.
GeoUtils.translate3x3 = function(tx, ty)
{
    var tx0 = GeoUtils.defaultArg(sx, 0.);
    var ty0 = GeoUtils.defaultArg(sy, 0.);
    var r = GeoUtils.unit3x3();
    r[0][2] = tx0;
    r[1][2] = ty0;
    return r;
}

// Create a 3x3 rotation matrix.
GeoUtils.rotate3x3 = function(phi)
{
    var phi0 = GeoUtils.defaultArg(phi, 0.);
    return [ 
        [ Math.cos(phi0), -Math.sin(phi0), 0. ], 
        [ Math.sin(phi0), Math.cos(phi0), 0. ], 
        [ 0., 0., 1. ]
    ];
}

// Transpose 3x3 matrix.
GeoUtils.transpose3x3 = function(mat)
{
    return [
        [ mat[0][0], mat[1][0], mat[2][0] ], 
        [ mat[0][1], mat[1][1], mat[2][1] ], 
        [ mat[0][2], mat[1][2], mat[2][2] ]
    ];
}

// Permute columns of a 3x3 matrix.
GeoUtils.permuteColumns3x3 = function(mat, p)
{
    return [
        GeoUtils.permute3(mat[0], p), 
        GeoUtils.permute3(mat[1], p), 
        GeoUtils.permute3(mat[2], p)
    ];
}

/**
 * Solve 3x3 matrix equation.
 * 
 * Solve a 3x3 matrix equation with the specified result vector. Returns the 
 * solution vector. Throws an exception if the matrix equation cannot be 
 * solved.
 */
GeoUtils.solve3x3 = function(mat, vec)
{
    var x11 = mat[0][0];
    var x12 = mat[0][1];
    var x13 = mat[0][2];
    var x21 = mat[1][0];
    var x22 = mat[1][1];
    var x23 = mat[1][2];
    var x31 = mat[2][0];
    var x32 = mat[2][1];
    var x33 = mat[2][2];
    var a = vec[0];
    var b = vec[1];
    var c = vec[2];
    var result = null;
    if (x11 != 0.0)
    {
        var y11 = (x22 * x11 - x12 * x21) / x11;
        var y12 = (x23 * x11 - x13 * x21) / x11;
        var y21 = (x32 * x11 - x12 * x31) / x11;
        var y22 = (x33 * x11 - x13 * x31) / x11;
        var d = (b * x11 - a * x21) / x11;
        var e = (c * x11 - a * x31) / x11;
        var r0 = GeoUtils.solve2x2([[y11, y12], [y21, y22]], [d, e]);
        var x = (a - r0[0] * x12 - r0[1] * x13) / x11;
        result = [x, r0[0], r0[1]];
    } else
    if (x12 != 0.0)
    {
        var p = [1, 0, 2];
        result = GeoUtils.permute3(GeoUtils.solve3x3(
            GeoUtils.permuteColumns3x3(mat, p), vec), p);
    } else
    if (x13 != 0.0)
    {
        var p = [2, 1, 0];
        result = GeoUtils.permute3(GeoUtils.solve3x3(
            GeoUtils.permuteColumns3x3(mat, p), vec), p);
    } else
        throw new Error("[solve3x3] Cannot solve 3x3 matrix equation.");
    return result;
}

/**
 * Invert a 3x3 matrix.
 * 
 * Returns the inverted matrix. Throws an exception if the matrix cannot be 
 * inverted.
 */
GeoUtils.invert3x3 = function(mat)
{
    var x = GeoUtils.solve3x3(mat, GeoUtils.E_X_3);
    var y = GeoUtils.solve3x3(mat, GeoUtils.E_Y_3);
    var z = GeoUtils.solve3x3(mat, GeoUtils.E_Z_3);
    return [
        [ x[0], y[0], z[0] ], 
        [ x[1], y[1], z[1] ], 
        [ x[2], y[2], z[2] ]
    ];
}

// Multiply 3x3 matrices.
GeoUtils.mult3x3 = function(m0, m1)
{
    var m1t = GeoUtils.transpose3x3(m1);
    return GeoUtils.transpose3x3([
        GeoUtils.transform3(m0, m1t[0]), 
        GeoUtils.transform3(m0, m1t[1]), 
        GeoUtils.transform3(m0, m1t[2])
    ]);
}

// Matrix comparison (with tolerance): equal.
GeoUtils.matrixEq = function(m0, m1, t)
{
    var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
    if (m0.length != m1.length)
        return false;
    for (var i = 0; i < m0.length; i++)
    {
        var mr0 = m0[i];
        var mr1 = m1[i];
        if (mr0.length != mr1.length)
            return false;
        for (var j = 0; j < mr0.length; j++)
            if (!GeoUtils.eq(mr0[j], mr1[j], t0))
                return false;
    }
    return true;
}

/**
 * Vertex (2D).
 *
 * x  -- X coordinate.
 * y  -- Y coordinate.
 */
GeoUtils.Vertex2 = Class.create({
    
    // Constructor.
    initialize: function(x, y)
    {
        this.x = GeoUtils.defaultArg(x, 0.);
        this.y = GeoUtils.defaultArg(y, 0.);
    }, 
    
    // Comparison: equal (2D vertices).
    eq: function(v, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        if (GeoUtils.eq(this.x, v.x, t0) && GeoUtils.eq(this.y, v.y, t0))
            return true;
        return false;
    },
    
    // Get vector representation.
    getVector: function()
    {
        return [ this.x, this.y ];
    },
    
    toString: function()
    {
        return "Vertex2[" + this.x + ", " + this.y + "]";
    }
});

// Create a vertex from a sequence of coordinates.
GeoUtils.Vertex2.createFromSeq = function(l)
{
    return new GeoUtils.Vertex2(l[0], l[1]);
}

/**
 * Polygon (2D).
 *
 * A polygon in the two-dimensional plane.
 *
 * vertices  -- Vertices (list of Vertex2).
 * edges     -- Edges (list of vertex index pairs).
 */
GeoUtils.Polygon2 = Class.create({
    
    // Constructor.
    initialize: function(vertices, edges)
    {
        this.vertices = GeoUtils.defaultArg(vertices, []);
        this.edges = GeoUtils.defaultArg(edges, []);
    }, 
    
    /**
     * Create edges from vertex list.
     *
     * Takes two subsequent vertices from the list to create edges. 
     * Returns the number of edges created.
     */
    createEdges: function()
    {
        this.edges = [];
        if (this.vertices.length < 2)
            return 0;
        for (var i = 1; i < this.vertices.length; i++)
            this.edges.push([i - 1, i]);
        if (this.vertices.length >= 3)
            // Close the polygon.
            this.edges.push([this.vertices.length - 1, 0]);
        return this.edges.length;
    }, 
    
    /**
     * Check whether a vertex is inside the polygon.
     */
    checkVertex: function(v, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var intersections = 0;
        for (var i = 0; i < this.edges.length; i++)
        {
            var e = this.edges[i];
            var a = this.vertices[e[0]];
            var b = this.vertices[e[1]];
            var vt = new GeoUtils.Vertex2(v.x, v.y);
            // <---- DEBUG ----- //
            GeoUtils.debug("v = " + v + ", a = " + a + ", b = " + b, 
                'Vertex2.checkVertex');
            // ----- DEBUG ----> */
            if (vt.eq(a, t0) || vt.eq(b, t0))
            {
                // <---- DEBUG ----- //
                GeoUtils.debug("Test vertex incident to poly vertex.", 
                    'Vertex2.checkVertex');
                // ----- DEBUG ----> */
                return true;
            }
            if (GeoUtils.eq(vt.y, a.y, t0) && GeoUtils.eq(vt.y, b.y, t0))
            {
                // Horizontal edge.
                // <---- DEBUG ----- //
                GeoUtils.debug("Horizontal edge.", 'Vertex2.checkVertex');
                // ----- DEBUG ----> */
                if (GeoUtils.gtOrEq(vt.x, Math.min(a.x, b.x), t0) 
                    && GeoUtils.ltOrEq(vt.x, Math.max(a.x, b.x), t0))
                {
                    // Vertex lies on horizontal edge.
                    // <---- DEBUG ----- //
                    GeoUtils.debug("Vertex lies on horizontal edge.", 
                        'Vertex2.checkVertex');
                    // ----- DEBUG ----> */
                    return true;
                } else
                {
                    // <---- DEBUG ----- //
                    GeoUtils.debug("Vertex does not lie on horizontal edge.", 
                        'Vertex2.checkVertex');
                    // ----- DEBUG ----> */
                }
            } else
            {
                /* Rather ugly: Offset the point so it will not have the same 
                   coordinate as any polygon vertex as this situation makes 
                   correct intersection counts difficult. */
                if (GeoUtils.eq(vt.y, a.y, t0))
                    vt.y -= 1.1 * t0;
                if (GeoUtils.eq(vt.y, b.y, t0))
                    vt.y -= 1.1 * t0;
                if (!((GeoUtils.gt(vt.x, a.x, t0) 
                        && GeoUtils.gt(vt.x, b.x, t0))
                    || (GeoUtils.lt(vt.y, a.y, t0) 
                        && GeoUtils.lt(vt.y, b.y, t0))
                    || (GeoUtils.gt(vt.y, a.y, t0) 
                        && GeoUtils.gt(vt.y, b.y, t0))))
                {
                    // Find intersection in vertex space.
                    var r = GeoUtils.solve2x2([[ b.x - a.x, -1. ], 
                        [ b.y - a.y, 0.]], [ vt.x - a.x, vt.y - a.y ]);
                    var iv = new GeoUtils.Vertex2(r[1], 0.);
                    // <---- DEBUG ----- //
                    GeoUtils.debug("intersection: iv = " + iv, 
                        'Vertex2.checkVertex');
                    // ----- DEBUG ----> */
                    if (GeoUtils.eq(iv.x, 0., t0) && GeoUtils.eq(iv.y, 0., t0))
                    {
                        // Vertex lies on an edge of the poly.
                        return true;
                    } else
                    if (GeoUtils.gt(iv.x, 0., t0))
                        intersections += 1;
                }
            }
        }
        // <---- DEBUG ----- //
        GeoUtils.debug("intersections = " + intersections, 
            'Vertex2.checkVertex');
        // ----- DEBUG ----> */
        if (intersections % 2 == 0)
            return false;
        return true;
    },
    
    toString: function()
    {
        return "Polygon2[[" + this.vertices + "], [" + this.edges + "]]";
    }
});

/**
 * Vertex (3D).
 *
 * x  -- X coordinate.
 * y  -- Y coordinate.
 * z  -- Z coordinate.
 */
GeoUtils.Vertex3 = Class.create({
    
    // Constructor.
    initialize: function(x, y, z)
    {
        this.x = GeoUtils.defaultArg(x, 0.);
        this.y = GeoUtils.defaultArg(y, 0.);
        this.z = GeoUtils.defaultArg(z, 0.);
    },
    
    // Comparison: equal (2D vertices).
    eq: function(v, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        if (GeoUtils.eq(this.x, v.x, t0) 
            && GeoUtils.eq(this.y, v.y, t0)
            && GeoUtils.eq(this.z, v.z, t0))
            return true;
        return false;
    },
    
    // Get vector representation.
    getVector: function()
    {
        return [ this.x, this.y, this.z ];
    },
    
    /**
     * Transform.
     * 
     * mat  -- Matrix (3x3).
     *
     * Transform vertex, using the specified 3x3 matrix. Returns a new, 
     * transformed vertex.
     */
    transform: function(mat)
    {
        var r = GeoUtils.transform3(mat, this.getVector());
        return GeoUtils.Vertex3.createFromSeq(r);
    },
    
    /**
     * Calculate distance to plane.
     *
     * plane  -- Plane.
     *
     * Returns the distance of the vertex to the specified plane.
     */
    distanceToPlane: function(plane)
    {
        return GeoUtils.dot3(this.getVector(), plane.getNormal());
    },
    
    toString: function()
    {
        return "Vertex3[" + this.x + ", " + this.y + ", " + this.z + "]";
    }
});

// Create a vertex from a sequence of coordinates.
GeoUtils.Vertex3.createFromSeq = function(l)
{
    return new GeoUtils.Vertex3(l[0], l[1], l[2]);
}

/**
 * Polygon (3D).
 *
 * A polygon in 3D space.
 *
 * vertices  -- Vertices (list of Vertex3).
 * edges     -- Edges (list of vertex index pairs).
 */
GeoUtils.Polygon3 = Class.create(GeoUtils.Polygon2, {
    
    // Constructor.
    initialize: function($super, vertices, edges)
    {
        $super.call(this, vertices, edges);
    },
    
    /**
     * Transform vertices using the specified 3x3 matrix.
     * 
     * Returns a new, transformed polygon. The polygon will be translated so 
     * its origin (the first vertex) is at the center of the coordinate system 
     * before the transformation is applied.
     */
    transform: function(mat)
    {
        var origin = this.vertices[0].getVector();
        var nv = [];
        for (var i = 0; i < this.vertices.length; i++)
        {
            var v = this.vertices[i];
            var vt = GeoUtils.Vertex3.createFromSeq(
                GeoUtils.sub3(v.getVector(), origin));
            nv.push(vt.transform(mat));
        }
        var ne = null;
        if (this.edges.length > 0)
            ne = GeoUtils.copyMatrix(this.edges);
        else
            ne = [];
        return new GeoUtils.Polygon3(nv, ne);
    },
    
    /**
     * Get plane spanned by vertices.
     * 
     * Get the plane spanned by the specified three vertex indices. If the 
     * vertices parameter is not specified, the first two and the last 
     * vertices are used.
     */
    getPlane: function(vertices)
    {
        if (!GeoUtils.isUndefined(vertices))
        {
            var a = this.vertices[vertices[0]].getVector();
            var b = this.vertices[vertices[1]].getVector();
            var c = this.vertices[vertices[2]].getVector();
        } else
        {
            var a = this.vertices[0].getVector();
            var b = this.vertices[1].getVector();
            var c = this.vertices[this.vertices.length - 1].getVector();
        }
        return new GeoUtils.Plane3(a, 
            GeoUtils.sub3(b, a), GeoUtils.sub3(c, a));
    },
    
    /**
     * Get barycenter.
     * 
     * Returns the barycenter vector for the polygon.
     */
    getBarycenter: function()
    {
        var vSum = [0., 0., 0.];
        for (var i = 0; i < this.vertices.length; i++)
        {
            var v = this.vertices[i];
            vSum = GeoUtils.add3(vSum, v.getVector());
        }
        return GeoUtils.mult3(1. / this.vertices.length, vSum);
    },
    
    toString: function()
    {
        return "Polygon3[[" + this.vertices + "], [" + this.edges + "]]";
    }
});

/**
 * Plane (3D).
 *
 * A plane in 3D space.
 *
 * p  -- Position vector.
 * u  -- Direction vector (u).
 * v  -- Direction vector (v).
 */
GeoUtils.Plane3 = Class.create({
    
    // Constructor.
    initialize: function(p, u, v)
    {
        this.p = GeoUtils.defaultArg(p, [0., 0., 0.]);
        this.u = GeoUtils.defaultArg(u, [1., 0., 0.]);
        this.v = GeoUtils.defaultArg(v, [0., 1., 0.]);
    },
    
    // Get tangent vector.
    getTangent: function()
    {
        return GeoUtils.normalize3(this.u);
    },
    
    // Get binormal vector.
    getBinormal: function()
    {
        return GeoUtils.normalize3(GeoUtils.ortho3(this.getTangent(), this.v));
    },
    
    // Get normal vector.
    getNormal: function()
    {
        return GeoUtils.normalize3(GeoUtils.cross3(this.u, this.v));
    },
    
    /**
     * Calculate tangent space base matrix.
     * 
     * Returns the (orthogonal) base matrix of the tangent space for the 
     * plane.
     */
    getTangentBase: function()
    {
        return GeoUtils.transpose3x3([
            this.getTangent(), 
            this.getBinormal(), 
            this.getNormal()
        ]);
    },
    
    toString: function()
    {
        return "Plane3[" + GeoUtils.vectorToString(this.p) + ", " 
            + GeoUtils.vectorToString(this.u) + ", " 
            + GeoUtils.vectorToString(this.v) + "]";
    }
});

/**
 * Create plane from normal vector.
 * 
 * n  -- Normal vector.
 * t  -- Tangent vector (optional).
 * p  -- Origin vector (optional).
 * 
 * Create a plane from the specified normal vector. If a linearly independent 
 * tangent vector is specified as well, that vector will be orthonormalized 
 * and then used to construct the binormal vector. If no tangent vector is 
 * specified or the tangent vector is not linearly independent, the tangent 
 * and binormal will be determined by the implementation.
 */
GeoUtils.Plane3.createFromNormal = function(n, t, p)
{
    var n0 = GeoUtils.defaultArg(n, [0., 0., 1.]);
    var t0 = GeoUtils.defaultArg(t, [1., 0., 0.]);
    var p0 = GeoUtils.defaultArg(p, [0., 0., 0.]);
    var u = GeoUtils.copyVector(t0);
    // If n and t are not linearly independent, modify t.
    var i = 0;
    while ((GeoUtils.eq(GeoUtils.norm3(GeoUtils.cross3(n0, u)), 0.)) 
        && (i < 2))
    {
        if (i == 0)
            u = GeoUtils.copyVector(GeoUtils.E_Y_3);
        else
        if (i == 1)
            u = GeoUtils.copyVector(GeoUtils.E_Z_3);
        i += 1;
    }
    u = GeoUtils.normalize3(GeoUtils.ortho3(n0, u));
    var v = GeoUtils.normalize3(GeoUtils.cross3(n0, u));
    return new GeoUtils.Plane3(p0, u, v);
}

/**
 * Line (3D).
 * 
 * A line in 3D space.
 * 
 * p  -- Position vector.
 * u  -- Direction vector.
 */
GeoUtils.Line3 = Class.create({
    
    // Constructor.
    initialize: function(p, u)
    {
        this.p = GeoUtils.defaultArg(p, [0., 0., 0.]);
        this.u = GeoUtils.defaultArg(u, [1., 0., 0.]);
    },
    
    /**
     * Intersect plane.
     * 
     * Returns the intersection point, or null if no intersection exists.
     */
    intersectPlane: function(plane)
    {
        try
        {
            var r = GeoUtils.solve3x3(GeoUtils.transpose3x3(
                    [ plane.u, plane.v, GeoUtils.flip3(this.u) ]), 
                GeoUtils.sub3(this.p, plane.p));
        } catch (e)
        {
            return null;
        }
        return GeoUtils.add3(GeoUtils.mult3(r[2], this.u), this.p);
    },
    
    /**
     * Polygon intersection test.
     * 
     * Returns True if the intersection point of the line and the plane 
     * defined by the first three vertices of the polygon is within the 
     * polygon. Returns False otherwise. Raises IntersectionError if the 
     * polygon is not planar.
     */
    intersectionInPoly: function(poly, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var p = poly.getPlane();
        var ip = this.intersectPlane(p);
        if (ip == null)
            return false;
        // Transform polygon and intersection point to tangent space.
        var tm = p.getTangentBase();
        var tmInv = GeoUtils.invert3x3(tm);
        /* NOTE: The transform() function is expected to translate the polygon 
                 vertices into the origin coordinate system. Otherwise this 
                 will not work as expected. */
        var tp = poly.transform(tmInv);
        // Check planarity.
        for (var i = 0; i < tp.vertices.length; i++)
        {
            var v = tp.vertices[i];
            if (!GeoUtils.eq(v.z, 0., t0))
                throw new Error("[Line3.intersectionInPoly] "
                    + "Polygon is not planar (v = " + v + ").");
        }
        var origin = poly.vertices[0];
        var iv = GeoUtils.Vertex3.createFromSeq(GeoUtils.sub3(ip,
            origin.getVector())).transform(tmInv);
        return tp.checkVertex(iv, t);
    },
    
    toString: function()
    {
        return "Line3[" + GeoUtils.vectorToString(this.p) + ", " 
            + GeoUtils.vectorToString(this.u) + "]";
    }
    
});

/**
 * Sphere (3D).
 * 
 * A Sphere in 3D space.
 * 
 * p  -- Position vector.
 * r  -- Radius.
 */
GeoUtils.Sphere3 = Class.create({
    
    // Constructor.
    initialize: function(p, r)
    {
        this.p = GeoUtils.defaultArg(p, [0., 0., 0.]);
        this.r = GeoUtils.defaultArg(r, 1.);
    },
    
    toString: function()
    {
        return "Sphere3[" + GeoUtils.vectorToString(this.p) + ", " + this.r 
            + "]";
    }
    
});

/**
 * Range of values.
 * 
 * rMin  -- Minimum value.
 * rMax  -- Maximum value.
 */
GeoUtils.Range = Class.create({
    
    // Constructor.
    initialize: function(rMin, rMax)
    {
        this.rMin = GeoUtils.defaultArg(rMin, 0.);
        this.rMax = GeoUtils.defaultArg(rMax, 0.);
    },
    
    // Extend range to contain value.
    extendRange: function(value)
    {
        if (value < this.rMin)
            this.rMin = value;
        if (value > this.rMax)
            this.rMax = value;
    },
    
    // Get center of range.
    getCenter: function()
    {
        return 0.5 * (this.rMin + this.rMax);
    },
    
    // Get radius of range.
    getRadius: function()
    {
        return 0.5 * (this.rMax - this.rMin);
    },
    
    /**
     * Get range value.
     * 
     * Get the value inside the range corresponding to the parameter s, 
     * where s = 0 returns the minimum value and s = 1 returns the maximum 
     * value.
     */
    getValue: function(s)
    {
        return this.rMin + s * (this.rMax - this.rMin);
    },
    
    /**
     * Compare ranges.
     * 
     * Returns RANGE_EQUAL if the ranges are equal within the tolerance, i.e. 
     * they have the same rMin and rMax values. Returns RANGE_OTHER_CONTAINS 
     * if the range on which the method is called is contained within the 
     * other range, and RANGE_FIRST_CONTAINS if the other range is contained 
     * within the range on which the method is called. Returns RANGE_OVERLAP 
     * if the ranges overlap. Returns RANGE_DISJOINT if the ranges are 
     * disjoint.
     */
    compare: function(other, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        if (GeoUtils.eq(this.rMin, other.rMin, t0) 
            && GeoUtils.eq(this.rMax, other.rMax, t0))
            return GeoUtils.RANGE_EQUAL;
        if (GeoUtils.lt(this.rMax, other.rMin, t0) 
            || GeoUtils.gt(this.rMin, other.rMax, t0))
            return GeoUtils.RANGE_DISJOINT;
        if (GeoUtils.ltOrEq(other.rMin, this.rMin, t0) 
            && GeoUtils.gtOrEq(other.rMax, this.rMax, t0))
            return GeoUtils.RANGE_OTHER_CONTAINS;
        if (GeoUtils.ltOrEq(this.rMin, other.rMin, t0) 
            && GeoUtils.gtOrEq(this.rMax, other.rMax, t0))
            return GeoUtils.RANGE_FIRST_CONTAINS;
        return GeoUtils.RANGE_OVERLAP;
    },
    
    /**
     * Range check.
     * 
     * Returns true if the value is within the range, false otherwise.
     */
    isInRange: function(v, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        if (GeoUtils.lt(v, this.rMin, t0) || GeoUtils.gt(v, this.rMax, t0))
            return false;
        return true;
    },
    
    /**
     * Get range bounds.
     * 
     * Get the range bounds as a vector.
     */
    getBounds: function()
    {
        return [ this.rMin, this.rMax ];
    },
    
    toString: function()
    {
        return "Range[" + this.rMin + ", " + this.rMax + "]";
    }
    
});

/**
 * Range of values (3D).
 * 
 * A range of values in 3D space.
 * 
 * x  -- X range.
 * y  -- Y range.
 * z  -- Z range.
 */
GeoUtils.Range3 = Class.create({
    
    // Constructor.
    initialize: function(vec)
    {
        if (GeoUtils.isUndefined(vec))
        {
            this.x = new GeoUtils.Range();
            this.y = new GeoUtils.Range();
            this.z = new GeoUtils.Range();
        } else
        {
            this.x = new GeoUtils.Range(vec[0], vec[0]);
            this.y = new GeoUtils.Range(vec[1], vec[1]);
            this.z = new GeoUtils.Range(vec[2], vec[2]);
        }
    },
    
    // Extend range to contain values from vector.
    extendRange: function(vec)
    {
        this.x.extendRange(vec[0]);
        this.y.extendRange(vec[1]);
        this.z.extendRange(vec[2]);
    },
    
    // Get center of range.
    getCenter: function()
    {
        return [ 
            this.x.getCenter(), 
            this.y.getCenter(), 
            this.z.getCenter()
        ];
    },
    
    // Get radius vector of range.
    getRadius: function()
    {
        return [ 
            this.x.getRadius(), 
            this.y.getRadius(), 
            this.z.getRadius()
        ];
    },
    
    // Get range for specified axis.
    getAxisRange: function(axis)
    {
        if (axis == GeoUtils.AXIS_X)
            return this.x;
        if (axis == GeoUtils.AXIS_Y)
            return this.y;
        if (axis == GeoUtils.AXIS_Z)
            return this.z;
        throw new Error("[Range3.getAxisRange] Invalid axis: " + axis);
    },
    
    /**
     * Compare ranges (per axis).
     * 
     * Return a vector containing the comparison results for the range on 
     * each axis. See Range.compare() for details on the return values.
     */
    compare3: function(other, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        return [
            this.x.compare(other.x, t0), 
            this.y.compare(other.y, t0), 
            this.z.compare(other.z, t0)
        ];
    },
    
    /**
     * Compare ranges.
     * 
     * Returns RANGE_EQUAL if the ranges are equal within the tolerance, 
     * i.e. they have the same rMin and rMax values in each dimension. 
     * Returns RANGE_OTHER_CONTAINS if the range on which the method is 
     * called is contained within the other range, and RANGE_FIRST_CONTAINS 
     * if the other range is contained within the range on which the method 
     * is called. Returns RANGE_OVERLAP if the ranges overlap in some 
     * dimension. Returns RANGE_DISJOINT if the ranges are disjoint.
     */
    compare: function(other, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var c = this.compare3(other, t0);
        var xc = c[0];
        var yc = c[1];
        var zc = c[2];
        if ((xc == yc) && (xc == zc))
            // This covers the equality and disjoint on all axes cases.
            return xc
        /* Check whether the first range contains the other range with equal 
           ranges in some dimension(s). */
        var result = true;
        for (var i = 0; i < c.length; i++)
        {
            var v = c[i];
            if (v == GeoUtils.RANGE_DISJOINT)
                // Disjoint on one axis means disjoint ranges.
                return GeoUtils.RANGE_DISJOINT;
            else
            if ((v != GeoUtils.RANGE_FIRST_CONTAINS) 
                && (v != GeoUtils.RANGE_EQUAL))
                result = false;
        }
        if (result)
            return GeoUtils.RANGE_FIRST_CONTAINS;
        /* Check whether the other range contains the first range with equal 
           ranges in some dimension(s). */
        result = true;
        for (var i = 0; i < c.length; i++)
        {
            var v = c[i];
            if ((v != GeoUtils.RANGE_OTHER_CONTAINS) 
                && (v != GeoUtils.RANGE_EQUAL))
            {
                result = false;
                break;
            }
        }
        if (result)
            return GeoUtils.RANGE_OTHER_CONTAINS;
        return GeoUtils.RANGE_OVERLAP;
    },
    
    /**
     * Range check.
     * 
     * Returns true if the value is within the range, false otherwise.
     */
    isInRange: function(v, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        return (this.x.isInRange(v[0], t0) 
            && this.y.isInRange(v[1], t0) 
            && this.z.isInRange(v[2], t0));
    },
    
    // Copy the range.
    copy: function()
    {
        return GeoUtils.Range3.createFromVectors(
            this.x.getBounds(), 
            this.y.getBounds(), 
            this.z.getBounds()
        );
    },
    
    toString: function()
    {
        return "Range3[" + this.x + ", " + this.y + ", " + this.z + "]";
    }
    
});

// Create 3D range from three vectors.
GeoUtils.Range3.createFromVectors = function(rx, ry, rz)
{
    var r = new GeoUtils.Range3([ rx[0], ry[0], rz[0] ]);
    r.extendRange([ rx[1], ry[1], rz[1] ]);
    return r;
}

/**
 * Item with box bounds.
 * 
 * This class already supplies much of the bounding box functionality, but 
 * does not deal with other items that may be contained inside the bounding 
 * box.
 * 
 * center  -- Bounding box center.
 * rVec    -- Radius vector of the bounding box (positive x, y, z corner).
 * radius  -- Length of radius vector.
 * bounds  -- Value range of bounds.
 * bVerts  -- Vertices of the bounding box (list of vectors).
 * bFaces  -- Faces of the bounding box (list of polygons).
 * itemID  -- ID of the item.
 */
GeoUtils.BoxBoundsItem = Class.create(GeoUtils.Identifiable, {
    
    // Constructor.
    initialize: function($super, center, rVec, itemID)
    {
        $super.call(this);
        this.center = GeoUtils.defaultArg(center, [0., 0., 0.]);
        this.rVec = GeoUtils.defaultArg(rVec, [0., 0., 0.]);
        this.itemID = GeoUtils.defaultArg(itemID, null);
        this.bVerts = null;
        this.bFaces = null;
        this.updateBounds();
    },
    
    /**
     * Update bounds.
     * 
     * After changes to the radius vector and center, this method should be 
     * called to update the bounds of the object. This will also update the 
     * scalar radius value.
     */
    updateBounds: function()
    {
        this.bounds = new GeoUtils.Range3(this.center);
        this.bounds.extendRange(GeoUtils.add3(this.center, this.rVec));
        this.bounds.extendRange(GeoUtils.sub3(this.center, this.rVec));
        this.radius = GeoUtils.norm3(this.rVec);
    },
    
    /**
     * Update radius and center.
     * 
     * After changes to the bounds of the object, this method should be 
     * called to update the radius and center of the object.
     */
    updateRadiusAndCenter: function()
    {
        this.center = this.bounds.getCenter();
        this.rVec = this.bounds.getRadius();
        this.radius = GeoUtils.norm3(this.rVec);
    },
    
    // Clear item.
    clear: function()
    {
        this.center = [0., 0., 0.];
        this.rVec = [0., 0., 0.];
        this.updateBounds();
    },
    
    /**
     * Get vertices.
     * 
     * Get the vertices of the bounding box in the global coordinate 
     * system. Returns a list of vectors.
     */
    getVertices: function()
    {
        if (this.bVerts != null)
            return this.bVerts;
        var tVerts = [
            // Top vertices.
            [ this.rVec[0], this.rVec[1], this.rVec[2] ], 
            [ -this.rVec[0], this.rVec[1], this.rVec[2] ], 
            [ -this.rVec[0], -this.rVec[1], this.rVec[2] ], 
            [ this.rVec[0], -this.rVec[1], this.rVec[2] ], 
            // Bottom vertices.
            [ this.rVec[0], this.rVec[1], -this.rVec[2] ], 
            [ -this.rVec[0], this.rVec[1], -this.rVec[2] ], 
            [ -this.rVec[0], -this.rVec[1], -this.rVec[2] ], 
            [ this.rVec[0], -this.rVec[1], -this.rVec[2] ]
        ];
        this.bVerts = [];
        for (var i = 0; i < tVerts.length; i++)
        {
            var v = tVerts[i];
            this.bVerts.push([ GeoUtils.add3(this.center, v) ]);
        }
        return this.bVerts;
    },
    
    /**
     * Get faces.
     * 
     * Get the faces of the bounding box in the global coordinate system. 
     * Returns a list of Polygon3 objects.
     */
    getFaces: function()
    {
        if (this.bFaces != null)
            return this.bFaces;
        var verts = [];
        var vt = this.getVertices();
        for (var i = 0; i < vt.length; i++)
        {
            var v = vt[i];
            verts.push([ GeoUtils.Vertex3.createFromSeq(v) ]);
        }
        this.bFaces = [
            new GeoUtils.Polygon3([ verts[0], verts[1], verts[2], verts[3] ]), 
            new GeoUtils.Polygon3([ verts[4], verts[7], verts[6], verts[5] ]), 
            new GeoUtils.Polygon3([ verts[0], verts[3], verts[7], verts[4] ]), 
            new GeoUtils.Polygon3([ verts[1], verts[5], verts[6], verts[2] ]), 
            new GeoUtils.Polygon3([ verts[2], verts[6], verts[7], verts[3] ]), 
            new GeoUtils.Polygon3([ verts[0], verts[4], verts[5], verts[1] ])
        ];
        for (var i = 0; i < vt.length; i++)
        {
            var f = this.bFaces[i];
            f.createEdges();
        }
        return this.bFaces;
    },
    
    /**
     * Check position relative to plane.
     * 
     * Check the bounding box position relative to a plane. Returns 1 if the 
     * bounding box is above the plane (in direction of the normal of the 
     * plane), 0 if the box intersects the plane, and -1 if the bounding box 
     * is below the plane.
     */
    checkPlane: function(plane, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var d = GeoUtils.dot3(plane.getNormal(), 
            GeoUtils.sub3(this.center, plane.p));
        if (GeoUtils.gt(d, this.radius, t0))
            return 1;
        if (GeoUtils.lt(d, -this.radius, t0))
            return -1;
        /* The bounding box may intersect the plane, we have to check 
           individual vertices. If all of them are above or below the plane, 
           so is the bounding box. Otherwise, there is an intersection. */
        var verts = this.getVertices();
        // Reference value.
        var c = 0;
        // Current vertex result.
        var s = 0;
        for (var i = 0; i < verts.length; i++)
        {
            var v = verts[i];
            d = GeoUtils.dot3(plane.getNormal(), GeoUtils.sub3(v, plane.p));
            if (GeoUtils.eq(d, 0., t0))
                // Vertex lies on plane.
                return 0;
            else
            if (GeoUtils.gt(d, 0., t0))
                // Vertex is above the plane.
                s = 1;
            else
            if (GeoUtils.lt(d, 0., t0))
                // Vertex is below the plane.
                s = -1;
            if (c == 0)
                // First vertex initializes the reference.
                c = s;
            else
            if (c != s)
                // Some are above, some below.
                return 0;
        }
        return c;
    },
    
    /**
     * Check position relative to sphere.
     * 
     * Check the bounding box position relative to a sphere. Returns 1 if the 
     * bounding box is inside the sphere, 0 if the box intersects the sphere, 
     * and -1 if the bounding box is outside the sphere.
     */
    checkSphere: function(sphere, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var d = GeoUtils.norm3(GeoUtils.sub3(this.center, sphere.p))
        if (GeoUtils.gt(d, this.radius + sphere.r, t0))
            return -1;
        if (GeoUtils.lt(d + this.radius, sphere.r, t0))
            return 1;
        return 0;
    },
    
    /**
     * Check line intersection.
     * 
     * Check whether the specified line intersects the bounding box. Returns 
     * true if the line intersects the bounding box, false otherwise.
     */
    checkLine: function(line, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var faces = self.getFaces();
        for (var i = 0; i < faces.length; i++)
        {
            var f = faces[i];
            if (line.intersectionInPoly(f, t0))
                return true;
        }
        return false;
    },
    
    /**
     * Compare bounding boxes (per axis).
     * 
     * Return a vector containing the comparison results for the bounding 
     * boxes on each axis. See Range.compare() for details on the return 
     * values.
     */
    compare3: function(other, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        return this.bounds.compare3(other.bounds, t0);
    },
    
    /**
     * Compare bounding boxes.
     * 
     * Returns RANGE_EQUAL if the bounding boxes are equal within the 
     * tolerance, i.e. they have the same range in each dimension. Returns 
     * RANGE_OTHER_CONTAINS if the bounding box on which the method is called 
     * is contained within the other bounding box, and RANGE_FIRST_CONTAINS 
     * if the other bounding box is contained within the bounding box on 
     * which the method is called. Returns RANGE_OVERLAP if the bounding 
     * boxes overlap in some dimension. Returns RANGE_DISJOINT if the 
     * bounding boxes are disjoint.
     */
    compare: function(other, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        return this.bounds.compare(other.bounds, t0);
    },
    
    toString: function()
    {
        return "BoxBoundsItem[" + GeoUtils.vectorToString(this.center) + ", " 
            + GeoUtils.vectorToString(this.rVec) + ", " + this.itemID + "]";
    }
    
});

/**
 * Source for items.
 * 
 * This can be used to restore bounding box hierarchies in which the items 
 * have been replaced by dummy items with only IDs.
 */
GeoUtils.ItemSource = Class.create({
    
    // Constructor.
    initialize: function()
    {
    },
    
    /**
     * Return item.
     * 
     * Return the item with the specified ID. Throws an error if no valid 
     * BoxBoundsItem can be returned. The ItemSource class does not provide a 
     * usable implementation of this function, so it has to be provided in a 
     * derived class.
     */
    getItem: function(itemID)
    {
        throw new Error("Not implemented.");
    }
    
});

/**
 * Axis split.
 * 
 * A split object specifies an axis and a parameter for determining a 
 * position on the axis where a split occurs.
 * 
 * axis  -- Split axis.
 * s     -- Split parameter (0 <= s <= 1).
 */
GeoUtils.Split = Class.create({
    
    // Constructor.
    initialize: function(axis, s)
    {
        this.axis = GeoUtils.defaultArg(axis, GeoUtils.AXIS_X);
        this.s = GeoUtils.defaultArg(s, 0.5);
    },
    
    toString: function()
    {
        return "Split[" + GeoUtils.axisToString(this.axis) + ", " + this.s 
            + "]";
    }
    
});

/**
 * Create splits.
 * 
 * Creates the specified number of splits along the axis. Returns a list 
 * of splits.
 */
GeoUtils.Split.createSplits = function(axis, num)
{
    var n0 = GeoUtils.defaultArg(num, 1);
    if (n0 <= 0)
        return [];
    var step = 1. / (n0 + 1);
    var s = step;
    var result = [];
    while (s < 1.)
    {
        result.push(new GeoUtils.Split(axis, s));
        s += step;
    }
    return result;
}

/**
 * Bounding box.
 * 
 * A bounding box which can contain other BoxBoundsItems.
 * 
 * items   -- Items contained within the bounding box.
 * parent  -- Parent bounding box.
 * level   -- Level (only used for hierarchical bounding boxes).
 */
GeoUtils.BoundingBox = Class.create(GeoUtils.BoxBoundsItem, {
    
    // Constructor.
    initialize: function($super, center, rVec, itemID, level, items, parent)
    {
        this.level = GeoUtils.defaultArg(level, 0);
        this.items = GeoUtils.defaultArg(items, new GeoUtils.Set());
        this.parent = GeoUtils.defaultArg(parent, null);
        $super.call(this, center, rVec, itemID);
    },
    
    /**
     * Update.
     * 
     * Update all state according to the items contained in the bounding 
     * box. If the bounding box has a parent, the parent will also be updated 
     * to reflect the changes.
     */
    update: function()
    {
        if (this.items.getNumEntries() == 0)
            return;
        this.bounds = null;
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            if (this.bounds == null)
                this.bounds = new GeoUtils.Range3(it.center);
            this.bounds.extend(GeoUtils.add3(it.center, it.rVec));
            this.bounds.extend(GeoUtils.sub3(it.center, it.rVec));
        }
        this.updateRadiusAndCenter();
        if (this.parent != null)
            this.parent.update();
    },
    
    /**
     * Clear bounding box.
     * 
     * Removes all items and resets state.
     */
    clear: function($super)
    {
        this.items.clear();
        $super.call(this);
    },
    
    /**
     * Add an item to the bounding box.
     * 
     * The dimensions of the bounding box will be updated to reflect the new 
     * bounds. If maxRadius is specified, the item will not be added if adding 
     * the item would make the radius of the bounding box larger than 
     * maxRadius. Returns True if the item has been added, False otherwise.
     */
    addItem: function(item, maxRadius)
    {
        var mr0 = GeoUtils.defaultArg(maxRadius, 0.);
        if (this.items.getNumEntries() == 0)
            this.bounds = item.bounds.copy();
        if (mr0 > 0)
        {
            var b = this.bounds.copy();
            b.extendRange(GeoUtils.add3(item.center, item.rVec));
            b.extendRange(GeoUtils.sub3(item.center, item.rVec));
            /* <---- DEBUG ----- //
            GeoUtils.debug(b + ', r = ' 
                + GeoUtils.vectorToString(b.getRadius())
                + ', l(r) = ' + GeoUtils.norm3(b.getRadius()), 
                'BoundingBox.addItem');
            // <---- DEBUG ----- */
            if (GeoUtils.norm3(b.getRadius()) > mr0)
                return false;
        }
        this.bounds.extendRange(GeoUtils.add3(item.center, item.rVec));
        this.bounds.extendRange(GeoUtils.sub3(item.center, item.rVec));
        this.items.add(item);
        item.parent = this;
        this.updateRadiusAndCenter();
        return true;
    },
    
    /**
     * Remove an item from the bounding box.
     * 
     * Remove an item from the bounding box. Returns true if the item has 
     * been removed, false if the item is not contained in the bounding box.
     */
    removeItem: function(item)
    {
        if (!this.items.contains(item))
            return false;
        this.items.remove(item);
        this.update();
        return true;
    },
    
    /**
     * Add items to the bounding box.
     * 
     * Add items from the specified Hash to the bounding box. If maxItems is 
     * specified, items will not be added if the number of items in the 
     * bounding box would exceed maxItems. If maxRadius is specified, items 
     * will not be added if the radius of the bounding box would exceed 
     * maxRadius. Returns the set of items that have not been added.
     */
    addItems: function(items, maxItems, maxRadius)
    {
        var mi0 = GeoUtils.defaultArg(maxItems, 0);
        var mr0 = GeoUtils.defaultArg(maxRadius, 0.);
        var remaining = new GeoUtils.Set();
        var e0 = items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            // Check for maximum number of items.
            if ((mi0 > 0) 
                && (this.items.getNumEntries() >= mi0))
                remaining.add(it);
            else
            if (!this.addItem(it, mr0))
                remaining.add(it);
        }
        return remaining;
    },
    
    /**
     * Add items to the bounding box.
     * 
     * Add items from the specified set to the bounding box. This method 
     * removes the items which are added to the bounding box from the source 
     * set. If maxItems is specified, items will not be added if the number 
     * of items in the bounding box would exceed maxItems. If maxRadius is 
     * specified, items will not be added if the radius of the bounding box 
     * would exceed maxRadius. Returns the number of items that have been 
     * added.
     */
    takeItems: function(items, maxItems, maxRadius)
    {
        var mi0 = GeoUtils.defaultArg(maxItems, 0);
        var mr0 = GeoUtils.defaultArg(maxRadius, 0.);
        var numTaken = 0;
        var putBack = new GeoUtils.Set();
        while (items.getNumEntries() > 0)
        {
            // Check for maximum number of items.
            if ((mi0 > 0)
                && (this.items.getNumEntries() >= mi0))
            {
                items.update(putBack);
                return numTaken;
            }
            var it = items.pop();
            if (this.addItem(it, maxRadius))
                numTaken++;
            else
                putBack.add(it);
        }
        items.update(putBack);
        return numTaken;
    },
    
    /**
     * Test bounding box split.
     * 
     * Split the bounding box along the specified axis, but do not change 
     * the actual structure of the bounding box contents. The split parameter 
     * s is used to determine the position where the split should occur. 
     * If s is 0.5, the split occurs at the center of the axis. If 
     * 0 < s < 0.5, the split occurs in the lower coordinate half of the 
     * axis. If 0.5 > s > 0, the split occurs in the upper coordinate half 
     * of the axis. Returns two sets of items.
     */
    splitTest: function(split, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var b = this.bounds.getAxisRange(split.axis);
        var sc = b.getValue(split.s);
        var b0 = new GeoUtils.Set();
        var b1 = new GeoUtils.Set();
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            if (GeoUtils.ltOrEq(it.center[split.axis], sc, t0))
                b0.add(it);
            else
                b1.add(it);
        }
        return [b0, b1];
    },
    
    /**
     * Determine best split.
     * 
     * Tests all of the specified splits and returns the one where the 
     * difference between item counts in both sets is minimal. Returns None 
     * if none of the splits results in two sets with at least minItems 
     * items per set.
     */
    getBestSplit: function(splits, minItems, t)
    {
        var mi0 = GeoUtils.defaultArg(minItems, 0);
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var best = null;
        for (var i = 0; i < splits.length; i++)
        {
            var s = splits[i];
            var sr = this.splitTest(s, t0);
            var n0 = sr[0].getNumEntries();
            var n1 = sr[1].getNumEntries();
            if ((n0 >= mi0)
                && (n1 >= mi0))
            {
                // Both sets have enough elements.
                var d = Math.abs(n0 - n1);
                /* <---- DEBUG ----- //
                GeoUtils.debug("Testing " + s 
                    + ": (" + n0 + ", " + n1 + ") " + d, 
                    "BoundingBox.getBestSplit");
                // ----- DEBUG ----> */
                if (best == null)
                    best = [s, d];
                else
                {
                    if (d < best[1])
                        best = [s, d];
                    else
                    if (d == best[1])
                    {
                        // Take the split that is more balanced.
                        var d0 = Math.abs(best[0].s - 0.5);
                        var d1 = Math.abs(s.s - 0.5);
                        /* <---- DEBUG ----- //
                        GeoUtils.debug("Testing balance for " + s 
                            + ": (" + d0 + ", " + d1 + ") " + d, 
                            "BoundingBox.getBestSplit");
                        // ----- DEBUG ----> */
                        if (d1 < d0)
                            best = [s, d];
                    }
                }
            } else
            {
                // <---- DEBUG ----- //
                GeoUtils.debug("Split "
                    + s + ": (" + n0 + ", " + n1 
                    + ") not usable (minItems = " + mi0 + ").", 
                    "BoundingBox.getBestSplit");
                // ----- DEBUG ----> */
            }
        }
        if (best != null)
        {
            /* <---- DEBUG ----- //
            GeoUtils.debug("Best split: " + best[0], 
                "BoundingBox.getBestSplit");
            // ----- DEBUG ----> */
            return best[0];
        }
        return null;
    },
    
    /**
     * Split bounding box.
     * 
     * Split the bounding box along the specified axis. The splits argument 
     * can be either a single split or a list of splits. If it is a list of 
     * splits, the best split will be determinded and used. The split 
     * parameter s is used to determine the position where the split should 
     * occur. If s is 0.5, the split occurs at the center of the axis. If 
     * 0 < s < 0.5, the split occurs in the lower coordinate half of the 
     * axis. If 0.5 > s > 0, the split occurs in the upper coordinate half 
     * of the axis. If recursive is set to True, the contained boxes will be 
     * split recursively until the split boxes contain either less than 
     * minItems items or maxDepth is reached. Returns two bounding boxes, 
     * which are the new items contained in the bounding box. Returns None 
     * if the box cannot be split because it does not contain any items, 
     * or one of the recursion limits is reached.
     */
    split: function(splits, recursive, minItems, maxLevel, t, splitLevel)
    {
        var r0 = GeoUtils.defaultArg(recursive, false);
        var mi0 = GeoUtils.defaultArg(minItems, 1);
        var ml0 = GeoUtils.defaultArg(maxLevel, 0);
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var sl0 = GeoUtils.defaultArg(splitLevel, 0);
        if (this.items.getNumEntries() == 0)
        {
            // Nothing to split.
            // <---- DEBUG ----- //
            GeoUtils.debug("Nothing to split (level = " + sl0 + ").", 
                "BoundingBox.split");
            // ----- DEBUG ----> */
            return null;
        }
        if (r0)
        {
            // Check the abort conditions for recursive splitting.
            if ((mi0 > 0) 
                && (this.items.getNumEntries() <= mi0))
            {
                // <---- DEBUG ----- //
                GeoUtils.debug("Not enough items for splitting (level = " 
                    + sl0 + ").", "BoundingBox.split");
                // ----- DEBUG ----> */
                return null;
            }
            if ((ml0 > 0)
                && (sl0 >= ml0))
            {
                // <---- DEBUG ----- //
                GeoUtils.debug("Maximum level reached (level = " + sl0 + ").", 
                    "BoundingBox.split");
                // ----- DEBUG ----> */
                return null;
            }
        }
        if (!GeoUtils.isUndefined(splits.length))
            var split = this.getBestSplit(splits, mi0, t0);
        else
            var split = splits;
        if (split == null)
        {
            // There is no split that does anything useful.
            // <---- DEBUG ----- //
            GeoUtils.debug("No suitable split (level = " + sl0 + ").", 
                "BoundingBox.split");
            // ----- DEBUG ----> */
            return null;
        }
        // <---- DEBUG ----- //
        GeoUtils.debug("Splitting box with " 
            + this.items.getNumEntries() + " items using " + split 
            + " (level = " + sl0 + ").", 
            "BoundingBox.split");
        // ----- DEBUG ----> */
        var b = this.bounds.getAxisRange(split.axis);
        var sc = b.getValue(split.s);
        var b0 = new GeoUtils.BoundingBox();
        b0.level = sl0 + 1;
        var b1 = new GeoUtils.BoundingBox();
        b1.level = sl0 + 1;
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            if (GeoUtils.ltOrEq(it.center[split.axis], sc, t0))
                b0.addItem(it);
            else
                b1.addItem(it);
        }
        // <---- DEBUG ----- //
        b = null;
        if (this.compare(b0) != GeoUtils.RANGE_FIRST_CONTAINS)
            b = b0;
        if (this.compare(b1) != GeoUtils.RANGE_FIRST_CONTAINS)
            b = b1;
        if (b != null)
            throw new Error("[BoundingBox.split] " 
                + "Box not contained before splitting (" 
                + this.compare(b) + "): " + b + " (" + this 
                + "), [" + GeoUtils.rangeCompToString3(
                    this.bounds.compare3(b.bounds)) + "]");
        // ----- DEBUG ----> */
        if (r0)
        {
            // Split recursively.
            b0.split(splits, r0, mi0, ml0, t0, sl0 + 1);
            b1.split(splits, r0, mi0, ml0, t0, sl0 + 1);
        }
        // <---- DEBUG ----- //
        b = null;
        if (this.compare(b0) != GeoUtils.RANGE_FIRST_CONTAINS)
            b = b0;
        if (this.compare(b1) != GeoUtils.RANGE_FIRST_CONTAINS)
            b = b1;
        if (b != null)
            throw new Error("[BoundingBox.split] " 
                + "Box not contained after splitting (" 
                + this.compare(b) + "): " + b + " (" + this 
                + "), [" + GeoUtils.rangeCompToString3(
                    this.bounds.compare3(b.bounds)) + "]");
        // ----- DEBUG ----> */
        // Add the new boxes.
        this.clear();
        // <---- DEBUG ----- //
        GeoUtils.debug("Adding box with " 
            + b0.items.getNumEntries() + " items.", "BoundingBox.split");
        // ----- DEBUG ----> */
        this.addItem(b0);
        // <---- DEBUG ----- //
        GeoUtils.debug("Adding box with " 
            + b1.items.getNumEntries() + " items.", "BoundingBox.split");
        // ----- DEBUG ----> */
        this.addItem(b1);
        return [b0, b1];
    },
    
    /**
     * Get items above plane.
     * 
     * Get the items which are above the specified plane (in direction of 
     * the normal of the plane). Returns two sets of items, the 'surely' and 
     * 'maybe' sets. The 'surely' set contains items which are surely above 
     * the specified plane. These can be leaves or bounding boxes containing 
     * other items which are above the plane. The 'maybe' set contains only 
     * leaf items with bounding boxes that intersect the plane, so the caller 
     * has to determine if the items themselves are above the plane.
     */
    getItemsAbovePlane: function(plane, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var surely = new GeoUtils.Set();
        var maybe = new GeoUtils.Set();
        var r = this.checkPlane(plane, t0);
        if (r == 1)
        {
            // Everything in this bounding box is above the plane.
            surely.add(this);
            return [ surely, maybe ];
        } else
        if (r == -1)
        {
            // Nothing in this bounding box is above the plane.
            return [ surely, maybe ];
        }
        if (this.items.getNumEntries() == 0)
            throw new Error("Bounding box used as a leaf.");
        // There is some intersection, so we need to go into the details.
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            r = it.checkPlane(plane, t0);
            if (r == 1)
                surely.add(it);
            else
            if (r == 0)
            {
                if (!GeoUtils.isUndefined(it.boundingBoxType))
                {
                    /* If this is a bounding box, check the items contained 
                       within recursively. */
                    var ts = it.getItemsAbovePlane(plane, t0);
                    surely.update(ts[0]);
                    maybe.update(ts[1]);
                } else
                {
                    // Leaf item, which is not a bounding box.
                    maybe.add(it);
                }
            }
        }
        return [ surely, maybe ];
    },
    
    /**
     * Get items which intersect line.
     * 
     * Get the leaf items from the bounding box hierarchy which may be 
     * intersected by the specified line. Returns a set of leaf items. For 
     * leaf items which do not have a checkLine method, it is up to the 
     * caller to determine if there are actual intersections.
     */
    getItemsOnLine: function(line, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var result = new GeoUtils.Set();
        if (!this.checkLine(line, t0))
        {
            // If this bounding box is not intersected, nothing in it will be.
            return result;
        }
        if (this.items.getNumEntries() == 0)
            throw new Error("Bounding box used as a leaf.");
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            if (it.checkLine(line, t0))
            {
                if (!GeoUtils.isUndefined(it.boundingBoxType))
                {
                    // Bounding box is intersected, check contained items.
                    result.update(it.getItemsOnLine(line, t0));
                } else 
                if (!GeoUtils.isUndefined(it.checkLine))
                {
                    // Leaf item, which supports checkLine.
                    if (it.checkLine(line, t))
                        result.add(it);
                } else
                {
                    // Leaf item, which is not a bounding box.
                    result.add(it);
                }
            }
        }
        return result;
    },
    
    /**
     * Get items in sphere.
     * 
     * Get the items which are inside the specified sphere. Returns two sets 
     * of items, the 'surely' and 'maybe' sets. The 'surely' set contains 
     * items which are surely inside the specified sphere. These can be 
     * leaves or bounding boxes containing other items which are inside the 
     * sphere. The 'maybe' set contains only leaf items with bounding boxes 
     * that intersect the sphere, so the caller has to determine if the 
     * items themselves are inside the sphere.
     */
    getItemsInSphere: function(sphere, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var surely = new GeoUtils.Set();
        var maybe = new GeoUtils.Set();
        var r = this.checkSphere(plane, t0);
        if (r == 1)
        {
            // Everything in this bounding box is inside the sphere.
            surely.add(this);
            return [ surely, maybe ];
        } else
        if (r == -1)
        {
            // Nothing in this bounding box is inside the sphere.
            return [ surely, maybe ];
        }
        if (this.items.getNumEntries() == 0)
            throw new Error("Bounding box used as a leaf.");
        // There is some intersection, so we need to go into the details.
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            r = it.checkPlane(plane, t0);
            if (r == 1)
                surely.add(it);
            else
            if (r == 0)
            {
                if (!GeoUtils.isUndefined(it.boundingBoxType))
                {
                    /* If this is a bounding box, check the items contained 
                       within recursively. */
                    var ts = it.getItemsInSphere(plane, t0);
                    surely.update(ts[0]);
                    maybe.update(ts[1]);
                } else
                {
                    // Leaf item, which is not a bounding box.
                    maybe.add(it);
                }
            }
        }
        return [ surely, maybe ];
    },
    
    /**
     * Get items in box.
     * 
     * Get the items which are inside the specified bounding box (which can 
     * be simply a BoxBoundsItem). Returns two sets of items, the 'surely' 
     * and 'maybe' sets. The 'surely' set contains items which are surely 
     * inside the specified bounding box. These can be leaves or bounding 
     * boxes containing other items which are inside the bounding box. The 
     * 'maybe' set contains only leaf items with bounding boxes that 
     * intersect the bounding box, so the caller has to determine if the 
     * items themselves are inside the box.
     */
    getItemsInBox: function(box, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var surely = new GeoUtils.Set();
        var maybe = new GeoUtils.Set();
        var r = this.compare(box, t0);
        if (r == GeoUtils.RANGE_OTHER_CONTAINS)
        {
            // Everything in this bounding box is inside the other box.
            surely.add(this);
            return [ surely, maybe ];
        } else
        if (r == GeoUtils.RANGE_DISJOINT)
        {
            // Nothing in this bounding box is inside the sphere.
            return [ surely, maybe ];
        }
        if (this.items.getNumEntries() == 0)
            throw new Error("Bounding box used as a leaf.");
        // There is some intersection, so we need to go into the details.
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            r = it.compare(box, t0);
            if (r == GeoUtils.RANGE_OTHER_CONTAINS)
                surely.add(it);
            else
            if (r == GeoUtils.RANGE_OVERLAP)
            {
                if (!GeoUtils.isUndefined(it.boundingBoxType))
                {
                    /* If this is a bounding box, check the items contained 
                       within recursively. */
                    var ts = it.getItemsInBox(box, t0);
                    surely.update(ts[0]);
                    maybe.update(ts[1]);
                } else
                {
                    // Leaf item, which is not a bounding box.
                    maybe.add(it);
                }
            }
        }
        return [ surely, maybe ];
    },
    
    /**
     * Get containing leaf.
     * 
     * Return the leaf item that contains the speified item, or null if none 
     * of the leaf items contains that item.
     */
    getContainingLeaf: function(item, t)
    {
        var t0 = GeoUtils.defaultArg(t, GeoUtils.DEFAULT_TOLERANCE);
        var r = this.compare(item, t0);
        // <---- DEBUG ----- //
        GeoUtils.debug('' + this + " (check: " 
            + GeoUtils.rangeCompToString(r) + ").", 
            "BoundingBox.getContainingLeaf");
        // ----- DEBUG ----> */
        if ((r != GeoUtils.RANGE_FIRST_CONTAINS)
            && (r != RANGE_EQUAL))
        {
            // This box does not contain the item.
            return null;
        }
        if (this.items.getNumEntries() == 0)
        {
            // This box contains the item.
            return this;
        }
        // Check children.
        var e0 = this.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            r = it.compare(item, t0);
            if ((r == GeoUtils.RANGE_FIRST_CONTAINS)
                || (r == GeoUtils.RANGE_EQUAL))
            {
                // Child box contains the item.
                var rb = null;
                if (!GeoUtils.isUndefined(it.boundingBoxType))
                {
                    // Check boxes recursively.
                    rb = it.getContainingLeaf(item, t0);
                } else
                {
                    // We have found the containing leaf item.
                    rb = it;
                }
                if (rb != null)
                    return rb;
            }
        }
        return null;
    },
    
    toString: function()
    {
        return "BoundingBox[" + GeoUtils.vectorToString(this.center) + ", " 
            + GeoUtils.vectorToString(this.rVec) + ", " + this.itemID + ", " 
            + this.level + "]";
    },
    
    // Type identification.
    boundingBoxType: true
    
});

