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

    void Platform::init()
    {
        gl::_functions = QOpenGLContext::currentContext()->functions();

        _controller.init();
        _controller.start();

        _controller._time.start();
    }

    void Platform::resize(int width, int height)
    {
        _controller.resize(width, height);
        _controller.resized();
    }

    int Platform::draw()
    {
        _controller.draw();
        return _controller._time.calculateWaitTime();
    }

    void Platform::tick()
    {
        _controller._time.frameEnd();
        _controller._time.frameBegin();
        _controller.tick();
    }
}
