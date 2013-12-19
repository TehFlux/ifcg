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

print("  m0: [%s]" % m0.getValueString())

q0 = cg.MatrixMN.create(3, 3)
r0 = cg.MatrixMN.create(3, 3)
mm.addLocalRef(q0)
mm.addLocalRef(r0)

m0.qrDecomp(q0, r0)

print("  q:  %s" % q0.getValueString())
print("  r:  %s" % r0.getValueString())

print("All done!")
