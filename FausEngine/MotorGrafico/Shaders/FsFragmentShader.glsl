#version 330 core

#define MAX_POINT_LIGHTS 50
#define MAX_SPOT_LIGHTS 50

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 fragColor;

struct Light{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;

	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	Light base;
	
	vec3 position;
	vec3 direction;
	float cosInnerCone;
	float cosOuterCone;

	float constant;
	float linear;
	float exponent;
};

struct Material 
{
    vec3 ambient;
    vec3 specular;
    float shininess;
	sampler2D texture;
};

uniform DirectionalLight directionalLight;
uniform int pointLightCounter;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int spotLightCounter;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;
uniform vec3 eyePos;

uniform bool lit;

uniform vec3 color;
uniform bool useTexture;





//=====================Directional Light Calculation==========================
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 eyePos)
{
	vec3 lightDir = normalize(-light.direction);  // direccion desde el fragment a la luz

	// Diffuse 
    float Normal_Dot_Light = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.base.diffuse * Normal_Dot_Light * vec3(texture(material.texture, TexCoord));
    
     // Specular
	vec3 Dir_Eye_to_light = normalize(lightDir + eyePos);
	float Normal_dot_dirEL = max(dot(normal, Dir_Eye_to_light), 0.0f);
	vec3 specular = light.base.specular * material.specular * pow(Normal_dot_dirEL, material.shininess);

	return (diffuse + specular);
}

//=====================Point Light Calculation==========================
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 eyePos)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse 
    float Normal_Dot_Light = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.base.diffuse * Normal_Dot_Light * vec3(texture(material.texture, TexCoord));
     // Specular 
	vec3 Dir_Eye_to_light = normalize(lightDir + eyePos);
	float Normal_dot_dirEL = max(dot(normal, Dir_Eye_to_light), 0.0f);
	vec3 specular = light.base.specular * material.specular * pow(Normal_dot_dirEL, material.shininess);

	// Attenuation
	float d = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));

	diffuse *= attenuation;
	specular *= attenuation;
	
	return (diffuse + specular);
}

//=====================Spot Light Calculation==========================
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 eyePos)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 spotDir  = normalize(light.direction);

	float cosDir = dot(-lightDir, spotDir);  
	//float spotIntensity = smoothstep(light.cosOuterCone, light.cosInnerCone, cosDir);
	float spotIntensity = smoothstep(0.93f, 0.96f, cosDir);
	// Diffuse 
    float Normal_Dot_Light = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.base.diffuse * Normal_Dot_Light * vec3(texture(material.texture, TexCoord));
     // Specular
	vec3 Dir_Eye_to_light = normalize(lightDir + eyePos);
	float Normal_dot_dirEL = max(dot(normal, Dir_Eye_to_light), 0.0f);
	vec3 specular = light.base.specular * material.specular * pow(Normal_dot_dirEL, material.shininess);

	// Attenuation 1 / c + l * d + exp * d2
	float d = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));

	diffuse *= attenuation * spotIntensity;
	specular *= attenuation * spotIntensity;
	
	return (diffuse + specular);
}

//================================MAIN===============================
void main()
{ 
	if(lit)
	{
		vec3 normal = normalize(Normal);  
		vec3 viewDir = normalize(eyePos - FragPos);

		// Ambient 
		vec3 ambient = vec3(0.0f);
		for(int i = 0; i < spotLightCounter; i++)
			ambient = spotLights[i].base.ambient * material.ambient * vec3(texture(material.texture, TexCoord))*directionalLight.base.ambient;
		
		vec3 outColor = vec3(0.0f);	

		//Directional light
		outColor += calcDirectionalLight(directionalLight, normal, viewDir);
		
		//Pointlight
		for(int i = 0; i < pointLightCounter; i++)
			outColor += calcPointLight(pointLights[i], normal, FragPos, viewDir);  
		
		//Spotlight
		for(int i = 0; i < spotLightCounter; i++)
			outColor += calcSpotLight(spotLights[i], normal, FragPos, viewDir);

		fragColor = vec4(ambient + outColor, 1.0f)* vec4(color,1.0f);
	}else{
	    if(useTexture)
			fragColor = vec4(color, 1.0f)* vec4(vec3(texture(material.texture, TexCoord)),1.0f);
		else
			fragColor = vec4(color, 1.0f);
	}
	
}