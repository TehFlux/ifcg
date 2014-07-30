#version 330
in vec4 color;
layout(location = 0) out vec4 fragData;
void main()
{
    fragData = color;
}
