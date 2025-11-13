#include "gtplatform/gt.h"
using namespace gt;


class Compass : public Node2D
{
    const gref<Sprite> _bg;
    gref<Sprite> _target;
    gref<Sprite> _overlay;
    gref<Text> _text;
    gref<Sprite> _place;

    Font::AsyncBuilder* _fontBuilder;

public:
    explicit Compass(Node::Initalizer initalizer) : Node2D(initalizer), _bg(child<Sprite>("compass-circle.png")), b(nullptr)
    {
        auto arrow = resources().icon();
//        auto arrow = resources().get<Texture>("arrow-mark.png");

        _target = _bg->child<Sprite>();
        _overlay = child<Sprite>(arrow, Color::f(1.0f, 0.5f, 0.0f, 1.0f));

//        auto font = resources().get<Font>("ua-sdf.fnt");

        GT_LOG("font");

//        _place = child<Sprite>("");
//        _place->transform.setWidth(w);
//        _place->transform.setHeight(h);

        _text = child<Text>()->str("Ab12.ІйаїЇ")->align(Text::H_RIGHT | Text::V_BOTTOM)->color(Color::blue());
//        _text = child<Text>(font, 72)->str("Ab12.ІйаїЇ")->align(Text::H_RIGHT | Text::V_BOTTOM)->color(Color::blue());




        _fontBuilder = new Font::AsyncBuilder(resources(), "ua-sdf.fnt");
        resources().loadTo<Font>(*_fontBuilder);

    }

    void start() override
    {
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

        float w = 200, h = 200;
        _text->transform.setWidth(w);
        _text->transform.setHeight(h);
    }

    int _tim = 0;
    bool _done = false;
    Texture::AsyncBuilder* b;

    void tick() override
    {
        if (_fontBuilder != nullptr) {
            auto font = _fontBuilder->build();
            if (font != nullptr) {
                _text->font(font);
                resources().add(font);

                delete _fontBuilder;
                _fontBuilder = nullptr;
            }
        }

        _tim += time().deltaMS();
        if (_tim > 1000 && !_done) {
            b = new Texture::AsyncBuilder(resources(), "arrow-mark.png");
            resources().loadTo<Texture>(*b);
            _done = true;
        }

        if (b != nullptr) {

            auto tex = b->build();
            if (tex != nullptr) {
                resources().add<Texture>(tex);
                _target->texture(tex);
                GT_LOG("!!!!!!!!!!!!!!!!!!!!!!!!!!!! DOOONE");
                delete b;
                b = nullptr;
            }
        }



        _bg->transform.setAngle(_bg->transform.angle() + 10 * time().delta());
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


GT_MAIN (
    GT_IF_QT(GT_SETTINGS = { .width = 640, .height = 480, .foolscreen = false });
    GT_RUN(DemoController);
)
