#include "gtengine/gtengine.h"
using namespace gt;


class Compass : public Node2D
{
    gref<Sprite> _bg;
    gref<Sprite> _overlay;
public:
    explicit Compass(w_ref<Node> parent) : Node2D(parent)
    {
        // TODO Can I create childer here?
    }

    void start() override
    {
        auto circle = resources().get<Texture>("compass-circle.png");
        _bg = child<Sprite>(circle);

        _overlay = child<Sprite>("cube.png");
    }

    void layout() override
    {
        auto canvas = s_cast<Canvas>(parent());//->to<Canvas>();

        float width = canvas->width();
        float height = canvas->height();
        float size = width < height ? width : height;

        transform.setX(width / 2.f);
        transform.setY(height / 2.f);

        transform.setWidth(size - 40.f);
        transform.setHeight(size - 40.f);

        _bg->transform.setWidth(transform.width());
        _bg->transform.setHeight(transform.height());
    }

    void tick() override
    {
        Node2D::tick();
//        tickChildren();

        _bg->transform.setAngle(_bg->transform.angle() + 10 * time().delta());
    }
};


class DemoController : public Controller
{
    gref<Compass> _compass;
public:
    explicit DemoController(Platform& platform) : Controller(platform) { }

    void start() override
    {
        Controller::start();

//        setBackground(Color::green());

        //auto cube = resources().get<Texture>("cube.png");
        //auto flower = resources().get<Texture>("folder/flower.jpg");
        //GT_LOG("%d", flower.use_count());

        //auto flower2 = resources().get<Texture>("folder/flower.jpg");
        //GT_LOG("%d", flower2.use_count());

        auto circle = resources().get<Texture>("compass-circle.png");

//        s = canvas()->child<Sprite>(circle);
//        s->setTexture(circle);

        _compass = canvas()->child<Compass>();



//        s->transform.setX(100);
//        s->transform.setY(100);
//        s->transform.setAngle(45);

//        auto s1 = s->child<Sprite>();
//        s1->setTexture(cube);
//        s1->transform.setY(100);
//        s1->transform.setAngle(45);
    }

    void layout() override
    {
        float width = screen().width();
        float height = screen().height();
        float size = width < height ? width : height;

//        GT_LOG("screen %f; %f", width, height);

//        s->transform.setX(width / 2.f);
//        s->transform.setY(height / 2.f);

//        s->transform.setWidth(size - 40.f);
//        s->transform.setHeight(size - 40.f);

//        _compass->transform.setX(width / 2.f);
//        _compass->transform.setY(height / 2.f);

//        _compass->transform.setWidth(size - 40.f);
//        _compass->transform.setHeight(size - 40.f);

//        GT_LOG("con %f; %f", _compass->transform.width(), _compass->transform.height());
    }

//    void tick() override
//    {
//        s->transform.setAngle(s->transform.angle() + 10 * time().delta());
//        tickChildren();
//    }
};

GT_RUN(DemoController);
