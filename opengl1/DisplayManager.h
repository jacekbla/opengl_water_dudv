#include "Utility.h"
#include <chrono>
#include <ctime>
#include <iostream>

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

class DisplayManager
{
public:
	explicit DisplayManager();
	DisplayManager(int p_argc, char **p_argv);
	~DisplayManager();

	static void createDisplay();
	static void updateDisplay();
	static void closeDisplay();

	static unsigned int getWIDTH() { return _WIDTH; };
	static unsigned int getHEIGHT() { return _HEIGHT; };

	static std::chrono::duration<float> getFrameTimeSeconds();

private:
	const static char* _TITLE;
	const static unsigned int _WIDTH = 800;
	const static unsigned int _HEIGHT = 600;

	static std::chrono::time_point<std::chrono::system_clock> _start;
	static std::chrono::duration<float> _delta;
};

#endif DISPLAY_MANAGER_H