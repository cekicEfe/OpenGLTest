#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 Colour;

uniform sampler2D texture_diffuse1;
// uniform bool hasTexture;

void main()
{
    // if(hasTexture)
        FragColor = texture(texture_diffuse1, TexCoords);
    // else
        // FragColor = Colour;
}
