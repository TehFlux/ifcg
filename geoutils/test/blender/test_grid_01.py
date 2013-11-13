import IFObjectBase as ib
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo

# memory management
mm = ib.IFObject()

subDivsX = 10
subDivsY = 10
name = "Grid01"

cgm0 = cg.Mesh.grid(subDivsX, subDivsY)
mm.addLocalRef(cgm0)

gm0 = bgm.Mesh(name + "M", cgm0)
gm0.createBMesh(None, False, False)
o0 = bgo.Object(name, gm0)
o0.createBObject()

