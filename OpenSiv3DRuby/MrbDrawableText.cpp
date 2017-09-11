#include "MrbDrawableText.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<DrawableText>::Inner MrbDrawableText::fInner;

//----------------------------------------------------------
void MrbDrawableText::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "DrawableText");

    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(3));
    mrb_define_method(mrb, Cc(), "draw_at", draw_at, MRB_ARGS_OPT(3));
}

//----------------------------------------------------------
mrb_value MrbDrawableText::draw(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|ffo", &x, &y, &color);

    switch (argc)
    {
        case 3:
            Self(self).draw(
                x,
                y,
                Util::ToColor(mrb, color)
                );
            break;
        case 2:
            Self(self).draw(
                x,
                y
                );
            break;
        default:
            Self(self).draw();
            break;
    }

    return mrb_nil_value();
}

//----------------------------------------------------------
mrb_value MrbDrawableText::draw_at(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|ffo", &x, &y, &color);

    switch (argc)
    {
        case 3:
            Self(self).drawAt(
                x,
                y,
                Util::ToColor(mrb, color)
                );
            break;
        case 2:
            Self(self).drawAt(
                x,
                y
                );
            break;
        default:
            Self(self).drawAt();
            break;
    }

    return mrb_nil_value();
}

}
