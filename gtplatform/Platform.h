#pragma once


namespace gt
{
    class Controller;

    class Platform
    {
        Controller& _controller;
        bool _started = false;

    public:
        explicit Platform(Controller& controller);

        void initializeGL();

        void resizeGL(int width, int height);

        void paintGL();
    };
}
