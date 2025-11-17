#include "gtplatform/gt.h"
using namespace gt;

#include <cmath>
#include "gtengine/utils/str.h"


struct Config
{
    static const Color self;
    static const Color target;
};

const Color Config::self = Color::green();
const Color Config::target = Color::red();



class CompassLabel : public Text
{
    char _buffer[sizeof("-000.00")];

public:
    explicit CompassLabel(Node::Initalizer initalizer, gref<Font> font, Color color) : Text(initalizer, font) {
        str(_buffer)->color(color);
    }

    void set(float value)
    {
        value = fmod(value + 360.0f, 360.0f);
        str_from_float(_buffer, "%06.2f", value);
    }
};

class Compass : public Node2D
{
    gref<Sprite> _circle;
    gref<Sprite> _target;
    gref<Sprite> _self;

    gref<CompassLabel> _selfLabel;
    gref<CompassLabel> _targetLabel;

    float _selfDeg = 0.0f;
    float _targeDeg = 0.0f;

public:
    explicit Compass(Node::Initalizer initalizer) : Node2D(initalizer)
    {
        _circle = child<Sprite>("compass-circle.png");

        auto mark = resources().get<Texture>("arrow-mark.png");
        _self = child<Sprite>(mark)->color(Config::self);
        _target = _circle->child<Sprite>(mark)->color(Config::target);

        auto font = resources().get<Font>("ua-sdf.fnt");
        _selfLabel = child<CompassLabel>(font, Config::self);
        _targetLabel = child<CompassLabel>(font, Config::target);
    }

//    void start() override { }

    void layout() override
    {
        float size = transform.width();

        _circle->transform.setWidth(transform.width());
        _circle->transform.setHeight(transform.height());

        _target->transform.setWidth(0.22f * size);
        _target->transform.setHeight(0.08f * size);
        _target->transform.setY(size * 0.4f);
        _target->transform.setAngle(270.0f);

        _self->transform.setSize(0.29f * size, 0.22f * size);
        _self->transform.setY(size * 0.19f);
        _self->transform.setAngle(90.0f);

        int fontSize = 0.13f * size;
        _selfLabel->fontSize(fontSize);
        _selfLabel->transform.setY(-0.02 * size);

        _targetLabel->fontSize(fontSize);
        _targetLabel->transform.setY(-0.15 * size);
    }

    void tick() override
    {
        _selfDeg += 10 * time().delta();
        _targeDeg -= 10 * time().delta();

        _selfLabel->set(_selfDeg);
        _targetLabel->set(_targeDeg);

        _circle->transform.setAngle(_selfDeg);

        _target->transform.setPosition(Vector2(0.0f, transform.width() * 0.4f).rotate(-_targeDeg));
        _target->transform.setAngle(-_targeDeg + 270.0f);
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

//    void start() override { }

    void layout() override
    {
        float width = screen().width();
        float height = screen().height();
        float size = width < height ? width : height;
        size *= 0.95f;

        _compass->transform.setWidth(size);
        _compass->transform.setHeight(size);

        _compass->transform.setX(width / 2.f);
        _compass->transform.setY(height / 2.f);
    }

    void tick() override
    {
    }
};


GT_MAIN (
    GT_IF_QT(GT_SETTINGS = { .width = 640, .height = 480, .foolscreen = false });
    GT_RUN(DemoController);
)
