#pragma once

#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

//#ifndef QT_NO_OPENGL
#include "GtWidget.h"
//#endif

#define GT_RUN(window) int main(int c, char *a[]) { return run<window>(c, a, "GT"); }

namespace gt
{
    template<typename TWindow> inline int run(int argc, char *argv[], const char* name)
    {
        QApplication app(argc, argv);

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        QSurfaceFormat::setDefaultFormat(format);

        app.setApplicationName(name);
        //app.setApplicationVersion("0.1");

    #ifndef QT_NO_OPENGL
        GtWidget<TWindow> widget(nullptr);
        widget.show();
    #else
        QLabel note("OpenGL Support required");
        note.show();
    #endif
        return app.exec();
    }
}
