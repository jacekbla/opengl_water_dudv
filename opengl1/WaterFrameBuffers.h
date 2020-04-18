#include "glFuncs.h"
#include "DisplayManager.h"

#ifndef WATER_FRAME_BUFFERS_H
#define WATER_FRAME_BUFFERS_H


class WaterFrameBuffers
{
public:
	explicit WaterFrameBuffers();
	~WaterFrameBuffers();

	void cleanUp();
	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer();
	int getReflectionTexture() const;
	int getRefractionTexture() const;
	int getRefractionDepthTexture() const;


private:
	static const int _REFLECTION_HEIGHT;
	static const int _REFRACTION_HEIGHT;

	GLuint _reflectionFrameBuffer;
	GLuint _reflectionTexture;
	GLuint _reflectionDepthBuffer;
	GLuint _refractionFrameBuffer;
	GLuint _refractionTexture;
	GLuint _refractionDepthTexture;

	void initialiseReflectionFrameBuffer();
	void initialiseRefractionFrameBuffer();
	void bindFrameBuffer(int p_frameBuffer, int p_width, int p_height);
	int createFrameBuffer();
	int createTextureAttachment(int p_width, int p_height);
	int createDepthTextureAttachment(int p_width, int p_height);
	int createDepthBufferAttachment(int p_width, int p_height);

protected:
	static const int REFLECTION_WIDTH;
	static const int REFRACTION_WIDTH;

};


#endif WATER_FRAME_BUFFERS_H