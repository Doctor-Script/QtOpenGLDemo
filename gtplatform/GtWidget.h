#pragma once

#include <QOpenGLWidget>

#include "gtplatform/gl.h"

#include "gtplatform/Platform.h"


namespace gt
{
    // TODO Get rid of template
    // TODO window.start() must be called after window has correct size

    template<typename TWindow> class GtWidget : public QOpenGLWidget
    {
//        Q_OBJECT

        TWindow _window;
        Platform _platform;

    public:
        explicit GtWidget(QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _window(_platform), _platform(_window)
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
