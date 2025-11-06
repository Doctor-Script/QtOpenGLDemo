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

    class Platform
    {
        QApplication _app;
        Controller* _controller;
        Construct<Controller> _construct;

    public:
        struct Settings
        {
            int width;
            int height;
            bool foolscreen;
        };

        explicit Platform(int count, void* args);
        ~Platform();

        OpResult run(Settings& settings, Construct<Controller> construct);

    private:
        OpResult init();
        OpResult destroy();

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
