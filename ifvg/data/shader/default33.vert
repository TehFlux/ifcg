#version 330

uniform mat4 ifvgMVPMatrix;
uniform mat3 ifvgNormalMatrix;

in vec4 ifvgVertex;
in vec4 ifvgColor;
in vec3 ifvgNormal;
in vec4 ifvgMultiTexCoord0;

smooth out vec4 color;
smooth out vec3 normal;
smooth out vec4 texCoord0;

void main()
{
    color = ifvgColor;
    normal = ifvgNormalMatrix * ifvgNormal;
    texCoord0 = ifvgMultiTexCoord0;
    gl_Position = ifvgMVPMatrix * ifvgVertex;
}
