#version 330 core

/*
struct tMaterial
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct tLight
{
	vec3 light_color;
	vec3 light_pos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec4 Color;

uniform tMaterial material;
uniform bool hasTexture;
uniform float time;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main()
{   
    if(!hasTexture)
    {
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
  	
        // diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        vec4 modelColor = Color;
        vec4 result = vec4((ambient + diffuse),1.0) * modelColor;
        FragColor = result; // vec4(Color,1.0f);

    }else{
        // ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
  	
        // diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        vec4 modelColor = texture(texture_diffuse1, TexCoords);
        vec4 result = vec4((ambient + diffuse),1.0) * modelColor;
        FragColor = result; // vec4(Color,1.0f);
    }
}

*/

struct Light
{
	vec3 light_color;
	vec3 light_pos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform float time;
uniform int light_count;
uniform vec3 light_positions[100];
uniform vec3 light_colors[100];
uniform sampler2D texture_diffuse1;

void main()
{   
    float ambientStrength = 0.1;
    vec3 norm = normalize(Normal);
    vec4 modelColor = texture(texture_diffuse1, TexCoords);
    vec4 result = vec4(0.0f);
    
    for( int i = 0 ; i < light_count ; i++)
    {
        vec3 ambient = ambientStrength * light_colors[i]; 
        vec3 lightDir = normalize(light_positions[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * light_colors[i];
        result += vec4((ambient + diffuse),1.0) * modelColor ; 
    }
    
    FragColor = result ;
}

