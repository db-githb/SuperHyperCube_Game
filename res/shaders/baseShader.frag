//Fragment Shader Code
#version 420
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	//sampler2D specular;
	//float shininess;
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
uniform samplerCube depthMap;
uniform float far_plane;
uniform bool shadows;

uniform vec3 colour;
uniform bool textureOn;
uniform bool borderOn;
uniform float specBias;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec3 fragPos);

void main()
{	
	vec3 color = textureOn ? texture(material.diffuse, TexCoords).rgb : colour;

    vec3 normal = normalize(Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(pointLight.position - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular =  spec * lightColor * specBias;    
    // calculate shadow
    float shadow = shadows ? ShadowCalculation(FragPos) : 0.0;                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;   
	

	vec2 uv = abs(TexCoords - 0.5) * 2.0;
	uv = pow(uv, vec2(10)) - 0.3;
	
	float c = clamp(uv.x + uv.y, 0.0, 1.0) * 10.0;
	if(c > 0 && borderOn)
		FragColor = vec4(lighting * c * 4, 1.0);
	else
		FragColor = vec4(lighting, 1.0);

    
};

float ShadowCalculation(vec3 fragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - pointLight.position;
    // ise the fragment to light vector to sample from the depth map    
    float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;    
    // display closestDepth as debug (to visualize depth cubemap)
	//FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    return shadow;
}
/*
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
*/
