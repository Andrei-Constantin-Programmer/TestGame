#include "shaderClass.h"

string getFileContents(const char* fileName)
{
	ifstream f(fileName, ios::binary);
	if (f)
	{
		string contents;
		f.seekg(0, ios::end);
		contents.resize(f.tellg());
		f.seekg(0, ios::beg);
		f.read(&contents[0], contents.size());
		f.close();

		return (contents);
	}
	throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	string vertexCode = getFileContents(vertexFile);
	string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create the vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach the vertex shader source to the object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the vertex shader
	glCompileShader(vertexShader);

	//Create the fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach the fragment shader source to the object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the fragment shader
	glCompileShader(fragmentShader);

	//Create the shader program object
	id = glCreateProgram();

	//Attach the shaders to the shader program
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	//Link all the shaders together in the shader program
	glLinkProgram(id);

	//Delete the shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(id);
}

void Shader::Delete()
{
	glDeleteProgram(id);
}