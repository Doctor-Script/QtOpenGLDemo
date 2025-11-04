#pragma once

#include <QApplication>
#include <QLabel>

//#ifndef QT_NO_OPENGL
#include "gtplatform/Platform.h"
//#endif

//#define GT_RES_WINDOWED(w, h) { w, h, false }
//#define GT_RES_FOOLSCREEN { 0, 0, true }
//#define GT_RES_DEFAULT { 640, 480, false }

#define GT_RUN(controller, resolution) int main(int c, char *a[]) { return !gt::App<Platform, controller>(c, a).run(&resolution); }

namespace gt
{

}
