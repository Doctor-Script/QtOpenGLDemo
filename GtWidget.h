#pragma once

#include <QOpenGLWidget>

#include "Window.h"
#include "gtrendering/QtRender.h"

namespace gt
{
    class GtWidget : public QOpenGLWidget
    {
        Q_OBJECT

        Window* _window;
        QtRender _render;

        // TODO check _window destruction. Nodes tree should be destroyed before window

    public:
        explicit GtWidget(Window* window, QWidget *parent = nullptr);
        ~GtWidget();

        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;
    };
}
