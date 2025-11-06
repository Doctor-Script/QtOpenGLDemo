#include "gtengine/gtengine.h"
#include "gtplatform/gtplatform.h"
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

        static GLubyte smiley[] = /* 16x16 smiley face */
        {
            0x03, 0xc0, /*       ****       */
            0x0f, 0xf0, /*     ********     */
            0x1e, 0x78, /*    ****  ****    */
            0x39, 0x9c, /*   ***  **  ***   */
            0x77, 0xee, /*  *** ****** ***  */
            0x6f, 0xf6, /*  ** ******** **  */
            0xff, 0xff, /* **************** */
            0xff, 0xff, /* **************** */
            0xff, 0xff, /* **************** */
            0xff, 0xff, /* **************** */
            0x73, 0xce, /*  ***  ****  ***  */
            0x73, 0xce, /*  ***  ****  ***  */
            0x3f, 0xfc, /*   ************   */
            0x1f, 0xf8, /*    **********    */
            0x0f, 0xf0, /*     ********     */
            0x03, 0xc0  /*       ****       */
        };

//        auto arrow = resources().add<Texture>(Texture::Builder("mono").mono(smiley, 16, 16));
//        auto arrow = resources().get<Texture>("arrow-mark.png");
//        auto arrow = resources().get<Texture>("cube.png");
        auto arrow = resources().get<Texture>("folder/flower.jpg");
        _target = _bg->child<Sprite>(arrow);
        _overlay = child<Sprite>(arrow, Color::f(1.0f, 0.5f, 0.0f, 1.0f));


        auto font = resources().get<Font>("ua-sdf.fnt");
        float w = 200, h = 200;
        _place = child<Sprite>("");
        _place->transform.setWidth(w);
        _place->transform.setHeight(h);


        _text = child<Text>(font, 72)->str("Ab12.ІйаїЇ")->align(Text::H_RIGHT | Text::V_BOTTOM)->color(Color::blue());
        _text->transform.setWidth(w);
        _text->transform.setHeight(h);
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

        const float speed = 0;//-70.0f;
        _text->transform.setAngle(_text->transform.angle() + speed * time().delta());
        _place->transform.setAngle(_place->transform.angle() + speed * time().delta());
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
