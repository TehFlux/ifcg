import IFObjectBase as ib
import Altjira as ai
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo

# memory management
mm = ib.IFObject()

subDivsX = 100
subDivsY = 100
name = "Grid01"
c0 = ai.Color.RED
c1 = ai.Color.BLUE
c2 = ai.Color.GREEN
c3 = ai.Color.MAGENTA

cgm0 = cg.Mesh.grid(subDivsX, subDivsY)
S = cg.Matrix4.scale(10., 10., 1.)
cgm0.transform(S)
cgm0.applyTransform()
mm.addLocalRef(cgm0)

vs0 = cg.VectorSet.create()
mm.addLocalRef(vs0)
for i in range(0, subDivsY + 1):
    cy0 = ai.Color.interpolate(c0, c1, i / subDivsY)
    cy1 = ai.Color.interpolate(c2, c3, i / subDivsY)
    for j in range(0, subDivsX + 1):
        c = ai.Color.interpolate(cy0, cy1, j / subDivsX)
        print("  Adding color: (%d, %d) (%s)" 
            % (i, j, c.getValueString()))
        vs0.addVector(cg.Vector3.create(
            c.getRed(), c.getGreen(), c.getBlue()))

for i in range(0, cgm0.getNumFaces()):
    f0 = cgm0.getFace(i)
    vcs0 = f0.addFaceData(cg.FaceData.TYPE_VERTEX_COLOR)
    for j in range(0, f0.getNumVertices()):
        vc0 = vs0.getVector(f0.getVertex(j))
        vcs0.addVector(vc0.copy())

gm0 = bgm.Mesh(name + "M", cgm0)
gm0.createBMesh(None, False, True)
o0 = bgo.Object(name, gm0)
o0.createBObject()

