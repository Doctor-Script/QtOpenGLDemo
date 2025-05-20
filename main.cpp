
#include <QApplication>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "GtWidget.h"
#endif

using namespace gt;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("GL Demo");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
    GtWidget widget;
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
