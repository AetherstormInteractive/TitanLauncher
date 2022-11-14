// TitanLauncher.cpp : Defines the entry point for the application.
//

#include "TitanLauncher.h"

using namespace std;

void TitanLauncher::Setup()
{
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, false);
	window = glfwCreateWindow(1280, 720, "Titan Launcher", NULL, NULL);
}

void TitanLauncher::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	cout << "Hello Titan." << endl;
	TitanLauncher* launcher = new TitanLauncher();

	launcher->Setup();
	launcher->Run();
	return 0;
}
