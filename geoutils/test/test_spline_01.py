import IFObjectBase as ib
import IFMapping as im
import CGeoUtils as cg
import IFTemplate as ift

testName = "Spline (01)"

print("GeoUtils test: %s" % testName)

# memory management
mm = ib.IFObject()

inFile0 = 'test/images/spline02.svg'
outFile0 = 'temp/test_spline_01-01.svg'
outFile1 = 'temp/test_spline_01-01.xml'
templatePath0 = 'test/template'
smoothness = 0.2
scale0 = 10.

print("Reading polygon data from file '%s'..." % inFile0)

d0 = im.getAttrValue(inFile0, "path", "poly01", "d")
print("  path data: %s" % d0)

poly0 = cg.Polygon3.create()
mm.addLocalRef(poly0)
vs0 = poly0.getVertexSource()
cg.extractSVGVertices(d0, vs0)
print("  polygon: [%s]" % poly0.getValueString())

spline0 = im.BezierSpline.create()
mm.addLocalRef(spline0)

print("Creating interpolating spline...")

poly0.createSplineInterp(spline0, smoothness)

print("  spline: [%s]" % spline0.getValueString())

print("Transforming spline...")

poly1 = cg.Polygon3.create()
mm.addLocalRef(poly1)
poly1.initFromSpline(spline0)
poly1.center()
poly1.normalize()
poly1.scale(scale0, scale0, scale0)
poly1.applyTransform()

print(poly1.getString())

spline1 = im.BezierSpline.create()
mm.addLocalRef(spline1)
poly1.createSpline(spline1)

print("  Transformed spline XML data:")

xml0 = spline1.getXML0()
print(xml0)

print("Writing transformed spline XML data to file '%s'..." % outFile1)

spline1.writeToXMLFile(outFile1)

print("Writing spline SVG data to file '%s'..." % outFile0)

tr0 = ift.TemplateRepository.create()
mm.addLocalRef(tr0)
tr0.addTemplatePath(templatePath0)
tr0.update()

config0 = ift.ConfigTree.create()
mm.addLocalRef(config0)

r0 = config0.getRoot()
n0 = r0.findChild("splineData")
n0.setData(spline0.getSVGPathData())

tpl0 = ift.Template.create("", r0, tr0)
mm.addLocalRef(tpl0)
d1 = tpl0.processModule('spline')

f0 = open(outFile0, 'w')
f0.write(d1)
f0.close()

print("All done!")
