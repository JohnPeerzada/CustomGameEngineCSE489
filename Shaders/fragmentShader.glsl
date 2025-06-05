// Targeting version 4.6 of GLSL. If the compiler does not support 4.5 it will cause an error.
#version 460 core

in vec3 worldPos;
in vec3 worldNorm;
in vec2 texCoord0;
in mat3 TBN;
out vec4 fragmentColor;

const float gamma = 2.2;

const int MaxLights = 16;

// Structure for holding general light properties
struct GeneralLight
{
	vec3 ambientColor;		// ambient color of the light
	vec3 diffuseColor;		// diffuse color of the light
	vec3 specularColor;		// specular color of the light

	// Either the position or direction
	// if w = 0 then the light is directional and direction specified 
	// is the negative of the direction the light is shinning
	// if w = 1 then the light is positional
	vec4 positionOrDirection;

	// Spotlight attributes
	vec3 spotDirection;		// the direction the cone of light is shinning    
	bool isSpot;				// 1 if the light is a spotlight  
	float spotCutoffCos;	// Cosine of the spot cutoff angle
	float spotExponent;		// For gradual falloff near cone edge

	// Attenuation coefficients
	float constant;
	float linear;
	float quadratic;

	bool enabled;			// true if light is "on"

};

layout(shared) uniform LightBlock
{
	GeneralLight lights[MaxLights];
};

layout(shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};


struct Material
{
	vec3 ambientMatColor;
	vec3 diffuseMatColor;
	vec3 specularMatColor;
	vec3 emmissiveMatColor;
	float specularExp;
	float alpha;
	int textureMode;
	bool diffuseTextureEnabled;
	bool specularTextureEnabled;
	bool normalMapTextureEnabled;
};

layout(shared) uniform MaterialBlock
{
	Material object;
};

//layout(shared) uniform FogBlock
//{
//	vec4 fogColor;
//	float fogEnd;
//	float fogStart;
//	float fogDensity;
//	unsigned int fogMode; // 0 no fog, 1 linear, 2 exponential, 3 exponential two
//}

layout(binding = 0) uniform sampler2D diffuseSampler;
layout(binding = 1) uniform sampler2D specularSampler;
layout(binding = 2) uniform sampler2D normalMapSampler;

void main()
{
	vec3 totalColor = object.emmissiveMatColor;

	vec3 ambientColor = object.ambientMatColor;

	vec3 diffuseColor = object.diffuseMatColor;

	float alpha = object.alpha;

	vec3 specularColor = object.specularMatColor;

	vec3 fragWorldNormal = normalize(worldNorm);

	if (object.normalMapTextureEnabled) {

		vec3 normal = texture(normalMapSampler, texCoord0).xyz;
		normal = normalize(normal * 2.0f - 1.0f);
		fragWorldNormal = normalize(TBN * normal);
	}

	if(object.textureMode != 0 && object.diffuseTextureEnabled) {

		vec4 diffuseTextureColor = texture( diffuseSampler, texCoord0 );

		diffuseColor = diffuseTextureColor.rgb;

		if(diffuseTextureColor.a < alpha) {
			alpha = diffuseTextureColor.a;
		}
		ambientColor = diffuseColor;
	 }

	 if(object.textureMode != 0 && object.specularTextureEnabled) {

		specularColor = texture( specularSampler, texCoord0 ).rgb;
	 }

//	 if(object.textureMode != 1) {
//
//		// Implement local illumination
//		// TODO
//
//		fragmentColor = vec4(totalColor, alpha);
//
//	}
//	else { // No lighting calculations applied

		fragmentColor = vec4(diffuseColor, alpha);
//	}

}