#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Coordinate/sequence conversion."""

def coordsToSeq(coords, dimensions):
    """Transform coordinates to sequence number."""
    result = 0
    f = 1
    for i in range(0, len(coords)):
        d = dimensions[i]
        c = coords[i]
        result += f * c
        f *= d
    return result

def seqToCoords(seq, dimensions):
    """Transform sequence number to coordinates."""
    result = []
    c0 = seq
    for i in range(0, len(dimensions)):
        d = dimensions[i]
        r = c0 % d
        c0 = int(c0 / d)
        result += [r]
    return result

