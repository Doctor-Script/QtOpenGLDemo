
#include <QApplication>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "GtWidget.h"
#endif



#include "gtengine.h"
using namespace gt;

class DemoWindow : public GtWindow
{
    void created() override
    {
        GtWindow::created();

        auto s = _scene->child<GtSprite>();
        s->transform.setX(100);
        s->transform.setY(100);
//        s->transform.setAngle(45);

        auto s1 = s->child<GtSprite>();
        s1->transform.setY(100);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("GL Demo");
    app.setApplicationVersion("0.1");



#ifndef QT_NO_OPENGL
    GtWidget widget(new DemoWindow());
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
