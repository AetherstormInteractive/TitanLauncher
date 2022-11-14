// TitanLauncher.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <nlohmann/json.hpp>

class TitanLauncher
{
public:
	void Setup();
	void Run();
private:
	GLFWwindow* window;
};

// TODO: Reference additional headers your program requires here.
