#include "WaterFrameBuffers.h"


const int WaterFrameBuffers::REFLECTION_WIDTH = 1280;
const int WaterFrameBuffers::_REFLECTION_HEIGHT = 720;
const int WaterFrameBuffers::REFRACTION_WIDTH = 1280;
const int WaterFrameBuffers::_REFRACTION_HEIGHT = 720;

WaterFrameBuffers::WaterFrameBuffers()
{
	initialiseReflectionFrameBuffer();
	initialiseRefractionFrameBuffer();
}


WaterFrameBuffers::~WaterFrameBuffers()
{
}

void WaterFrameBuffers::cleanUp()
{
	glFuncs::ref().glDeleteFramebuffers(1, &_reflectionFrameBuffer);
	glFuncs::ref().glDeleteFramebuffers(1, &_refractionFrameBuffer);
	glDeleteTextures(1, &_reflectionTexture);
	glDeleteTextures(1, &_refractionTexture);
	glDeleteTextures(1, &_refractionDepthTexture);
	glFuncs::ref().glDeleteRenderbuffers(1, &_reflectionDepthBuffer);
}

void WaterFrameBuffers::bindReflectionFrameBuffer()
{
	bindFrameBuffer(_reflectionFrameBuffer, REFLECTION_WIDTH, _REFLECTION_HEIGHT);
}

void WaterFrameBuffers::bindRefractionFrameBuffer()
{
	bindFrameBuffer(_refractionFrameBuffer, REFRACTION_WIDTH, _REFRACTION_HEIGHT);
}

void WaterFrameBuffers::unbindCurrentFrameBuffer()
{
	glFuncs::ref().glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, DisplayManager::getWIDTH(), DisplayManager::getHEIGHT());
}

int WaterFrameBuffers::getReflectionTexture() const
{
	return _reflectionTexture;
}

int WaterFrameBuffers::getRefractionTexture() const
{
	return _refractionTexture;
}

int WaterFrameBuffers::getRefractionDepthTexture() const
{
	return _refractionDepthTexture;
}

void WaterFrameBuffers::initialiseReflectionFrameBuffer()
{
	_reflectionFrameBuffer = createFrameBuffer();
	_reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, _REFLECTION_HEIGHT);
	_reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, _REFLECTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::initialiseRefractionFrameBuffer()
{
	_refractionFrameBuffer = createFrameBuffer();
	_refractionTexture = createTextureAttachment(REFRACTION_WIDTH, _REFRACTION_HEIGHT);
	_refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, _REFRACTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::bindFrameBuffer(int p_frameBuffer, int p_width, int p_height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glFuncs::ref().glBindFramebuffer(GL_FRAMEBUFFER, p_frameBuffer);
	glViewport(0, 0, p_width, p_height);
}

int WaterFrameBuffers::createFrameBuffer()
{
	GLuint frameBuffer = 0;
	glFuncs::ref().glGenFramebuffers(1, &frameBuffer);
	glFuncs::ref().glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frameBuffer;
}

int WaterFrameBuffers::createTextureAttachment(int p_width, int p_height)
{
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFuncs::ref().glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	return texture;
}

int WaterFrameBuffers::createDepthTextureAttachment(int p_width, int p_height)
{
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, p_width, p_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFuncs::ref().glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, texture, 0);
	return texture;
}

int WaterFrameBuffers::createDepthBufferAttachment(int p_width, int p_height)
{
	GLuint depthBuffer = 0;
	glFuncs::ref().glGenRenderbuffers(1, &depthBuffer);
	glFuncs::ref().glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glFuncs::ref().glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, p_width, p_height);
	glFuncs::ref().glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}
