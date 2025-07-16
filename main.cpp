#include "gtengine/gtengine.h"
using namespace gt;


class Compass : public Node2D
{
    gref<Sprite> _bg;
    gref<Sprite> _target;
    gref<Sprite> _overlay;
public:
    explicit Compass(Node::Initalizer initalizer) : Node2D(initalizer)
    {
        // TODO Can I create childer here?
    }

    void start() override
    {
        auto circle = resources().get<Texture>("compass-circle.png");
        _bg = child<Sprite>(circle);

        _target = _bg->child<Sprite>("arrow-mark.png");

        _overlay = child<Sprite>("arrow-mark.png");
    }

    void layout() override
    {
        auto canvas = s_cast<Canvas>(parent());//->to<Canvas>();

        float width = canvas->width();
        float height = canvas->height();
        float size = width < height ? width : height - 40.f;


        transform.setX(width / 2.f);
        transform.setY(height / 2.f);

        transform.setWidth(size);
        transform.setHeight(size);

        _bg->transform.setWidth(transform.width());
        _bg->transform.setHeight(transform.height());

        _target->transform.setWidth(0.2f * size);
        _target->transform.setHeight(0.1f * size);
        _target->transform.setX(size * 0.5f);
        _target->transform.setAngle(180.0f);

        _overlay->transform.setWidth(0.3f * size);
        _overlay->transform.setHeight(0.3f * size);
        _overlay->transform.setAngle(90.0f);
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
    explicit DemoController(Platform& platform) : Controller(platform)
    {
//        _compass = canvas()->child<Compass>();
    }

    void start() override
    {
        Controller::start();
        _compass = canvas()->child<Compass>();
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
