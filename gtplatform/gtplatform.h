#pragma once

#include <QApplication>
#include <QLabel>

//#ifndef QT_NO_OPENGL
#include "gtplatform/Platform.h"
//#endif

#define GT_RES_WINDOWED(w, h) { w, h, false }
#define GT_RES_FOOLSCREEN { 0, 0, true }
#define GT_RES_DEFAULT { 640, 480, false }

#define GT_RUN(controller, resolution) int main(int c, char *a[]) { return run<controller>(c, a, resolution); }


namespace gt
{
    struct Resoulution
    {
        int width;
        int height;
        bool foolscreen;
    };

    template<typename TController> inline int run(int argc, char *argv[], Resoulution res)
    {
        QApplication app(argc, argv);
        //app.setApplicationName(name);
        //app.setApplicationVersion("0.1");

    #ifndef QT_NO_OPENGL
        GtWidget<TController> widget(nullptr);
        if (res.foolscreen) {
            widget.showFullScreen();
        }
        else
        {
            widget.resize(res.width, res.height);
            widget.show();
        }
    #else
        QLabel note("OpenGL Support required");
        note.show();
    #endif
        return app.exec();
    }
}
