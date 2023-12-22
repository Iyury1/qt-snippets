#include "SubOGLWidget.h"

SubOGLWidget::SubOGLWidget(int& spiralEnd, QWidget *parent) : spiralEnd(spiralEnd), BasedOGLWidget(parent) {}

SubOGLWidget::~SubOGLWidget() {}


void SubOGLWidget::implInitGL() {
    int success;
    char infoLog[512];

    // compile shaders

    unsigned int implVertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int implFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(implVertexShader, 1, &implVertexShaderSource, NULL);
    glCompileShader(implVertexShader);
    glGetShaderiv(implVertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
        {
        glGetShaderInfoLog(implVertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    glShaderSource(implFragmentShader, 1, &implFragmentShaderSource, NULL);
    glCompileShader(implFragmentShader);
    glGetShaderiv(implFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
        {
        glGetShaderInfoLog(implFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    implShaderProgram = glCreateProgram();
    glAttachShader(implShaderProgram, implVertexShader);
    glAttachShader(implShaderProgram, implFragmentShader);
    glLinkProgram(implShaderProgram);
    // check for linking errors
    glGetProgramiv(implShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(implShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(implVertexShader);
    glDeleteShader(implFragmentShader);

    // setup vertex attribs and buffer

    glGenVertexArrays(1,&implVAO);
    glBindVertexArray(implVAO);
    glGenBuffers(1,&implVBO);
    glBindBuffer(GL_ARRAY_BUFFER,implVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray (0);
}

void SubOGLWidget::implResizeGL() {}

void SubOGLWidget::implPaintGL() {
    // draw the archimedean spiral
    glUseProgram(implShaderProgram);
    glBindVertexArray(implVAO);
    glLineWidth(2.0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_t) * spiralEnd, &spiralVertices, GL_STATIC_DRAW);
	glDrawArrays(GL_LINES, 0, spiralEnd * 2);
    glBindVertexArray(0);
    glUseProgram(0);
}

/*
* minimumSizeHint() and sizeHint() should be implemented by all custom Widgets.
* These functions are used by Qt layout managers for sizing Widgets inside a
* layout.
*/
QSize SubOGLWidget::minimumSizeHint() const
{
    return QSize(800, 600);
}

QSize SubOGLWidget::sizeHint() const
{
    return QSize(800, 600);
}
