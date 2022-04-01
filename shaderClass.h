#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

using namespace std;
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cerrno>

string getFileContents(const char* fileName);

class Shader
{
	public:
		GLuint id;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();

		void Delete();

		void compileErrors(unsigned int shader, const char* type);
};

#endif