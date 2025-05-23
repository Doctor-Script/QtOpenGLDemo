#include "GtWidget.h"
#include "SriteRenderDelegate.h"

//#include "sprite/Transform2D.h"

namespace gt
{
    GtWidget::GtWidget(GWindow* window, QWidget *parent)
        : QOpenGLWidget(parent), _window(window)
    {
        _window->render = new QtRender();
        _window->context.render = _window->render;
        _window->start();
    }

    GtWidget::~GtWidget()
    {
        delete _window->render;
    }

    void GtWidget::initializeGL()
    {
        _window->render->init();
    }

    void GtWidget::resizeGL(int w, int h)
    {
         _window->render->resize(w, h);
    }

    void GtWidget::paintGL()
    {
         _window->render->draw(_window->_scene);
    }
}
