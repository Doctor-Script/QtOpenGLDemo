#pragma once

#include <QOpenGLWindow>
#include <QBasicTimer>
#include <QElapsedTimer>
#include <QApplication>

#include "gtplatform/gl.h"
#include "gtengine/utils/delayed.h"
#include "gtengine/utils/types.h"

#include <functional>


namespace gt
{
    class Controller;
    typedef std::function<Controller*()> BuildController;

    struct Resoulution
    {
        int width;
        int height;
        bool foolscreen;
    };

    class Platform
    {
        QApplication _app;
        Controller* _controller;
        BuildController _build;

    public:
        explicit Platform(int count, void* args);

        OpResult run(void* settings, BuildController build);

        void init();

        void resize(int width, int height);

        int draw();

        void tick();




        class GLWindow : public QOpenGLWindow
        {
            //Q_OBJECT

            Platform& _platform;
            int _timer;

        public:
            explicit GLWindow(Platform& platform) : _platform(platform) { }

            void initializeGL() override
            {
                gl::_functions = QOpenGLContext::currentContext()->functions();
                gl::_extra = QOpenGLContext::currentContext()->extraFunctions();
                _platform.init();
            }

            void resizeGL(int width, int height) override {
                _platform.resize(width, height);
            }

            void paintGL() override {
                _timer = startTimer(_platform.draw());
            }

            void timerEvent(QTimerEvent*) override
            {
                _platform.tick();
                update();
            }
        };




    };





//    template<typename TController> class GtWindow
//    {
//        delayed<TController> _controller;
//        Platform _platform;

//    public:
//        explicit GtWindow(int count, void* args) : _platform(count, args) { }

//        OpResult run(void* settings)
//        {
//            auto build = [this]() { return _controller.construct(_platform); };
//            CHECK_OP(_platform.run(settings, build));
//            return OpResult::OK;
//        }
//    };
}
