#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 pass_Color;

void main()
{    
    FragColor = vec4(pass_Color, 1.0);
}
