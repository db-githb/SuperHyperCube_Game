//Fragment Shader Code
#version 420
out vec4 FragColor;

struct DirLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform DirLight dirLight;
uniform vec3 viewPos;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{	
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos-FragPos);
	
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	
	FragColor = vec4(result, 1.0);
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	
	// combine results
	vec3 ambient = light.ambient;
	
	vec3 diffuse = light.diffuse * diff;
	
	return (ambient + diffuse);
};