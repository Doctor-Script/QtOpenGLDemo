
#include <QApplication>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "GtWidget.h"
#endif

#include <iostream>
#include <stdio.h>
#include <QDebug>

#include "gtengine.h"
using namespace gt;

class A {};
class B {};
class C : public A, public B {};

class DemoWindow : public GWindow
{
    void start() override
    {
        GWindow::start();

        auto s = _scene->child<GSprite>();
        s->transform.setX(100);
        s->transform.setY(100);
        s->transform.setAngle(45);

        qDebug() << "asdasda";
//        std::cout << s->state <<
        printf("s state %x\n", s->state);

        auto s1 = s->child<GSprite>();
        s1->transform.setY(100);
        s1->transform.setAngle(45);
    }
};

int main(int argc, char *argv[])
{
//    A* a = new C;
//    B* b = static_cast<B*>(a);

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
