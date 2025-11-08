#include "gtplatform/native/OpenGLWindow.h"

#include "gtplatform/Platform.h"
#include "gtplatform/gl.h"

#include "gtengine/utils/Log.h"

#include <QTimer>
#include <QThread>
#include <QDebug>


namespace gt
{
    OpenGLWindow::OpenGLWindow(Platform& platform) : _platform(platform)
    {
        _timer = new QTimer(this);
        connect(_timer, &QTimer::timeout, this, &OpenGLWindow::onTimerTick);
    }

    void OpenGLWindow::initializeGL()
    {
        gl::_functions = QOpenGLContext::currentContext()->functions();
        gl::_extra = QOpenGLContext::currentContext()->extraFunctions();
        if (!_platform.init()) {
            GT_LOG_ERR(AT "_platform.init()");
        }

        _timer->setInterval(0);
        _timer->start();
    }

    void OpenGLWindow::resizeGL(int width, int height) {
        _platform.resize(width, height);
    }

    void OpenGLWindow::paintGL()
    {
        int waitTime = _platform.draw();
        _timer->setInterval(waitTime);
    }

    void OpenGLWindow::onTimerTick()
    {
        _platform.tick();
        update();
    }
}
