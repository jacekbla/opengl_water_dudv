#include "ShaderProgram.h"
#include "Camera.h"
#include "Maths.h"

#ifndef WATER_SHADER_H
#define WATER_SHADER_H


class WaterShader : public ShaderProgram
{
public:
	explicit WaterShader() : ShaderProgram(_VERTEX_FILE, _FRAGMENT_FILE)
	{
		getAllUniformLocations();
		bindAttributes();
	};
	~WaterShader();

	virtual void bindAttributes() override;
	virtual void getAllUniformLocations() override;

	void connectTextureUnits();

	void loadProjectionMatrix(glm::mat4 &p_matrix);
	void loadViewMatrix(Camera &p_camera);
	void loadModelMatrix(glm::mat4 &p_matrix);
	void loadMoveFactor(float p_factor);

private:
	static const char* _VERTEX_FILE;
	static const char* _FRAGMENT_FILE;

	int _location_modelMatrix;
	int _location_viewMatrix;
	int _location_projectionMatrix;
	int _location_reflectionTexture;
	int _location_refractionTexture;
	int _location_dudvMap;
	int _location_moveFactor;
	int _location_cameraPosition;
	int _location_depthMap;
};


#endif WATER_SHADER_H