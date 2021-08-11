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
#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

struct Spotlight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

uniform Spotlight spotlight;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform sampler2D diffuseTexture;
uniform sampler2D depthMap;

uniform vec3 colour;
uniform bool isTextured;

uniform bool spotlightOn;
uniform bool directionalLightOn;
uniform bool ambientLightOn;
vec3 lightColor;

float ShadowCalculation(vec4 fragPos,float bias);
vec3 CalcSpotLight(Spotlight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{	
    lightColor = vec3(0.4);

	vec3 color = isTextured ? texture(diffuseTexture, TexCoords).rgb : colour;

    vec3 normal = normalize(Normal);
    
    // ambient
   
    vec3 ambient = ambientLightOn ?  0.5 * color : vec3(0);
    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular =  spec * lightColor;    
    // calculate shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = ShadowCalculation(FragPosLightSpace,bias);              
    
    
    vec3 lighting = directionalLightOn ? (ambient + (1.0 - shadow) * (diffuse + specular)) * color : ambient * color;   
	lighting = spotlightOn ? lighting + 50 * CalcSpotLight(spotlight, normal, FragPos, viewDir) : lighting;
	FragColor = vec4(lighting, 1.0);
};

float ShadowCalculation(vec4 fragPosLightSpace,float bias)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(depthMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
     
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; 
    
    if(projCoords.z > 1.0)
        shadow = 0.0;
    return shadow;
}

vec3 CalcSpotLight(Spotlight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * lightColor;
    vec3 diffuse = light.diffuse * diff * lightColor;
    vec3 specular = light.specular * spec * lightColor;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}