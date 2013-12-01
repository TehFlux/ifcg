import IFObjectBase as ib
import CGeoUtils as cg
import math as m

testName = "SVD (01)"

print("CGeoUtils test: %s" % testName)

mm = ib.IFObject()

axis0 = cg.Vector3.create(1., 2., 3.)
mm.addLocalRef(axis0)
axis0.normalizeIP()
print("  rotation axis: (%s)" % axis0.getValueString())

#r = cg.Matrix3.rotate(0.5 * m.pi, cg.AXIS_Z).copy()
r = cg.Matrix3.rotate(0.5 * m.pi, axis0).copy()
mm.addLocalRef(r)

u = cg.Matrix3.create()
s = cg.Vector3.create()
v = cg.Matrix3.create()
mm.addLocalRef(u)
mm.addLocalRef(s)
mm.addLocalRef(v)

r.svd(u, s, v)

print("  r: %s" % r.getValueString())
print("  u: %s" % u.getValueString())
print("  s: %s" % s.getValueString())
print("  v: %s" % v.getValueString())

m0 = r.copy()
mm.addLocalRef(m0)
m0.subtractIP(cg.Matrix3.UNIT)
m0.svd(u, s, v)

print("  m0: %s" % m0.getValueString())
print("  u:  %s" % u.getValueString())
print("  s:  %s" % s.getValueString())
print("  v:  %s" % v.getValueString())

axis1 = v.getC2()
angle0 = m.acos(0.5 * (r.trace() - 1.))
print("  rotation axis:          (%s)" % axis1.getValueString())
print("  rotation angle (1/pi):  %f" % (angle0 / m.pi))

print("All done!")
