#include "DisplayManager.h"

const char* DisplayManager::_TITLE = "openGL";

std::chrono::time_point<std::chrono::system_clock> DisplayManager::_start = std::chrono::system_clock::now();
std::chrono::duration<float> DisplayManager::_delta = std::chrono::duration<float>(0.0f);

DisplayManager::DisplayManager(int p_argc, char **p_argv)
{
	glutInit(&p_argc, p_argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
}

DisplayManager::DisplayManager()
{
	glutInit(nullptr, nullptr);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
}

DisplayManager::~DisplayManager()
{
}

void DisplayManager::createDisplay()
{
	glutInitWindowSize(_WIDTH, _HEIGHT);
	glutCreateWindow(_TITLE);
	glViewport(0, 0, _WIDTH, _HEIGHT);

	DisplayManager::_start = std::chrono::system_clock::now();
}

void DisplayManager::updateDisplay()
{
	glutSwapBuffers();
	glutPostRedisplay();

	DisplayManager::_delta = std::chrono::system_clock::now() - _start;
	DisplayManager::_start = std::chrono::system_clock::now();
}

void DisplayManager::closeDisplay()
{
	
}

std::chrono::duration<float> DisplayManager::getFrameTimeSeconds()
{
	return _delta;
}

