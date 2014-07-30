#version 330
uniform mat4 cgMVPMatrix;
uniform mat3 cgNormalMatrix;
layout(location = 0) in vec3 cgVertex;
layout(location = 1) in vec4 cgColor;
layout(location = 2) in vec3 cgNormal;
layout(location = 3) in vec4 cgMultiTexCoord0;
smooth out vec4 color;
smooth out vec3 normal;
smooth out vec4 texCoord0;
void main()
{
    color = cgColor;
    normal = cgNormalMatrix * cgNormal;
    texCoord0 = cgMultiTexCoord0;
    gl_Position = cgMVPMatrix * vec4(cgVertex, 1);
}
