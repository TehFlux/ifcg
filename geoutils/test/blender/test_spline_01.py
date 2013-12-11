import IFObjectBase as ib
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Data as bgd
import BGeoUtils.Object as bgo
import math as m

# memory management
mm = ib.IFObject()

name = "Spline01"
#inFile0 = '/Users/flux/recent/ifcg/geoutils/test/curves/spline01.xml'
inFile0 = '/home/flux4/recent/ifcg/geoutils/test/curves/spline01.xml'

spline0 = im.BezierSpline.create()
mm.addLocalRef(spline0)

spline0.loadFromXMLFile(inFile0)

gs0 = bgd.BezierSpline(name + "C_0", spline0)
bc0 = gs0.createBCurve(None)
o0 = bgo.Object(name, gs0)
o0.createBObject()

spline1 = im.BezierSpline.create()
mm.addLocalRef(spline1)

gs1 = bgd.BezierSpline(name + "M_1", spline1)
gs1.setFromBCurve(bc0)

print(spline1.getString())

