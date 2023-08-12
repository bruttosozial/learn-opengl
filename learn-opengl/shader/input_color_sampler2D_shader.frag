
#version 330 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float amount;

void main()
{
    vec2 texCoordFlipped = vec2(TexCoord.x * -1, TexCoord.y);
    FragColor = mix(texture(texture1, TexCoord / 2), texture(texture2, texCoordFlipped), amount);
} 