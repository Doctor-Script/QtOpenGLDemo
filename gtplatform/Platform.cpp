#include "Platform.h"

#include "gtengine/Controller.h"
#include "gtengine/utils/Log.h"

#include <QSurfaceFormat>


namespace gt
{
    Platform::Platform(int count, void* args) : _app(count, reinterpret_cast<char**>(args)), _controller(nullptr)
    {
        GT_LOG_INFO("Launch Platform: Qt");
    }

    Platform::~Platform() {
        destroy();
    }

    OpResult IPlatform::exit()
    {
        // TODO implement me
        return OpResult::OK;
    }

    OpResult Platform::run(Settings& settings, Construct<Controller> construct)
    {
        _construct = construct;

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        QSurfaceFormat::setDefaultFormat(format);

#ifndef QT_NO_OPENGL
        GLWindow w(*this);
        if (settings.foolscreen) {
            w.showFullScreen();
        }
        else
        {
            w.resize(settings.width, settings.height);
            w.show();
        }
#else
        QLabel note("OpenGL Support required");
        note.show();
#endif
        return static_cast<OpResult>(!_app.exec());
    }

    OpResult Platform::init()
    {
        _controller = _construct();
        CHECK_NULL(_controller);

        _controller->start();
        _controller->_time.start();

        return OpResult::OK;
    }

    OpResult Platform::destroy() {
        return OpResult::OK;
    }

    void Platform::resize(int width, int height)
    {
        _controller->resize(width, height);
        _controller->layout();
    }

    int Platform::draw()
    {
        _controller->draw();
        int waitTime = _controller->_time.calculateWaitTime();
        return waitTime >= 0 ? waitTime : 0;
    }

    void Platform::tick()
    {
        Time& time = _controller->_time;
        time.frameEnd();
        time.frameBegin();

        // TODO Input

        _controller->tick();
        _controller->tickChildren();
    }

    Platform::GLWindow::GLWindow(Platform& platform) : _platform(platform) { }

    void Platform::GLWindow::initializeGL()
    {
        gl::_functions = QOpenGLContext::currentContext()->functions();
        gl::_extra = QOpenGLContext::currentContext()->extraFunctions();
        if (!_platform.init()) {
            GT_LOG_ERR(AT "_platform.init()");
        }
    }

    void Platform::GLWindow::resizeGL(int width, int height) {
        _platform.resize(width, height);
    }

    void Platform::GLWindow::paintGL() {
        _timer = startTimer(_platform.draw());
    }

    void Platform::GLWindow::timerEvent(QTimerEvent*)
    {
        _platform.tick();
        update();
    }
}
