#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""IFMapping/Noise test 01"""
import noise
import IFMapping as im
import IFMappingNoise as imn
try:
    # Use Altjira for image output if available.
    import Altjira as ai
    import AltjiraNoise as an
    haveAltjira = True
except ImportError as e:
    haveAltjira = False

imageSize = (512, 512)
noiseScale = 7.
#curveFile01 = 'test/curves/curve02.svg'
#curveFile01 = 'test/curves/curve03.svg'
curveFile01 = 'test/curves/curve04.svg'
outFile0 = 'temp/noisetest01'

def getMinMax(m):
    """Get minimum and maximum values of noise map."""
    mMin = None
    mMax = None
    w = m.GetWidth()
    h = m.GetHeight()
    for x in range(0, w):
        for y in range(0, h):
            v = m.GetValue(x, y)
            if ((mMin is None) 
                or (v < mMin)):
                mMin = v
            if ((mMax is None) 
                or (v > mMax)):
                mMax = v
    return (mMin, mMax)

print("Loading curve data from file...")
ms0 = im.MappingSet()
cWidth = 1000
cHeight = 1000
pScale = cWidth
pOffset = 0.
fOffset = im.Point(0., 1., 0.)
fScale = im.Point(1. / cWidth, -1. / cHeight, 1.)
d0 = im.getAttrValue(curveFile01, 'path', 'spline01', 'd')
c0 = im.BezierSpline.create()
c0.initFromSVG(d0)
m0 = c0.createFunc(pScale, pOffset, fScale, fOffset)
# Create a LUT for a huge performance boost.
m1 = im.Lookup.create()
m1.setSource(m0)
m1.update(256)

print("Creating noise graph...")

p0 = noise.RidgedMulti()
p0.SetSeed(2)
p0.SetOctaveCount(2)
p0.SetFrequency(0.451)
p0.SetLacunarity(2.)
s = noise.ScalePoint()
s.SetXScale(noiseScale)
s.SetYScale(noiseScale)
s.SetZScale(noiseScale)
s.SetSourceModule(0, p0)

nm0 = imn.NoiseMapping()
nm0.setFunc(m1)
nm0.SetSourceModule(s)

print("Creating noise map...")
m = noise.NoiseMap()
b = noise.NoiseMapBuilderPlane()
b.EnableSeamless();
b.SetBounds(-0.5, 0.5, -0.5, 0.5)
b.SetDestSize(*imageSize)
b.SetDestNoiseMap(m)
b.SetSourceModule(nm0)
b.Build()

mMin, mMax = getMinMax(m)
print("  min = " + str(mMin) + ", max = " + str(mMax))

i = noise.Image(*imageSize)
r = noise.RendererImage()
r.BuildGrayscaleGradient()
r.SetSourceNoiseMap(m)
r.SetDestImage(i)

print("Rendering noise map...")
r.Render()

if (not haveAltjira):
    fn0 = outFile0 + ".bmp"
    print("You do not seem to have Altjira installed! PNG output disabled.")
    print("Writing image to '" + fn0 + "'...")
    w = noise.WriterBMP()
    w.SetSourceImage(i)
    w.SetDestFilename(fn0)
    w.WriteDestFile()
else:
    fn0 = outFile0 + ".png"
    print("Writing image to '" + fn0 + "'...")
    i0 = ai.Image(*imageSize)
    an.setImage(i, i0)
    i0.writeToFile(fn0, ai.Image.TYPE_PNG)

print("All done!")
