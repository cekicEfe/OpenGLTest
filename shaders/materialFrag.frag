#version 330 core

struct tLight
{
	vec3 light_color;
	vec3 light_pos;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct tMaterial {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 Color;

uniform tMaterial material;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;
uniform vec3 viewPos;

void main()
{    
    // ambient
    vec3 ambient = lightColor * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}