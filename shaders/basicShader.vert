#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColour;

out vec2 TexCoords;
out vec4 Colour;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    Colour = aColour;
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0f); 
}
