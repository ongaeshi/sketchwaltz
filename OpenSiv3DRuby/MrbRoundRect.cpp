#include "MrbRoundRect.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<RoundRect>::Inner MrbRoundRect::fInner;

//----------------------------------------------------------
void MrbRoundRect::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "RoundRect");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(5));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(1));
}

//----------------------------------------------------------
mrb_value MrbRoundRect::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h, r;
    mrb_get_args(mrb, "fffff", &x, &y, &w, &h, &r);

    Initialize(self, new RoundRect(x, y, w, h, r));
    return self;
}

//----------------------------------------------------------
mrb_value MrbRoundRect::draw(mrb_state *mrb, mrb_value self)
{
    mrb_value color;
    int argc = mrb_get_args(mrb, "|o", &color);

    switch (argc)
    {
        case 1:
            Self(self).draw(Util::ToColor(mrb, color));
            break;
        default:
            Self(self).draw();
            break;
    }

    return mrb_nil_value();
}

}
