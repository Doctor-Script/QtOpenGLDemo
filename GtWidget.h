#pragma once

#include <QOpenGLWidget>

#include "gtrendering/QtRender.h"
#include "Window.h"

namespace gt
{
    class GtWidget : public QOpenGLWidget
    {
        Q_OBJECT

        QtRender _render;
        Window* _window;

        // TODO check _window destruction. Nodes tree should be destroyed before window

    public:
        explicit GtWidget(Window* window, QWidget *parent = nullptr);
        ~GtWidget();

        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;
    };
}
