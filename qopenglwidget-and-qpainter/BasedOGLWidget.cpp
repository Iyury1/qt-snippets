#include "BasedOGLWidget.h"

BasedOGLWidget::BasedOGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

BasedOGLWidget::~BasedOGLWidget() {}


void BasedOGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    int success;
    char infoLog[512];

    unsigned int backgVertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int backgFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(backgVertexShader, 1, &backgVertexShaderSource, NULL);
    glCompileShader(backgVertexShader);
    glGetShaderiv(backgVertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(backgVertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glShaderSource(backgFragmentShader, 1, &backgFragmentShaderSource, NULL);
    glCompileShader(backgFragmentShader);
    glGetShaderiv(backgFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(backgFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    backgShaderProgram = glCreateProgram();
    glAttachShader(backgShaderProgram, backgVertexShader);
    glAttachShader(backgShaderProgram, backgFragmentShader);
    glLinkProgram(backgShaderProgram);

    // check for linking errors
    glGetProgramiv(backgShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(backgShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(backgVertexShader);
    glDeleteShader(backgFragmentShader);



    glGenVertexArrays(1, &backgVAO);
    glBindVertexArray(backgVAO);
    glGenBuffers(1, &backgVBO);
    glBindBuffer(GL_ARRAY_BUFFER, backgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(backgVertices), backgVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    viewportWidthLocation = glGetUniformLocation(backgShaderProgram, "viewportWidth");
    viewportHeightLocation = glGetUniformLocation(backgShaderProgram, "viewportHeight");

    
    implInitGL();

}

void BasedOGLWidget::resizeGL(int w, int h) {
    implResizeGL();
 }

void BasedOGLWidget::paintGL() {

#if defined(WITH_PAINTER)
    QPainter painter(this);
    painter.beginNativePainting();
    makeCurrent();
#endif
    drawBackground();
    implPaintGL();
#if defined(WITH_PAINTER)
    painter.endNativePainting();
#endif
}

void BasedOGLWidget::drawBackground()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(backgShaderProgram);
    glUniform1f(viewportWidthLocation, static_cast<float>(width()));
    glUniform1f(viewportHeightLocation, static_cast<float>(height()));
    glBindVertexArray(backgVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

void BasedOGLWidget::drawGreenDot(QPainter* painter)
{
  painter->setRenderHint(QPainter::Antialiasing);

  painter->setBrush(Qt::green);
  painter->setPen(Qt::NoPen);
  // Draw a circle
  int diameter = 100; // Set the diameter of the dot
  int x = (width() - diameter) / 2;  // Center the dot horizontally
  int y = (height() - diameter) / 2; // Center the dot vertically
  painter->drawEllipse(x, y, diameter, diameter);
}