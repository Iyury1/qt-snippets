#pragma once

#define SPIRAL_PTS 1000


extern float backgVertices[12];

// Shader sources
extern const char* backgVertexShaderSource;
extern const char* backgFragmentShaderSource;
extern const char* implVertexShaderSource;
extern const char* implFragmentShaderSource;

typedef struct
{
    float x1;
    float y1;
    float z1;
    float x2;
    float y2;
    float z2;
} Vertex_t;

extern Vertex_t spiralVertices[SPIRAL_PTS];


extern void initSprial();
