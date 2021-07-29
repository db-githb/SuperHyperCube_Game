//Fragment Shader Code
#version 420
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;

void main()
{
   	// ambient shading
	vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse shading
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(dirLight.direction-FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	

	// specular shading
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = dirLight.specular * (spec * material.specular);

    // combine results    
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
} 
