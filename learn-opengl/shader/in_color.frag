#version 330 core

out vec4 FragColor;
in vec4 location;

void main()
{
    FragColor = location;
} 