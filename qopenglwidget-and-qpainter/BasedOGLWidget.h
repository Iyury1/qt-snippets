#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "Shaders.h"
#include <iostream>
#include <QPainter>

class BasedOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
private:
    // background is the same for all subclasses
    unsigned int backgShaderProgram;
    unsigned int backgVBO;
    unsigned int backgVAO;
    // uniforms for gradient calc
    unsigned int viewportWidthLocation;
    unsigned int viewportHeightLocation;
    void drawBackground();
    void drawGreenDot(QPainter* painter);

public:
    BasedOGLWidget(QWidget *parent = nullptr);
    ~BasedOGLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // subclass specific drawing
    virtual void implInitGL() = 0;
    virtual void implResizeGL() = 0;
    virtual void implPaintGL() = 0;
};