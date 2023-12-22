#pragma once

#include "BasedOGLWidget.h"


class SubOGLWidget : public BasedOGLWidget
{

private:
    unsigned int implShaderProgram;
    unsigned int implVAO;
    unsigned int implVBO;

    int& spiralEnd;
public:
    SubOGLWidget(int& spiralEnd, QWidget *parent = nullptr);
    ~SubOGLWidget();
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
protected:
    virtual void implInitGL() override;
    virtual void implResizeGL() override;
    virtual void implPaintGL() override;
};

