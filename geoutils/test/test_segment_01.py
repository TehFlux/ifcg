import IFObjectBase as ib
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import IFTemplate as ift
import os

testName = "Segment (01)"

print("GeoUtils test: %s" % testName)

# memory management
mm = ib.IFObject()

inFile0 = 'test/images/spline03.svg'
numSamples0 = 20
outFile0 = 'temp' + os.path.sep + 'test_segment_01_01.svg'
imageWidth = 1000
imageHeight = 1000
numStyles = 10
numSplitLevels0 = 7

d0 = im.getAttrValue(inFile0, "path", "spline01", "d")
#print("  path data: %s" % d0)

ps0 = im.PointSet.create()
mm.addLocalRef(ps0)
im.extractSVGControlPoints(d0, ps0)
#print("  point set: [%s]" % ps0.getValueString())

spline0 = im.BezierSpline.create()
mm.addLocalRef(spline0)
spline0.initFromSVG(d0)

print("  spline: [%s]" % spline0.getValueString())
#print("  spline (SVG path data): [%s]" % spline0.getSVGPathData())

print("  Sampling spline...")

p0 = cg.Polygon3.create()
mm.addLocalRef(p0)
p0.sample(spline0, numSamples0)

print("    p0: [%s]" % p0.getValueString())

print("  Creating segments...")

seg0 = im.Segment.create(spline0)
mm.addLocalRef(seg0)

print("    seg0: [%s]" % seg0.getValueString())

seg0.split(2, True, True, im.Segment.DEFAULT_ERROR_THRESHOLD, 
    numSplitLevels0)

seg1 = im.Segment.create()
mm.addLocalRef(seg1)
seg0.getLeafSegments(seg1)

print("    seg1: [%s]" % seg1.getValueString())

p1 = cg.Polygon3.create()
mm.addLocalRef(p1)
p1.initFromSegment(seg0)

print("    p1: [%s]" % p1.getValueString())

# Visualize the results.
styleSource = cg.SVGShapeStyleVectorSource.create()

# Styles for the grid polygons
st0 = cg.getSVGShapeStyle("#707070", 0.7, "#000000", 1., 0.)
styleSource.addStyle(st0)
styleSource.addStyle(st0)
st1 = cg.getSVGShapeStyle("#707070", 0.0, "#707070", 0.7, 1.)
styleSource.addStyle(st1)
styleSource.addStyle(st1)

# Create color styles.
colors = ai.ColorVector()
c0 = ai.createFloatColor(0.0, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
c1 = ai.createFloatColor(0.8, 0.9, 1., 0.6, ai.Color.SPACE_HSV)
ai.createColors(colors, c0, c1, numStyles, 1, 1)
numColors = colors.size()

outlineStyles = []
solidStyles = []
for i in range(0, numColors):
    c = colors[i]
    ch0 = c.getHex()
    #print(("    c%02d = " % i) + ch0)
    s0 = cg.getSVGShapeStyle("none", 0., ch0[:7], c.getAlpha(), 1.)
    s1 = cg.getSVGShapeStyle(ch0[:7], c.getAlpha(), "#000000", 0., 0.)
    outlineStyles += [s0]
    solidStyles += [s1]

# Create the grid polygons (two lines and two circles)
ps0 = cg.Polygon3Set.create()
mm.addLocalRef(ps0)
sq0 = cg.Polygon3.square()
sq0.scale(cg.Vector3(imageWidth, 1., 1.))
sq1 = cg.Polygon3.square()
sq1.scale(cg.Vector3(1., 1., imageHeight))
sq1.translate(cg.Vector3(0.5, 0., 0.))
ci0 = cg.Polygon3.circle(100)
ci0.scale(cg.Vector3(0.4 * imageWidth, 1., 0.4 * imageWidth))
ci1 = cg.Polygon3.circle(100)
ci1.scale(cg.Vector3(0.1 * imageWidth, 1., 0.1 * imageWidth))

# Add the curve polygons.
ps1 = cg.Polygon3Set.create()
mm.addLocalRef(ps1)
ps1.addPolygon(p0)
style0 = outlineStyles[7 % numColors]
style0.closePath = False
style0.shapeType = cg.SHAPE_TYPE_PATH
styleSource.addStyle(style0)
ps1.addPolygon(p1)
style1 = outlineStyles[4 % numColors]
style1.closePath = False
style1.shapeType = cg.SHAPE_TYPE_PATH
styleSource.addStyle(style1)
m0 = cg.Matrix4.translate(-0.5 * imageWidth, -0.5 * imageHeight, 0.);
m1 = cg.Matrix4.scale(1., -1., 1.);
m2 = cg.Matrix4.swapAxes(cg.AXIS_X, cg.AXIS_Z, cg.AXIS_Y)
ps1.transform(m0)
ps1.transform(m1)
ps1.transform(m2)
ps1.applyTransform()

# Add all polygons to the main set.
ps0.addPolygon(sq0)
ps0.addPolygon(sq1)
ps0.addPolygon(ci0)
ps0.addPolygon(ci1)
ps0.addPolygons(ps1)

print("  Rendering to SVG image '" + outFile0 + "'...")
ip0 = cg.SVGImageProperties()
ip0.setFileName(outFile0)
ip0.setStyleSource(styleSource)
ip0.setWidth(imageWidth)
ip0.setHeight(imageHeight)
ip0.setOrigin(cg.Vector2(imageWidth / 2, imageHeight / 2))
ps0.writeSVG(ip0, "polygon", cg.AXIS_Y)

print("All done!")
