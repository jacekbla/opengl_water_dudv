#include "ShaderProgram.h"
#include "Camera.h"
#include "Maths.h"
#include "Light.h"

#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

class StaticShader : public ShaderProgram
{
public:
	explicit StaticShader() : ShaderProgram(_VERTEX_FILE, _FRAGMENT_FILE) 
	{
		getAllUniformLocations();
		bindAttributes();
	};
	~StaticShader();

	virtual void bindAttributes() override;
	virtual void getAllUniformLocations() override;

	void loadTransformMatrix(glm::mat4 &p_matrix);
	void loadProjectionMatrix(glm::mat4 &p_matrix);
	void loadViewMatrix(Camera &p_camera);
	void loadLight(Light &p_light);
	void loadShineVariables(float p_damper, float p_reflectivity);
	void loadClipPlane(glm::fvec4 p_plane);

	void loadMVP(glm::mat4 &p_matrix);

private:
	static const char* _VERTEX_FILE;
	static const char* _FRAGMENT_FILE;
	int _location_MVP;
	int _location_transformMatrix;
	int _location_projectionMatrix;
	int _location_viewMatrix;
	int _location_lightPosition;
	int _location_lightColor;
	int _location_shineDamper;
	int _location_reflectivity;
	int _location_plane;
};

#endif STATIC_SHADER_H