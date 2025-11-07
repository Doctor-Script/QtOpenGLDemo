#pragma once

#include "gtengine/utils/types.h"
#include "gtengine/App.h"

#include <QApplication>


namespace gt
{
    class Controller;

    class Platform
    {
        friend class OpenGLWindow;

        QApplication _app;
        Controller* _controller;
        Construct<Controller> _construct;

    public:
        struct Settings;

        explicit Platform(int count, void* args);
        ~Platform();

        OpResult run(Settings& settings, Construct<Controller> construct);

    private:
        OpResult init();
        OpResult destroy();

        void resize(int width, int height);

        int draw();

        void tick();

    public:
        struct Settings
        {
            int width;
            int height;
            bool foolscreen;
        };
    };
}
