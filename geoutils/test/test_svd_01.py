import IFObjectBase as ib
import CGeoUtils as cg
import math as m

mm = ib.IFObject()
r = cg.Matrix3.rotate(0.5 * m.pi, cg.AXIS_X)
mm.addLocalRef(r)

u = cg.Matrix3.create()
s = cg.Vector3.create()
v = cg.Matrix3.create()
mm.addLocalRef(u)
mm.addLocalRef(s)
mm.addLocalRef(v)

r.svd(u, s, v)

print("r: %s" % r.getValueString())
print("u: %s" % u.getValueString())
print("s: %s" % s.getValueString())
print("v: %s" % v.getValueString())

m0 = r.copy()
mm.addLocalRef(m0)
m0.subtractIP(cg.Matrix3.UNIT)
m0.svd(u, s, v)
v.transposeIP()

print("m0: %s" % m0.getValueString())
print("u: %s" % u.getValueString())
print("s: %s" % s.getValueString())
print("v': %s" % v.getValueString())

