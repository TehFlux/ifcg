import IFObjectBase as ib
import IFMapping as im
import Altjira as ai
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Data as bgd
import BGeoUtils.Object as bgo
import BGeoUtils.Material as bgm
import math as m

# memory management
mm = ib.IFObject()

def updateVectors(v0, v1, v2, a0, a1, a2):
    """Update the visualization for vectors v0, v1, v2."""
    a0.setDirection(v0)
    a1.setDirection(v1)
    a2.setDirection(v2)
    a0.setBasePoint(cg.Vector3.ZERO)
    a1.setBasePoint(cg.Vector3.ZERO)
    a2.setBasePoint(cg.Vector3.ZERO)

def showSlerp(v0, v1, t, a0, a1, a2):
    """Visualize SLERP."""
    v2 = v0.slerp(v1, t)
    updateVectors(v0, v1, v2, a0, a1, a2)

#v0 = cg.Vector3.create(1., 0., 0.)
#v1 = cg.Vector3.create(0.2, 1., 0.)
v0 = cg.Vector3.create(1., 2., 3.)
v1 = cg.Vector3.create(-2., 1., 1.5)
v0.normalizeIP()
v1.normalizeIP()
mm.addLocalRef(v0)
mm.addLocalRef(v1)

t = 0.9
v2 = v0.slerp(v1, t)
l0 = v0.norm()
l1 = v1.norm()
l2 = v2.norm()

materials0 = bgm.MaterialMap.getDefault()
mat0 = materials0.getMaterial('Red')
mat1 = materials0.getMaterial('Blue')
mat2 = materials0.getMaterial('Green')

a0 = bgo.Arrow("V0_A", length = l0, create = True)
a1 = bgo.Arrow("V1_A", length = l1, create = True)
a2 = bgo.Arrow("V2_A", length = l2, create = True)
a0.setMaterial(mat0)
a1.setMaterial(mat1)
a2.setMaterial(mat2)

showSlerp(v0, v1, t, a0, a1, a2)
#updateVectors(v0, v1, v0.ortho(v1), a0, a1, a2)

