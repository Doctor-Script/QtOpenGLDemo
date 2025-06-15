#pragma once

#include <QOpenGLWidget>

#include "Window.h"
#include "gtrendering/QtRender.h"

namespace gt
{
    template<typename TWindow> class GtWidget : public QOpenGLWidget
    {
//        Q_OBJECT

        QtRender _render;
        TWindow _window;

    public:
        explicit GtWidget(void* arg, QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _window(arg, &_render)
        {
        }

        void initializeGL()
        {
            gl::_functions = QOpenGLContext::currentContext()->functions();
            _render.init();
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
