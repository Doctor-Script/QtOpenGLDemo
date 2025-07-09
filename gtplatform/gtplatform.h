#pragma once

#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

//#ifndef QT_NO_OPENGL
#include "gtplatform/GtWidget.h"
//#endif

#define GT_RUN(controller) int main(int c, char *a[]) { return run<controller>(c, a, "GT"); }

namespace gt
{
    template<typename TController> inline int run(int argc, char *argv[], const char* name)
    {
        QApplication app(argc, argv);

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        QSurfaceFormat::setDefaultFormat(format);

        app.setApplicationName(name);
        //app.setApplicationVersion("0.1");

    #ifndef QT_NO_OPENGL
        GtWidget<TController> widget(nullptr);
        widget.show();
    #else
        QLabel note("OpenGL Support required");
        note.show();
    #endif
        return app.exec();
    }
}
