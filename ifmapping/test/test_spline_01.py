import IFObjectBase as ib
import IFMapping as im
import math as m

testName = "Spline (01)"

print("IFMapping test: %s" % testName)

# memory management
mm = ib.IFObject()

inFile0 = 'test/images/spline02.svg'

d0 = im.getAttrValue(inFile0, "path", "curve01", "d")
print("  path data: %s" % d0)

ps0 = im.PointSet.create()
mm.addLocalRef(ps0)
im.extractSVGControlPoints(d0, ps0)
print("  point set: [%s]" % ps0.getValueString())

c0 = im.BezierSpline.create()
mm.addLocalRef(c0)
c0.initFromSVG(d0)

print("  spline:                 [%s]" % c0.getValueString())
print("  spline (SVG path data): [%s]" % c0.getSVGPathData())

print("All done!")
