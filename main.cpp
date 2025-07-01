#include "gtengine/gtengine.h"
using namespace gt;

//#include <iostream>
//#include <stdio.h>
//#include <QDebug>

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

GT_RUN(DemoWindow);
