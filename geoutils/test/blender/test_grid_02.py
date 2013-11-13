import IFObjectBase as ib
import Altjira as ai
import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Mesh as bgm
import BGeoUtils.Object as bgo
import math as m

# memory management
mm = ib.IFObject()

subDivsX = 200
subDivsY = 200
scale = [10., 10., 4.]
name = "Grid01"
c0 = ai.Color.RED
c1 = ai.Color.BLUE
c2 = ai.Color.GREEN
c3 = ai.Color.MAGENTA

def f(x, y, sigma = 0.25):
    return m.exp(-(x*x + y*y) / sigma**2)

cgm0 = cg.Mesh.grid(subDivsX, subDivsY)
mm.addLocalRef(cgm0)

for i in range(0, subDivsY + 1):
    for j in range(0, subDivsX + 1):
        v = cgm0.getVertex(j + i * (subDivsX + 1))
        v.setZ(f(v.getX(), v.getY()))

S = cg.Matrix4.scale(*scale)
cgm0.transform(S)
cgm0.applyTransform()

cb0 = ai.ColorBand.heat()
mm.addLocalRef(cb0)

vs0 = cg.VectorSet.create()
mm.addLocalRef(vs0)
for i in range(0, subDivsY + 1):
    for j in range(0, subDivsX + 1):
        v = cgm0.getVertex(j + i * (subDivsX + 1))
        c = cb0(v.getZ() / scale[2])
        #print("  Adding color: (%d, %d) (%s)" 
        #    % (i, j, c.getValueString()))
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

