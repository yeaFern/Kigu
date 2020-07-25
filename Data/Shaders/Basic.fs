#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 pass_TexCoords;
in vec4 pass_Color;

uniform sampler2D u_SpriteAtlas;

void main()
{    
    FragColor = pass_Color;
    FragColor = texture(u_SpriteAtlas, pass_TexCoords) * pass_Color;

    if(FragColor.a == 0)
    {
        discard;
    }
}
