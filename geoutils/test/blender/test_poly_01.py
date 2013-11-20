import IFObjectBase as ib
import Altjira as ai
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo
import math as m

# memory management
mm = ib.IFObject()

name = "Poly01"

p0 = cg.Polygon3.circle()
mm.addLocalRef(p0)

gp0 = bgm.Polygon3(name + "M_0", p0)
bm0 = gp0.createBMesh(None)
o0 = bgo.Object(name, gp0)
o0.createBObject()

p1 = cg.Polygon3.create()
mm.addLocalRef(p1)

gp1 = bgm.Polygon3(name + "M_1", p1)
gp1.setFromBMesh(bm0)

print(p1.getString())

