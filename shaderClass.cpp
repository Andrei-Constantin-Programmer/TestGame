#include "ShaderClass.h"

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

	//Check if the shader was compiled successfully
	compileErrors(vertexShader, "VERTEX");

	//Create the fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach the fragment shader source to the object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the fragment shader
	glCompileShader(fragmentShader);

	//Check if the shader was compiled successfully
	compileErrors(fragmentShader, "FRAGMENT");

	//Create the shader program object
	id = glCreateProgram();

	//Attach the shaders to the shader program
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	//Link all the shaders together in the shader program
	glLinkProgram(id);

	//Check if the shader was compiled successfully
	compileErrors(id, "PROGRAM");

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


void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << endl;
		}
	}
}
