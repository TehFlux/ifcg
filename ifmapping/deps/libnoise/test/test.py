"""
    This file is part of pynoise

    pynoise is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    pynoise is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pynoise; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
"""

from noise import *

myModule = Perlin()
myModule.SetOctaveCount(4);

heightMap = NoiseMap()
heightMapBuilder = NoiseMapBuilderPlane()
heightMapBuilder.SetSourceModule(myModule)
heightMapBuilder.SetDestNoiseMap(heightMap)
heightMapBuilder.SetDestSize(256, 256)
heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0)
heightMapBuilder.Build()

renderer = RendererImage()
image = Image()
renderer.SetSourceNoiseMap(heightMap)
renderer.SetDestImage(image)
renderer.ClearGradient()
renderer.AddGradientPoint (-1.0000, Color (  0,   0, 128, 255))# deeps
renderer.AddGradientPoint (-0.2500, Color (  0,   0, 255, 255))# shallow
renderer.AddGradientPoint ( 0.0000, Color (  0, 128, 255, 255))# shore
renderer.AddGradientPoint ( 0.0625, Color (240, 240,  64, 255))# sand
renderer.AddGradientPoint ( 0.1250, Color ( 32, 160,   0, 255))# grass
renderer.AddGradientPoint ( 0.3750, Color (224, 224,   0, 255))# dirt
renderer.AddGradientPoint ( 0.7500, Color (128, 128, 128, 255))# rock
renderer.AddGradientPoint ( 1.0000, Color (255, 255, 255, 255))# snow
renderer.EnableLight()

renderer.SetLightContrast(3.0)
renderer.SetLightBrightness(2.0)
renderer.Render();

writer = WriterBMP()
writer.SetSourceImage(image)
writer.SetDestFilename('test.bmp')
writer.WriteDestFile()

print("Done")
