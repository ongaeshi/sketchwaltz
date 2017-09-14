#include "MrbLine.hpp"

#include "MrbVec2.hpp"
#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Line>::Inner MrbLine::fInner;

//----------------------------------------------------------
void MrbLine::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Line");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(2));
    mrb_define_method(mrb, Cc(), "draw_arrow", draw_arrow, MRB_ARGS_OPT(2));
}

//----------------------------------------------------------
mrb_value MrbLine::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float x0, y0, x1, y1;
    mrb_get_args(mrb, "ffff", &x0, &y0, &x1, &y1);

    Initialize(self, new Line(x0, y0, x1, y1));
    return self;
}

//----------------------------------------------------------
mrb_value MrbLine::draw(mrb_state *mrb, mrb_value self)
{
    mrb_float thickness;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|fo", &thickness, &color);

    switch (argc)
    {
        case 2:
            Self(self).draw(thickness, Util::ToColor(mrb, color));
            break;
        case 1:
            Self(self).draw(thickness);
            break;
        default:
            Self(self).draw();
            break;
    }

    return mrb_nil_value();
}

//----------------------------------------------------------
mrb_value MrbLine::draw_arrow(mrb_state *mrb, mrb_value self)
{
    mrb_float width;
    mrb_value head_size, color;
    int argc = mrb_get_args(mrb, "|foo", &width, &head_size, &color);

    switch (argc)
    {
        case 3:
            Self(self).drawArrow(width, Util::ToVec2(mrb, head_size), Util::ToColor(mrb, color));
            break;
        case 2:
            Self(self).drawArrow(width, Util::ToVec2(mrb, head_size));
            break;
        case 1:
            Self(self).drawArrow(width);
            break;
        default:
            Self(self).drawArrow();
            break;
    }

    return mrb_nil_value();
}

}
