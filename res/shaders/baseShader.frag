//Fragment Shader Code
#version 420
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct PointLight {
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Material material;
uniform PointLight pointLight;
uniform vec3 viewPos;
uniform vec3 colour;
uniform int textureOn;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{	

	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos-FragPos);
	
	vec3 result = vec3(0.0, 0.0, 0.0);
	
	// Point light 
	result += CalcPointLight(pointLight, norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0);
};

vec3 CalcPointLight (PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 0.5; //1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));	

	vec3 ambient = vec3(0.0f,0.0f,0.0f);
	vec3 diffuse = vec3(0.0f,0.0f,0.0f);
	vec3 specular= vec3(0.0f,0.0f,0.0f);


	if (textureOn == 1){
		// combine results
		 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
		 diffuse = light.diffuse * diff *vec3(texture(material.diffuse, TexCoords));
		 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	}else{
		ambient = light.ambient * colour;
		diffuse = light.diffuse * diff * colour;
		specular = light.specular * spec * colour;
	}

	
	ambient *= attenuation;
	diffuse *= attenuation;
	// no attentuation for specular to ensure shininess from a far distance
	//specular *= attenuation;

	return (ambient+ diffuse + specular);
}