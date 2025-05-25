#include "GtWidget.h"

namespace gt
{
    GtWidget::GtWidget(GWindow* window, QWidget *parent)
        : QOpenGLWidget(parent), _window(window)
    {
        _window->init(&_render);
        _window->start();
    }

    GtWidget::~GtWidget() {
        delete _window;
    }

    void GtWidget::initializeGL() {
        _render.init();
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
