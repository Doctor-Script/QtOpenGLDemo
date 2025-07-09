#pragma once

#include <QOpenGLWidget>

#include "gtplatform/gl.h"

#include "gtplatform/Platform.h"


namespace gt
{
    // TODO Get rid of template
    // TODO _controller.start() must be called after window has correct size

    template<typename TController> class GtWidget : public QOpenGLWidget
    {
//        Q_OBJECT

        TController _controller;
        Platform _platform;

    public:
        explicit GtWidget(QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _controller(_platform), _platform(_controller)
        { }

        void initializeGL()
        {
            gl::_functions = QOpenGLContext::currentContext()->functions();
            _controller.init();
            _controller.start();
        }

        void resizeGL(int width, int height) {
            _controller.resize(width, height);
        }

        void paintGL() {
            _controller.draw();
        }
    };
}
