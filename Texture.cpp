#include "Texture.h"

Texture::Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
	//Assigns the type of the texture
	type = textureType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);

	// Generates an OpenGL texture object
	glGenTextures(1, &id);
	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(textureType, id);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(textureType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(textureType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(textureType, 0);
}

void Texture::textureUnit(Shader& shader, const char* uniform, GLuint unit)
{
	//Gets the location of the uniform
	GLuint textureUnit = glGetUniformLocation(shader.id, uniform);
	//Activate the shader
	shader.Activate();
	//Set the value of the uniform
	glUniform1i(textureUnit, unit);
}

void Texture::Bind()
{
	glBindTexture(type, id);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &id);
}

