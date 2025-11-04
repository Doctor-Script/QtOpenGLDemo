#pragma once

#include <QOpenGLWindow>
#include <QBasicTimer>
#include <QElapsedTimer>
#include <QApplication>

#include "gtplatform/gl.h"
#include "gtengine/utils/delayed.h"
#include "gtengine/utils/types.h"
#include "gtengine/App.h"


namespace gt
{
    class Controller;

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
        Construct<Controller> _construct;

    public:
        explicit Platform(int count, void* args);

        OpResult run(void* settings, Construct<Controller> construct);

    private:
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
            explicit GLWindow(Platform& platform);

            void initializeGL() override;
            void resizeGL(int width, int height) override;
            void paintGL() override;
            void timerEvent(QTimerEvent*) override;
        };
    };
}
