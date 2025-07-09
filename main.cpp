#include "gtengine/gtengine.h"
using namespace gt;


class DemoController : public Controller
{
public:
    explicit DemoController(Platform& platform) : Controller(platform) { }

    void start() override
    {
        Controller::start();

        auto cube = resources().get<Texture>("cube.png");

        auto flower = resources().get<Texture>("folder/flower.jpg");
        GT_LOG("%d", flower.use_count());

        auto flower2 = resources().get<Texture>("folder/flower.jpg");
        GT_LOG("%d", flower2.use_count());

        auto s = canvas()->child<Sprite>();
        s->setTexture(flower);
        s->transform.setX(100);
        s->transform.setY(100);
        s->transform.setAngle(45);

        auto s1 = s->child<Sprite>();
        s1->setTexture(cube);
        s1->transform.setY(100);
        s1->transform.setAngle(45);
    }
};

GT_RUN(DemoController);
