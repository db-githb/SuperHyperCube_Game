//Fragment Shader Code

/*
 * Fragment shader class is adapted the learnOpenGL.com code repostitory on github: https://github.com/JoeyDeVries/LearnOpenGL
   License:
 * All code samples, unless explicitly stated otherwise, are licensed under the terms of the CC BY-NC 4.0 license as published by Creative Commons, either version 4 of the License, or (at your option) any later version.
 * Link to license:  https://github.com/JoeyDeVries/LearnOpenGL/blob/master/LICENSE.md
*/

// This shader adapts from an online resource for it's edge outline effect.
// Resource: Tron Shader by SketchPunkLabs on Youtube (Bonus edge outline feature)
// Link: https://www.youtube.com/watch?v=DI498yX-6XM&ab_channel=SketchpunkLabs
//
#version 420
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	//sampler2D specular;
	//float shininess;
};

struct PointLight {
	vec3 position;
	//vec3 ambient;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Material material;
uniform PointLight pointLight;
uniform vec3 viewPos;
uniform samplerCube depthMap;
uniform float far_plane;

uniform vec3 colour;
uniform bool textureOn;
uniform bool borderOn;
uniform float specBias;

uniform bool moonAmbient;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec3 fragPos);

void main()
{	
	vec3 color = textureOn ? texture(material.diffuse, TexCoords).rgb : colour;

    vec3 normal = normalize(Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;

	if(moonAmbient){
		//ambient = vec3(1.0, 1.0, 1.0);
	}
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
    float shadow = ShadowCalculation(FragPos);                      
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

	// bias and the shadow line are used to handle the shadow acne
    float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;   

    // display closestDepth as debug (to visualize depth cubemap)
	//FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    return shadow;
}