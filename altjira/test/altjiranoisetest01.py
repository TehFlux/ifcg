#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Altjira/Noise test 01"""
import noise
import Altjira as ai
import AltjiraNoise as an

imageSize = (512, 512)
outFile0 = 'temp/noisetest01.png'

print("Creating noise graph...")

p0 = noise.RidgedMulti()
p0.SetSeed(2)
p0.SetOctaveCount(2)
p0.SetFrequency(0.451)
p0.SetLacunarity(2.)
s = noise.ScalePoint()
s.SetXScale(8.)
s.SetYScale(8.)
s.SetZScale(8.)
s.SetSourceModule(0, p0)

print("Creating noise map...")
m = noise.NoiseMap()
b = noise.NoiseMapBuilderPlane()
b.EnableSeamless();
b.SetBounds(-0.5, 0.5, -0.5, 0.5)
b.SetDestSize(*imageSize)
b.SetDestNoiseMap(m)
b.SetSourceModule(s)
b.Build()
i = noise.Image(*imageSize)
r = noise.RendererImage()
r.BuildGrayscaleGradient()
r.SetSourceNoiseMap(m)
r.SetDestImage(i)

print("Rendering noise map...")
r.Render()

#w = noise.WriterBMP()
#w.SetSourceImage(i)
#w.SetDestFilename("temp/noisetest01.bmp")
#w.WriteDestFile()

print("Writing image to '" + outFile0 + "'...")
i0 = ai.Image(*imageSize)
an.setImage(i, i0)
i0.writeToFile(outFile0, ai.Image.TYPE_PNG)

print("All done!")
