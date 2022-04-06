#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normal layout
layout (location = 3) in vec3 aNormal;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

out vec3 Normal;
out vec3 currentPosition;

uniform mat4 cameraMatrix;
uniform mat4 model;

void main()
{
	currentPosition = vec3(model*vec4(aPos, 1.0f));

	// Outputs the positions/coordinates of all vertices
	gl_Position = cameraMatrix * vec4(currentPosition, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	Normal = aNormal;
}