#pragma once

#include <QOpenGLWidget>

#include "gtplatform/gl.h"

#include "gtplatform/Platform.h"


namespace gt
{
    template<typename TController> class GtWidget : public QOpenGLWidget
    {
//        Q_OBJECT

        TController _controller;
        Platform _platform;

    public:
        explicit GtWidget(QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _controller(_platform), _platform(_controller)
        { }

        void initializeGL() override {
            _platform.initializeGL();
        }

        void resizeGL(int width, int height) override {
            _platform.resizeGL(width, height);
        }

        void paintGL() override {
            _platform.paintGL();
        }
    };
}
