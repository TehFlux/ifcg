import IFObjectBase as ib
import Altjira as ai
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Data as bgd
import BGeoUtils.Object as bgo
import math as m

# memory management
mm = ib.IFObject()

name0 = "Fiber01"
aSubDivs0 = 12
lSubDivs0 = 20
length0 = 5.
radius0 = 0.2

gm0 = cg.Mesh.fiber(aSubDivs0, lSubDivs0, length0, radius0)
mm.addLocalRef(gm0)

gp0 = bgd.Mesh(name0 + "M_0", gm0)
bm0 = gp0.createBMesh(None)
o0 = bgo.Object(name0, gp0)
o0.createBObject()

