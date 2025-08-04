#pragma once

#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QElapsedTimer>


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

        TController _controller;
        Platform _platform;
        int _timer;

    public:
        explicit GtWidget(QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _controller(_platform), _platform(_controller)
        { }

        void initializeGL() override {
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
