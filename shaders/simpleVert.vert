#version 330 core
/*
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 InstanceMatrix;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //Color = aColor;
    Normal = aNormal;
    TexCoords = aTexCoords;    
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * InstanceMatrix *  vec4(aPos, 1.0);
}

*/

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 4) in mat4 aInstanceMatrix;// Consumes to 7

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    Normal = aNormal;
    TexCoords = aTexCoords;
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f);
}
