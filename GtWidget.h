#ifndef GT_GTWIDGET_H
#define GT_GTWIDGET_H

#include <QOpenGLWidget>

#include "gtengine.h"

namespace gt
{
    class GtWidget : public QOpenGLWidget
    {
        Q_OBJECT

        std::unique_ptr<GWindow> _window;


    public:
        explicit GtWidget(GWindow* window, QWidget *parent = nullptr);
        ~GtWidget();

        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
    };
}

#endif // GT_GTWIDGET_H
