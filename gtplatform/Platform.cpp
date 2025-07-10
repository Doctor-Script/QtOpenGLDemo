#include "Platform.h"

#include "gtplatform/gl.h"
#include "gtengine/Controller.h"


namespace gt
{
    Platform::Platform(Controller& controller) : _controller(controller) { }

    void Platform::initializeGL()
    {
        gl::_functions = QOpenGLContext::currentContext()->functions();
        _controller.init();
        _controller.start();
    }

    void Platform::resizeGL(int width, int height)
    {
        _controller.resize(width, height);
        _controller.resized();
    }

    void Platform::paintGL() {
        _controller.draw();
    }
}
