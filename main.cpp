
#include <QApplication>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "GtWidget.h"
#endif

//#include <iostream>
//#include <stdio.h>
//#include <QDebug>

#include "gtengine/gtengine.h"
using namespace gt;


class DemoWindow : public Window
{
public:
    DemoWindow(void* arg) : Window(arg) { }

    void start() override
    {
        Window::start();

//        auto tex = resources().texture(":/cube.png");

        auto tex = resources().get<Texture>("folder/flower.jpg");
        printf("%d\n", tex.use_count());

        auto tex2 = resources().get<Texture>("folder/flower.jpg");
        printf("%d\n", tex.use_count());

        auto s = canvas()->child<Sprite>();
        s->setTexture(tex);
        s->transform.setX(100);
        s->transform.setY(100);
        s->transform.setAngle(45);

        auto s1 = s->child<Sprite>();
        s1->setTexture(tex2);
        s1->transform.setY(100);
        s1->transform.setAngle(45);
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
    GtWidget<DemoWindow> widget(nullptr);
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
