#include "Platform.h"

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
        _controller.start();
        _controller._time.start();
    }

    void Platform::resize(int width, int height)
    {
        _controller.resize(width, height);
        _controller.layout();
    }

    int Platform::draw()
    {
        _controller.draw();
        int waitTime = _controller._time.calculateWaitTime();
        return waitTime >= 0 ? waitTime : 0;
    }

    void Platform::tick()
    {
        Time& time = _controller._time;
        time.frameEnd();
        time.frameBegin();

        // TODO Input

        _controller.tick();
        _controller.tickChildren();
    }
}
