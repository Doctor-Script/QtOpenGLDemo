#include "gtengine/gtengine.h"
using namespace gt;


class DemoController : public Controller
{
    gref<Sprite> s;
public:
    explicit DemoController(Platform& platform) : Controller(platform) { }

    void start() override
    {
        Controller::start();

        //auto cube = resources().get<Texture>("cube.png");
        //auto flower = resources().get<Texture>("folder/flower.jpg");
        //GT_LOG("%d", flower.use_count());

        //auto flower2 = resources().get<Texture>("folder/flower.jpg");
        //GT_LOG("%d", flower2.use_count());

        auto circle = resources().get<Texture>("compass-circle.png");

        s = canvas()->child<Sprite>();
        s->setTexture(circle);



//        s->transform.setX(100);
//        s->transform.setY(100);
//        s->transform.setAngle(45);

//        auto s1 = s->child<Sprite>();
//        s1->setTexture(cube);
//        s1->transform.setY(100);
//        s1->transform.setAngle(45);
    }

    void resized() override
    {
        float width = screen().width();
        float height = screen().height();
        float size = width < height ? width : height;

        s->transform.setX(width / 2.f);
        s->transform.setY(height / 2.f);

        s->transform.setWidth(size - 40.f);
        s->transform.setHeight(size - 40.f);
    }

    void tick(Time& time) override
    {

        // TODO get rid of parent call
        Controller::tick(time);


        s->transform.setAngle(s->transform.angle() + 10 * time.deltaS());
    }
};

GT_RUN(DemoController);
