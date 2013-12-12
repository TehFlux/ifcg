import IFObjectBase as ib
import IFMapping as im
import math as m

testName = "Arc length (01)"

print("IFMapping test: %s" % testName)

# memory management
mm = ib.IFObject()

relativeError0 = 1e-5
t0 = 0.
t1 = 0.25
inFile0 = 'test/curves/spline01.xml'

spline0 = im.BezierSpline.create()
mm.addLocalRef(spline0)

print("  Reading spline XML data from file '%s'..." % inFile0)

spline0.loadFromXMLFile(inFile0)

print("  spline: [%s]" % spline0.getValueString())

m0 = im.ArcLength.create(spline0, 0., 1., t0, relativeError0)
mm.addLocalRef(m0)

s0 = m0(t1)
p0 = spline0.evalArcLength(s0)

print("  arc length (t = %d): %f" % (t1, s0))
print("  spline point (s = %f): (%s)" % (s0, p0.getValueString()))

print("All done!")
