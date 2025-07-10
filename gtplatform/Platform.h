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
        QElapsedTimer _counter;
        bool _started;


    public:
        explicit Platform(Controller& controller);

        void initializeGL();

        void resizeGL(int width, int height);

        void paintGL();

        void timerTick();
    };

    template<typename TController> class GtWidget : public QOpenGLWidget
    {
        //Q_OBJECT

        TController _controller;
        Platform _platform;
        QBasicTimer _timer;

    public:
        explicit GtWidget(QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _controller(_platform), _platform(_controller)
        {
            _timer.start(1000 / 60, this);
        }

        void initializeGL() override {
            _platform.initializeGL();
        }

        void resizeGL(int width, int height) override {
            _platform.resizeGL(width, height);
        }

        void paintGL() override {
            _platform.paintGL();
        }

        void timerEvent(QTimerEvent*) override
        {
            _platform.timerTick();
            update();
        }
    };
}
