#version 430 

//in vec3 vColorFrag;
in vec2 vTexCoordsFrag;
in vec3 vSurfaceNormal;
in vec3 vToLightVector;
in vec3 vToCameraVector;

out vec4 fColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;

void main()
{
	vec3 unitNormal = normalize(vSurfaceNormal);
	vec3 unitToLightVector = normalize(vToLightVector);

	float nDotl = dot(unitNormal, unitToLightVector);
	float brightness = max(nDotl, 0.1);
	vec3 diffuse = brightness * lightColor;

	vec3 unitToCameraVector = normalize(vToCameraVector);
	vec3 lightDirection = -unitToLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float specularFactor = dot(reflectedLightDirection, unitToCameraVector);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, shineDamper);
	vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

	//fColor = vec4(vColorFrag, 1.0);
	fColor = vec4(diffuse, 1.0) * texture(textureSampler, vTexCoordsFrag) + vec4(finalSpecular, 1.0);
}
