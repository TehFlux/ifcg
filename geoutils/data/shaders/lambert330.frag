#version 330
const int numLights = 1;
uniform vec4 cgLightColor[numLights];
uniform vec4 cgLightParam[numLights];
in vec4 emitColor;
in vec4 diffuseColor;
in vec3 lightDir[numLights];
in vec3 normalVS;
in vec3 normalOS;
layout(location = 0) out vec4 fragData;
void main()
{
    vec3 n0 = normalize(normalOS);
    vec4 dc = vec4(0);
    for (int i = 0; i < numLights; i++)
    {
        vec3 ld0 = lightDir[i];
        vec3 ldn0 = normalize(ld0);
        float ldl0 = length(ld0);
        float intensity0 = cgLightParam[i].x;
        float foe0 = cgLightParam[i].y;
        float fos0 = cgLightParam[i].z;
        float c0 = 1.;
        if (foe0 != 0)
            c0 = 1. / pow(fos0 * ldl0, foe0);
        vec4 lc = vec4(c0 * intensity0 * dot(n0, ldn0) 
            * cgLightColor[i].rgb * diffuseColor.rgb, 1);
        dc += lc;
    }
    fragData = emitColor + dc;
}
