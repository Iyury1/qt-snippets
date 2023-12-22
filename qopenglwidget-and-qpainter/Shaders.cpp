#include "Shaders.h"
#include <cmath>

// triangles used for drawing blue and white gradient

float backgVertices[12] = {
    // positions
    -1.0f, -1.0f, 0.0f, // Bottom-left
    -1.0f,  1.0f, 0.0f, // Top-left
     1.0f, -1.0f, 0.0f, // Bottom-right
     1.0f,  1.0f, 0.0f  // Top-right
};

Vertex_t spiralVertices[SPIRAL_PTS];

const char* implVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* implFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

const char* backgFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform float viewportWidth;\n"
"uniform float viewportHeight;\n"
"void main() {\n"
"    float normalizedX = gl_FragCoord.x / viewportWidth;\n"
"    float normalizedY = gl_FragCoord.y / viewportHeight;\n"
"    float mixRatio = (normalizedX + normalizedY) / 2.0;\n"
"    vec3 colorLeft = vec3(0.0, 1.0, 0.0);\n" // Green
"    vec3 colorRight = vec3(0.0, 0.0, 1.0);\n" // Blue
"    vec3 color = mix(colorLeft, colorRight, mixRatio);\n"
"    FragColor = vec4(color, 1.0);\n"
"}\n\0";


const char* backgVertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\n\0";


// archimedean spiral
// r = a + b*theta
void initSprial()
{
	float a = 0.0f; // Adjust these values as needed
	float b = 0.1f; // Adjust for spiral tightness

	for (int i = 0; i < SPIRAL_PTS; ++i) {
		// Calculate the theta for this segment and the next segment
		float theta1 = i * 0.1f;
		float theta2 = (i + 1) * 0.1f;

		// First point of the line segment
		float r1 = a + (b * theta1);
		float x1 = r1 * cos(theta1);
		float y1 = r1 * sin(theta1);

		// Second point of the line segment
		float r2 = a + (b * theta2);
		float x2 = r2 * cos(theta2);
		float y2 = r2 * sin(theta2);

		// Add both points to the vertices list
		spiralVertices[i].x1 = x1; 
		spiralVertices[i].y1 = y1;
		spiralVertices[i].z1 = 0.0f;

		spiralVertices[i].x2 = x2;
		spiralVertices[i].y2 = y2;
		spiralVertices[i].z2 = 0.0f;
	}
}