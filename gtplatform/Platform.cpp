#include "Platform.h"

#include "gtplatform/gl.h"
#include "gtengine/Controller.h"
#include "gtengine/utils/Log.h"

#include <QSurfaceFormat>


namespace gt
{
    Platform::Platform(Controller& controller) : _controller(controller)
    {
        GT_LOG_INFO("Launch Platform");

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        QSurfaceFormat::setDefaultFormat(format);
    }

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
