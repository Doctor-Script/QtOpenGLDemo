#pragma once

#include <QApplication>
#include <QLabel>

//#ifndef QT_NO_OPENGL
#include "gtplatform/Platform.h"
//#endif

#define GT_RUN(controller) int main(int c, char *a[]) { return run<controller>(c, a, "GT"); }


namespace gt
{
    template<typename TController> inline int run(int argc, char *argv[], const char* name)
    {
        QApplication app(argc, argv);
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
