import IFObjectBase as ib
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm

outFile0 = 'temp/bmeshtest02_mesh.xml'

# memory management
mm = ib.IFObject()

cgm0 = cg.Mesh.create()
mm.addLocalRef(cgm0)

bm0 = bpy.data.meshes.get('Cube')
gm0 = bgm.Mesh("Cube01", cgm0)
gm0.setFromBMesh(bm0)

xml0 = cgm0.getXML0()
print(xml0)

f = open(outFile0, 'w')
f.write(xml0)
f.close()
