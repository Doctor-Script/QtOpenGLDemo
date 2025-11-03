#include "Platform.h"

#include "gtengine/Controller.h"
#include "gtengine/utils/Log.h"

#include <QSurfaceFormat>
//#include <QApplication>


namespace gt
{
    Platform::Platform(int count, void** args) : _app(count, reinterpret_cast<char**>(args)), _controller(nullptr)
    {
        GT_LOG_INFO("Launch Platform");

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        QSurfaceFormat::setDefaultFormat(format);
    }



    OpResult IPlatform::exit()
    {
        // TODO implement me
        return OpResult::OK;
    }


    OpResult Platform::run(BuildController build)
    {
        _build = build;

//        int argc = 0;          // must be a variable, not a literal
//        char **argv = nullptr; // no arguments
//        QApplication app(argc, argv);



//        QApplication app(0, nullptr);//(argc, argv);
        //app.setApplicationName(name);
        //app.setApplicationVersion("0.1");

//        #ifndef QT_NO_OPENGL
//            GtWindow<TController> widget;
//            if (res.foolscreen) {
//                widget.showFullScreen();
//            }
//            else
//            {
//                widget.resize(res.width, res.height);
//                widget.show();
//            }
//        #else
//            QLabel note("OpenGL Support required");
//            note.show();
//        #endif

        GLWindow w(*this);
        w.resize(640, 480);
        w.show();

        return _app.exec() ? OpResult::FAIL : OpResult::OK;
    }




    void Platform::init()
    {
        _controller = _build();
        _controller->start();
        _controller->_time.start();
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
}
