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
#include "Camera.h"

// Vertices of coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};


// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,	// Bottom side
	0, 2, 3,	// Bottom side
	4, 6, 5,	// Left side
	7, 9, 8,	// Non-facing side
	10, 12, 11, // Right side
	13, 15, 14	// Facing side
};

GLfloat lightVertices[] =
{
	-0.10f, -0.10f,  0.10f,
	-0.10f, -0.10f, -0.10f,
	 0.10f, -0.10f, -0.10f,
	 0.10f, -0.10f,  0.10f,
	-0.10f,  0.10f,  0.10f,
	-0.10f,  0.10f, -0.10f,
	 0.10f,  0.10f, -0.10f,
	 0.10f,  0.10f,  0.10f,
};


GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	VAO defaultVAO;
	defaultVAO.Bind();

	//Generate the VBO and link it to the vertices
	VBO defaultVBO(vertices, sizeof(vertices));
	
	//Generate the EBO and link it to the indices
	EBO defaultEBO(indices, sizeof(indices));

	//Link VBO to VAO
	defaultVAO.LinkAttrib(defaultVBO, 0, 3, GL_FLOAT, 11*sizeof(float), (void*)0);
	defaultVAO.LinkAttrib(defaultVBO, 1, 3, GL_FLOAT, 11*sizeof(float), (void*)(3*sizeof(float)));
	defaultVAO.LinkAttrib(defaultVBO, 2, 2, GL_FLOAT, 11*sizeof(float), (void*)(6*sizeof(float)));
	defaultVAO.LinkAttrib(defaultVBO, 3, 3, GL_FLOAT, 11*sizeof(float), (void*)(8*sizeof(float)));
	 

	//Unbind the VAO, VBO and EBO (to prevent modification)
	defaultVAO.Unbind();
	defaultVBO.Unbind();
	defaultEBO.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);

	glm::vec3 pyramidPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPosition);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.id, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(lightShader.id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.id, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);

	//Texture
	Texture block("sandstone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	block.textureUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// The main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Set background colour
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clear the back buffer and assign the new colour to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Check for inputs
		camera.Inputs(window);

		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		//Tell OpenGL what shader program to use
		shaderProgram.Activate();

		glUniform3f(glGetUniformLocation(shaderProgram.id, "cameraPosition"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shaderProgram, "cameraMatrix");

		//Bind the texture
		block.Bind();
		//Bind the VAO (so that OpenGL knows to use it)
		defaultVAO.Bind();

		//Draw the triangle
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);


		lightShader.Activate();
		camera.Matrix(lightShader, "cameraMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}


	//Delete the shader-related objects
	defaultVAO.Delete();
	defaultVBO.Delete();
	defaultEBO.Delete();

	block.Delete();

	shaderProgram.Delete();

	//Delete window
	glfwDestroyWindow(window);

	//Terminate GLFW
	glfwTerminate();
	
	return 0;
}