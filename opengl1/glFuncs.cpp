#include "glFuncs.h"


glFuncs::glFuncs()
{
	init();
}

glFuncs& glFuncs::ref()
{
	static glFuncs instance;

	return instance;
}

void glFuncs::init()
{
	// pobranie numeru wersji biblioteki OpenGL
	const char * version = (char *)glGetString(GL_VERSION);
	printf("%s", version);
	if ((version[0] < '1') || ((version[0] == '1') && (version[2] < '5')) || (version[1] != '.')) {
		printf("Bledny format wersji OpenGL\n");
		exit(0);
	}
	else {
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)wglGetProcAddress("glPatchParameteri");
		glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
		glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
		glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");

		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glMapBuffer = (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBuffer");
		glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");

		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");

		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");


		glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
		glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
		glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
		glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
		glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
		glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
		glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
		glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
		glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)wglGetProcAddress("glFramebufferTexture");
		glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
		glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
		glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
		glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
		glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
		glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	}
}
