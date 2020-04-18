#version 430

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;

out vec4 out_Color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D depthMap;

uniform float moveFactor;

const float waveStrength = 0.01;
const float waterBlendDepth = 0.25;

void main(void) 
{
	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	float near = 0.1;
	float far = 1000.0f;
	float depth = texture(depthMap, refractTexCoords).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	float waterDepth = floorDistance - waterDistance;
	
	vec2 distorion1 = (texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 2.0 - 1.0) * waveStrength;
	vec2 distorion2 = (texture(dudvMap, vec2(-textureCoords.x + moveFactor, textureCoords.y + moveFactor)).rg * 2.0 - 1.0) * waveStrength;
	vec2 totalDistortion = (distorion1 + distorion2) * clamp(waterDepth/(waterBlendDepth * 4), 0.0, 1.0);
	
	reflectTexCoords += totalDistortion;
	refractTexCoords += totalDistortion;
	
	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);

	vec4 reflectColor = texture(reflectionTexture, reflectTexCoords);
	vec4 refractColor = texture(refractionTexture, refractTexCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));
	refractiveFactor = pow(refractiveFactor, 0.8);

	out_Color = mix(reflectColor, refractColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0, 0.3, 0.5, 1.0), 0.2);
	out_Color.a = clamp(waterDepth/waterBlendDepth, 0.0, 1.0);
}