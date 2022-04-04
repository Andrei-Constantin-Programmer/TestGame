using namespace std;
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Vertices of coordinates
GLfloat vertices[] =
{
//		COORDINATES						COLOURS				TEXTURE COORDS
	-0.5f, 0.0f,  0.5f,			0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,			0.83f, 0.70f, 0.44f,		5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,			0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,			0.83f, 0.70f, 0.44f,		5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,			0.92f, 0.86f, 0.76f,		2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
	//Initialise GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL is being used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a GLFW window object of width x height pixels, with the name "My Window"
	GLFWwindow* window = glfwCreateWindow(width, height, "Test Game", NULL, NULL);

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
	glViewport(0, 0, width, height);

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
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));
	 

	//Unbind the VAO, VBO and EBO (to prevent modification)
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	//Get the id of the uniform called "scale"
	GLuint uniId = glGetUniformLocation(shaderProgram.id, "scale");

	//Texture
	Texture block("dirt.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	block.textureUnit(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);


	// The main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Set background colour
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clear the back buffer and assign the new colour to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Tell OpenGL what shader program to use
		shaderProgram.Activate();

		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= (float)1 / 60)
		{
			rotation += 0.5f;
			prevTime = currentTime;
		}

		//Initialise matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		int modelLocation = glGetUniformLocation(shaderProgram.id, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		int viewLocation = glGetUniformLocation(shaderProgram.id, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		int projLocation = glGetUniformLocation(shaderProgram.id, "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));


		glUniform1f(uniId, 0.5f);
		block.Bind();
		//Bind the VAO (so that OpenGL knows to use it)
		VAO.Bind();

		//Draw the triangle
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}



	//Delete the shader-related objects
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();

	block.Delete();

	shaderProgram.Delete();

	//Delete window
	glfwDestroyWindow(window);

	//Terminate GLFW
	glfwTerminate();
	
	return 0;
}