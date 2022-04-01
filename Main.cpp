using namespace std;
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	//Initialise GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL is being used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a GLFW window object of 800x800 pixels, with the name "My Window"
	GLFWwindow* window = glfwCreateWindow(800, 800, "My Window", NULL, NULL);
	//Check if the window failed to be created
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	//Introduce the current window into the current context
	glfwMakeContextCurrent(window);

	//Load Glad to configure OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the window
	glViewport(0, 0, 800, 800);

	//Set colour
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//Clear buffer and assign the new colour
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// The main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Take care of all GLFW events
		glfwPollEvents();
	}


	//Delete window
	glfwDestroyWindow(window);

	//Terminate GLFW
	glfwTerminate();
	
	return 0;
}