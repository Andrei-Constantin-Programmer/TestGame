#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

in vec3 Normal;
in vec3 currentPosition;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
	//Ambient lighting
	float ambient = 0.20f;

	//Diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - currentPosition);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse+ambient);
}