#pragma once

#include <QOpenGLWidget>

#include "gtpatform/gl.h"


namespace gt
{
    template<typename TWindow> class GtWidget : public QOpenGLWidget
    {
//        Q_OBJECT

        TWindow _window;

    public:
        explicit GtWidget(void* arg, QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _window(arg)
        { }

        void initializeGL()
        {
            gl::_functions = QOpenGLContext::currentContext()->functions();
            _window.init();
            _window.start();
        }

        void resizeGL(int width, int height) {
            _window.resize(width, height);
        }

        void paintGL() {
            _window.draw();
        }
    };
}
