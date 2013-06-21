import bmesh

m0 = bpy.data.meshes.get('Cube')
bm0 = bmesh.new()
bm0.from_mesh(m0)
f0 = bm0.faces[0]
uv0 = bm0.loops.layers.uv[0]
l0 = f0.loops[0]
l0[uv0].uv

import CGeoUtils as cg
import BGeoUtils as bg
import BGeoUtils.Object as bgo

p0 = cg.Vector3.ZERO
d0 = cg.Vector3.E_SUM

a0 = bgo.Arrow()
a0.createBObject()
a0.setDirection(d0)
a0.setBasePoint(p0)
