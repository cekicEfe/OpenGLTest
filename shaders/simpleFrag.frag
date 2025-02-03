#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 Colour;

uniform int light_count;
uniform vec3 light_positions[100];
uniform vec3 light_colors[100];

// uniform float ambient;
// uniform float diffuse;
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

