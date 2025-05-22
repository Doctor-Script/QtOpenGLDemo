#include "GtWidget.h"
#include "SriteRenderDelegate.h"

#include "sprite/Transform2D.h"

namespace gt
{
    GtWidget::GtWidget(GWindow* window, QWidget *parent)
        : QOpenGLWidget(parent), _window(window), indexBuf(QOpenGLBuffer::IndexBuffer)
    {
        _window->renderer = new QtRenderer();
        _window->start();
    }

    GtWidget::~GtWidget()
    {
        arrayBuf.destroy();
        indexBuf.destroy();
        delete _window->renderer;
    }

    void GtWidget::initializeGL()
    {
        _window->renderer->init();
    }

    void GtWidget::resizeGL(int w, int h)
    {
         _window->renderer->resize(w, h);
    }

    void GtWidget::paintGL()
    {
         _window->renderer->render(_window->_scene);
    }
} // namespace gt
