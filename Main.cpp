using namespace std;
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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

	//Create the vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach the vertex shader source to the object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the vertex shader
	glCompileShader(vertexShader);

	//Create the fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach the fragment shader source to the object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile the fragment shader
	glCompileShader(fragmentShader);

	//Create the shader program object
	GLuint shaderProgram = glCreateProgram();

	//Attach the shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Link all the shaders together in the shader program
	glLinkProgram(shaderProgram);

	//Delete the shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Vertices coordinates for the triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	//Containers for the vertex array object and the vertex buffer object
	GLuint VAO, VBO;

	//Generate the VAO and VBO with a single object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//Make the VAO the current vertex array object by binding it
	glBindVertexArray(VAO);

	//Bind VBO, specifying it is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure the Vertex Attribute (so that OpenGL knows how to read the VBO)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	//Enable the Vertex Attribute (so that OpenGL knows to use it)
	glEnableVertexAttribArray(0);

	//Bind the VBO and VAO to 0 (to not accidentally modify them)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// The main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Set background colour
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clear the back buffer and assign the new colour to it
		glClear(GL_COLOR_BUFFER_BIT);

		//Tell OpenGL what shader program to use
		glUseProgram(shaderProgram);
		//Bind the VAO (so that OpenGL knows to use it)
		glBindVertexArray(VAO);

		//Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Delete window
	glfwDestroyWindow(window);

	//Terminate GLFW
	glfwTerminate();
	
	return 0;
}