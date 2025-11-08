#pragma once

#include <QOpenGLWindow>


namespace gt
{
    class Platform;

    class OpenGLWindow : public QOpenGLWindow
    {
        Q_OBJECT

        QTimer* _timer;
        Platform& _platform;

    public:
        explicit OpenGLWindow(Platform& platform);

        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;

    private slots:
        void onTimerTick();
    };
}
