#pragma once

#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QElapsedTimer>

#include "gtplatform/gl.h"
#include "gtengine/utils/delayed.h"


namespace gt
{
    class Controller;

    class Platform
    {
        Controller& _controller;

    public:
        explicit Platform(Controller& controller);

        void init();

        void resize(int width, int height);

        int draw();

        void tick();
    };

    template<typename TController> class GtWidget : public QOpenGLWidget
    {
        //Q_OBJECT

        delayed<TController> _controller;
        Platform _platform;
        int _timer;

    public:
        explicit GtWidget(QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _platform(*_controller.get())
        { }

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
    };
}
