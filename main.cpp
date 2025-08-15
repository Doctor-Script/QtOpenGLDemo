#include "gtengine/gtengine.h"
using namespace gt;


class Compass : public Node2D
{
    const gref<Sprite> _bg;
    gref<Sprite> _target;
    gref<Sprite> _overlay;
    gref<Text> _text;
    gref<Sprite> _place;

public:
    explicit Compass(Node::Initalizer initalizer) : Node2D(initalizer), _bg(child<Sprite>("compass-circle.png"))
    {
//        _bg = child<Sprite>("compass-circle.png");

        auto arrow = resources().get<Texture>("arrow-mark.png");
        _target = _bg->child<Sprite>(arrow);
        _overlay = child<Sprite>(arrow, Color::f(1.0f, 0.5f, 0.0f, 1.0f));


//        float a = 20;
        _place = child<Sprite>("");
//        place->transform.setAngle(a);

        auto font = resources().get<Font>("digits");
        _text = child<Text>(font);
        _text->_value = "561";
//        _text->transform.setAngle(a);
    }

    void start() override
    {
//        _bg = child<Sprite>("compass-circle.png");

//        auto arrow = resources().get<Texture>("arrow-mark.png");
//        _target = _bg->child<Sprite>(arrow);
//        _overlay = child<Sprite>(arrow);
    }

    void layout() override
    {
        float size = transform.width();

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
        _bg->transform.setAngle(_bg->transform.angle() + 10 * time().delta());

//        _text->transform.setAngle(_text->transform.angle() - 10 * time().delta());
//        _place->transform.setAngle(_place->transform.angle() - 10 * time().delta());
    }
};


class DemoController : public Controller
{
    gref<Compass> _compass;
public:
    explicit DemoController(Platform& platform) : Controller(platform)
    {
        _compass = canvas()->child<Compass>();
    }

    void start() override
    {
//        _compass = canvas()->child<Compass>();
    }

    void layout() override
    {
        float width = screen().width();
        float height = screen().height();
        float size = width < height ? width : height - 40.f;

        _compass->transform.setWidth(size);
        _compass->transform.setHeight(size);

        _compass->transform.setX(width / 2.f);
        _compass->transform.setY(height / 2.f);
    }

    void tick() override
    {
    }
};

GT_RUN(DemoController);
