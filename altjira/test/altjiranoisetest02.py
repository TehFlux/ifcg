#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Altjira/Noise test 02"""
import noise
import Altjira as ai
import AltjiraNoise as an
import IFMapping as im
import IFMappingNoise as imn

imageSize = (1024, 1024)
curveFile0 = 'test/curves/curve02.svg'
outFile0 = 'temp/noisetest02.png'
scale = 7.13

print("Loading curve from SVG file...")
cWidth = 1000
cHeight = 1000
pScale = cWidth
pOffset = 0.
fOffset = im.Point(0., 1., 0.)
fScale = im.Point(1. / cWidth, -1. / cHeight, 1.)
d0 = im.getAttrValue(curveFile0, 'path', 'spline01', 'd')
c0 = im.BezierSpline.create()
c0.initFromSVG(d0)
m0 = c0.createFunc(pScale, pOffset, fScale, fOffset)
m1 = im.Lookup.create()
m1.setSource(m0)
m1.update(256)

nm0 = imn.NoiseMapTransform()
nm0.setFunc(m1)

print("Creating noise graph...")
p0 = noise.Perlin()
p0.SetSeed(2733)
p0.SetOctaveCount(12)
p0.SetFrequency(0.551)
p0.SetLacunarity(2.101)
p1 = noise.RidgedMulti()
p1.SetSeed(2321)
p1.SetOctaveCount(8)
p1.SetFrequency(0.453)
p1.SetLacunarity(3.1)
a0 = noise.Add()
a0.SetSourceModule(0, p0)
a0.SetSourceModule(1, p1)
n0 = noise.Const()
n0.SetConstValue(0.7)
n1 = noise.Multiply()
n1.SetSourceModule(0, n0)
n1.SetSourceModule(1, a0)

s = noise.ScalePoint()
s.SetXScale(scale)
s.SetYScale(scale)
s.SetZScale(scale)
s.SetSourceModule(0, n1)

print("Creating noise map...")
m = noise.NoiseMap()
b = noise.NoiseMapBuilderPlane()
b.EnableSeamless();
b.SetBounds(-0.5, 0.5, -0.5, 0.5)
b.SetDestSize(*imageSize)
b.SetDestNoiseMap(m)
b.SetSourceModule(s)
b.Build()
nm0.transform(m)
i = noise.Image(*imageSize)
r = noise.RendererImage()
r.BuildGrayscaleGradient()
r.SetSourceNoiseMap(m)
r.SetDestImage(i)

print("Rendering noise map to image...")

r.Render()
i0 = ai.Image(*imageSize)
an.setImage(i, i0)

print("Creating color band...")
cb0 = ai.ColorBand.terrain()
i0.addLocalRef(cb0)

print("Transforming values...")
i0.valuesToColor(cb0)

print("Writing image to '" + outFile0 + "'...")
i0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("All done!")
