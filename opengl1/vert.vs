#version 430 

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoords;
layout(location = 3) in vec3 vNormal;
//out vec3 vColorFrag;
out vec2 vTexCoordsFrag;
out vec3 vSurfaceNormal;
out vec3 vToLightVector;
out vec3 vToCameraVector;

uniform mat4 MVP;
uniform mat4 transformMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

uniform vec4 plane;

void main() 
{
	vec4 worldPosition = transformMatrix * vec4(vPosition, 1.0);

	gl_ClipDistance[0] = dot(worldPosition, plane);

	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	//vColorFrag = vColor;
	vTexCoordsFrag = vTexCoords;

	vSurfaceNormal = (transformMatrix * vec4(vNormal, 0.0)).xyz;
	vToLightVector = worldPosition.xyz - lightPosition;					//?
	vToCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}
