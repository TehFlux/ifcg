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

gm0 = bgm.Polygon3(name + "M", p0)
gm0.createBMesh(None)
o0 = bgo.Object(name, gm0)
o0.createBObject()

