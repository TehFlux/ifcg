import IFObjectBase as ib
import Altjira as ai
import CGeoUtils as cg
import CIFPhySim as cifp
import BGeoUtils as bg
import BGeoUtils.Data as bgd
import BGeoUtils.Object as bgo
import bpy

# memory management
mm = ib.IFObject()

name = "Fiber01"

p0 = cg.Polygon3.create()
mm.addLocalRef(p0)

pm0 = bgd.Polygon3(name + "M", p0)
bm0 = bpy.data.meshes.get(pm0.name)
pm0.setFromBMesh(bm0)

print(p0.getString())

pm1 = bgd.Polygon3(name + "M_0", p0)
pm1.createBMesh(None)
o1 = bgo.Object(name + "_0", pm1)
o1.createBObject()

