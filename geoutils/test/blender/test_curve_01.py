import bpy

name = "Curve02"

c0 = bpy.data.curves.new(name + '_C', type = 'CURVE')
s0 = c0.splines.new(type = 'BEZIER')
s0.bezier_points.add(1)
p0 = s0.bezier_points[0]
p0.co = [-1., 2., 0.]
p0.handle_left_type = 'ALIGNED'
p0.handle_right_type = 'FREE'
p0.handle_right = [-2.5, 3., 0.]
p0 = s0.bezier_points[1]
p0.co = [4., -1., 0.]
p0.handle_left_type = 'FREE'
p0.handle_right_type = 'ALIGNED'
p0.handle_left = [2.5, -1.5, 0.]

o0 = bpy.data.objects.new(name, c0)

o1 = bpy.context.scene.objects.link(o0)

