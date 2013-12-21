import IFObjectBase as ib
import CGeoUtils as cg
import math as m

testName = "QR decomposition (01)"

print("CGeoUtils test: %s" % testName)

# memory management
mm = ib.IFObject()

m0 = cg.MatrixMN.create(3, 3, 
    1., -2., 1., 
    2., 1., 3.,
    0., -1., -2.
)
mm.addLocalRef(m0)

print("  m0:")
print(m0.getValueStringF(3))

q0 = cg.MatrixMN.create(3, 3)
r0 = cg.MatrixMN.create(3, 3)
mm.addLocalRef(q0)
mm.addLocalRef(r0)

m0.qrDecomp(q0, r0)
q0.roundIP(4)
r0.roundIP(4)

print("  q0:")
print(q0.getValueStringF(10))
print("  r0:")
print(r0.getValueStringF(10))

b0 = cg.VectorN.create(3)
b1 = cg.VectorN.create(3)
b2= cg.VectorN.create(3)
mm.addLocalRef(b0)
mm.addLocalRef(b1)
mm.addLocalRef(b2)
b0.setElements(cg.Vector3.E_X)
b1.setElements(cg.Vector3.E_Y)
b2.setElements(cg.Vector3.E_Z)

print("  b0: %s" % b0.getValueString())
print("  b1: %s" % b1.getValueString())
print("  b2: %s" % b2.getValueString())

x0 = cg.VectorN.create(3)
x1 = cg.VectorN.create(3)
x2= cg.VectorN.create(3)
mm.addLocalRef(x0)
mm.addLocalRef(x1)
mm.addLocalRef(x2)

cg.MatrixMN.qrSolve(q0, r0, b0, x0)
cg.MatrixMN.qrSolve(q0, r0, b1, x1)
cg.MatrixMN.qrSolve(q0, r0, b2, x2)

print("  x0: %s" % x0.getValueString())
print("  x1: %s" % x1.getValueString())
print("  x2: %s" % x2.getValueString())

m1 = cg.MatrixMN.create(3, 3)
mm.addLocalRef(m1)
m1.setCol(0, x0)
m1.setCol(1, x1)
m1.setCol(2, x2)

print("  m1: [%s]" % m1.getValueString())

m2 = cg.MatrixMN.create(3, 3)
mm.addLocalRef(m2)
m0.multiply(m1, m2)
m2.roundIP()

print("  m2: [%s]" % m2.getValueString())

print("All done!")
