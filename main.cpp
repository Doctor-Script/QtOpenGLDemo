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
        //value = fmod(value + 360.0f, 360.0f);
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
        GT_ASSERT(transform.width() == transform.height());
        float size = transform.width();

        _circle->transform.size(size, size);
        _target->transform.size(0.22f * size, 0.08f * size).y(size * 0.4f).angle(270.0f);
        _self->transform.size(0.29f * size, 0.22f * size).y(0.19f * size).angle(90.0f);

        int fontSize = 0.13f * size;
        _selfLabel->fontSize(fontSize);
        _selfLabel->transform.y(-0.02 * size);

        _targetLabel->fontSize(fontSize);
        _targetLabel->transform.y(-0.15 * size);
    }

    void tick() override
    {
        _selfDeg += 10 * time().delta();
        _selfDeg = fmod(_selfDeg + 360.0f, 360.0f);
        _targeDeg -= 10 * time().delta();
        _targeDeg = fmod(_targeDeg + 360.0f, 360.0f);

        _selfLabel->set(_selfDeg);
        _targetLabel->set(_targeDeg);

        _circle->transform.angle(_selfDeg);

        _target->transform.position(Vector2(0.0f, transform.width() * 0.4f).rotate(-_targeDeg));
        _target->transform.angle(-_targeDeg + 270.0f);
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

        _compass->transform.position(width * 0.5f, height * 0.5f).size(size, size);
    }

    void tick() override
    {
    }
};


GT_MAIN (
    GT_IF_QT(GT_SETTINGS = { .width = 640, .height = 480, .foolscreen = false });
    GT_RUN(DemoController);
)
