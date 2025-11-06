#pragma once

#include "gtplatform/Platform.h"

#include <QApplication>
#include <QLabel>


#undef GT_IF_QT
#define GT_IF_QT(...) __VA_ARGS__

#define GT_PLATFORM_QT

#define GT_QT_WINDOWED(w, h) { w, h, false }
#define GT_QT_FOOLSCREEN { 0, 0, true }
#define GT_QT_DEFAULT { 640, 480, false }

#define GT_MAIN(body) int main(int argc, char *argv[]) { gt::Platform::Settings GT_SETTINGS = GT_QT_DEFAULT; body }
#define GT_RUN(controller) return !gt::App<Platform, controller>(argc, argv).run(GT_SETTINGS);


namespace gt
{

}
