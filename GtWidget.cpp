#include "GtWidget.h"

namespace gt
{
    GtWidget::GtWidget(Window* window, QWidget *parent)
        : QOpenGLWidget(parent), _window(window)
    {
        _window->init(&_render);
    }

    GtWidget::~GtWidget() {
        delete _window;
    }

    void GtWidget::initializeGL() {
        _render.init();
        _window->start();
    }

    void GtWidget::resizeGL(int width, int height)
    {
        _window->resize(static_cast<float>(width), static_cast<float>(height));
        _render.resize(width, height);
    }

    void GtWidget::paintGL() {
        _render.draw(_window->scene());
    }
}
