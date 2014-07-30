#version 330
const int numLights = 1;
uniform mat4 cgMVPMatrix;
uniform mat3 cgNormalMatrix;
uniform vec3 cgLightPos[numLights];
layout(location = 0) in vec3 cgVertex;
layout(location = 1) in vec4 cgEmitColor;
layout(location = 2) in vec4 cgDiffuseColor;
layout(location = 3) in vec3 cgNormal;
layout(location = 4) in vec4 cgMultiTexCoord0;
smooth out vec4 emitColor;
smooth out vec4 diffuseColor;
smooth out vec3 lightDir[numLights];
smooth out vec3 normalVS;
smooth out vec3 normalOS;
smooth out vec4 texCoord0;
void main()
{
    emitColor = cgEmitColor;
    diffuseColor = cgDiffuseColor;
    normalVS = cgNormalMatrix * cgNormal;
    normalOS = cgNormal;
    texCoord0 = cgMultiTexCoord0;
    for (int i = 0; i < numLights; i++)
        lightDir[i] = cgLightPos[i] - cgVertex;
    gl_Position = cgMVPMatrix * vec4(cgVertex, 1);
}