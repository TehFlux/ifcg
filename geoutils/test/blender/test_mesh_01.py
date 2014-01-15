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

name0 = "Cylinder01"

cyl0 = cg.Mesh.cylinder(10, 5., 0.2)
mm.addLocalRef(cyl0)

cm0 = bgd.Mesh(name0 + "_M", cyl0)
cm0.createBMesh(None)
co0 = bgo.PointingObject(name0 + "_0", cm0)
bo0 = co0.createBObject()

#co0.setScale([1., 1., 1.])
co0.setDirection(cg.Vector3(0., 0., 1.))
co0.setBasePoint(cg.Vector3(0., 0., 0.))

bo0.keyframe_insert(data_path = "scale", frame = 0)
bo0.keyframe_insert(data_path = "location", frame = 0)
bo0.keyframe_insert(data_path = "rotation_euler", frame = 0)

co0.setScale([2., 2., 2.])
co0.setDirection(cg.Vector3(0., 1., 1.))
co0.setBasePoint(cg.Vector3(0., 0., 0.))

bo0.keyframe_insert(data_path = "scale", frame = 20)
bo0.keyframe_insert(data_path = "location", frame = 20)
bo0.keyframe_insert(data_path = "rotation_euler", frame = 20)

