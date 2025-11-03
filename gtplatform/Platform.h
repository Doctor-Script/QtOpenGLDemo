#pragma once

#include <QOpenGLWindow>
#include <QBasicTimer>
#include <QElapsedTimer>

#include "gtplatform/gl.h"
#include "gtengine/utils/delayed.h"
#include "gtengine/utils/types.h"

#include <functional>


namespace gt
{
    class Controller;
    typedef std::function<Controller*()> BuildController;

    class Platform
    {
        Controller* _controller;
        BuildController _build;

    public:
        explicit Platform(void* arg);

        OpResult run(BuildController build);

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
//                _platform.draw();
            }

            void timerEvent(QTimerEvent*) override
            {
                _platform.tick();
                update();
            }
        };




    };





    template<typename TController> class GtWindow
    {
        delayed<TController> _controller;
        Platform _platform;

    public:
        explicit GtWindow(void* arg) : _platform(arg) { }

        OpResult run()
        {
            CHECK_OP(_platform.run([this]() { return _controller.construct(_platform); }));
            return OpResult::OK;
        }
    };

/*
    template<typename TController> class GtWindow : public QOpenGLWindow
    {
        //Q_OBJECT

        delayed<TController> _controller;
        Platform _platform;
        int _timer;

    public:
        explicit GtWindow() : _platform(*_controller.get()) { }

        void initializeGL() override
        {
            gl::_functions = QOpenGLContext::currentContext()->functions();
            gl::_extra = QOpenGLContext::currentContext()->extraFunctions();
            _controller.construct(_platform);
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
    };//*/
}
