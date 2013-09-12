import IFObjectBase as ib
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo

inFile0 = 'test/meshes/colorcube01.xml'
#name = "ColorCube01"

# memory management
mm = ib.IFObject()

cgm0 = cg.Mesh.create()
mm.addLocalRef(cgm0)

cgm0.loadFromXMLFile(inFile0)
name = cgm0.getID()
print(cgm0.getString())

gm0 = bgm.Mesh(name + "M", cgm0)
gm0.createBMesh(None, True, True)
o0 = bgo.Object(name, gm0)
o0.createBObject()

