#version 330
const int numLights = 1;
uniform vec3 cgLightColor[numLights];
in vec4 emitColor;
in vec4 diffuseColor;
in vec4 lightDir[numLights];
in vec3 normal;
layout(location = 0) out vec4 fragData;
void main()
{
    vec4 dc(0);
    for (int i = 0; i < numLights; i++)
    {
        vec4 lc = vec4(dot(normal, normalize(lightDir[i])) 
            * cgLightColor.rgb * diffuseColor.rgb, 1);
        dc += lc;
    }
    fragData = emitColor + dc;
}
