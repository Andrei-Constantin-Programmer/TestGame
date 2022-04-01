using namespace std;
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{
	//				COORDINATES								COLOURS
	-0.50f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.80f, 0.30f, 0.02f,// Lower left corner
	 0.50f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.80f, 0.30f, 0.02f,// Lower right corner
	 0.00f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    1.00f, 0.60f, 0.32f,// Upper corner
	-0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,    0.90f, 0.40f, 0.17f,// Inner left
	 0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,    0.50f, 0.40f, 0.17f,// Inner right
	 0.00f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.80f, 0.30f, 0.02f// Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};


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

	//Generate the shader object using the default.vert and default.frag files
	Shader shaderProgram("default.vert", "default.frag");

	//Generate the VAO and bind it
	VAO VAO;
	VAO.Bind();

	//Generate the VBO and link it to the vertices
	VBO VBO(vertices, sizeof(vertices));
	
	//Generate the EBO and link it to the indices
	EBO EBO(indices, sizeof(indices));

	//Link VBO to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 6*sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 6*sizeof(float), (void*)(3*sizeof(float)));
	 

	//Unbind the VAO, VBO and EBO (to prevent modification)
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	//Get the id of the uniform called "scale"
	GLuint uniId = glGetUniformLocation(shaderProgram.id, "scale");

	// The main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Set background colour
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clear the back buffer and assign the new colour to it
		glClear(GL_COLOR_BUFFER_BIT);

		//Tell OpenGL what shader program to use
		shaderProgram.Activate();

		glUniform1f(uniId, 0.25f);
		//Bind the VAO (so that OpenGL knows to use it)
		VAO.Bind();

		//Draw the triangle
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}



	//Delete the shader-related objects
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();

	shaderProgram.Delete();

	//Delete window
	glfwDestroyWindow(window);

	//Terminate GLFW
	glfwTerminate();
	
	return 0;
}