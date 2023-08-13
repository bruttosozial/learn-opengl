
#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 location;

void main()
{
    gl_Position = vec4(aPos.xyz, 1.0);
    location = vec4(aPos.xyz, 1.0);
}