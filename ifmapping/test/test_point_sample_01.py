import IFObjectBase as ib
import IFMapping as im
import math as m

testName = "Point sample (01)"
enableMemDebug = True

print("IFMapping test: %s" % testName)

# memory management
mm = ib.IFObject()
if (enableMemDebug):
    mmh = ib.IFMMEventHandler.getInstance()
    mmh.clearLogFile()
    mmh.setLogFileName('temp/memdebug.log')

relativeError0 = 1e-5
t0 = 0.
t1 = 0.25
inFile0 = 'test/curves/spline01.xml'

spline0 = im.BezierSpline.create()
mm.addLocalRef(spline0)

print("  Reading spline XML data from file '%s'..." % inFile0)

spline0.loadFromXMLFile(inFile0)

print("  spline: [%s]" % spline0.getValueString())

p0 = spline0.getSample(t1, True)
mm.addLocalRef(p0)

print("  point sample: (%s)" % p0.getValueString())

if (enableMemDebug):
    mm.removeAllLocalRefs()
    ib.IFMMEventHandler.cleanup()
print("All done!")

