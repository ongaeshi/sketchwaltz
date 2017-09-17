#include "MrbCircle.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Circle>::Inner MrbCircle::fInner;

//----------------------------------------------------------
void MrbCircle::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Circle");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, Cc(), "draw_frame", draw_frame, MRB_ARGS_OPT(2));
    mrb_define_method(mrb, Cc(), "draw_inner_outer", draw_inner_outer, MRB_ARGS_ARG(2, 1));
}

//----------------------------------------------------------
mrb_value MrbCircle::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, r;
    mrb_get_args(mrb, "fff", &x, &y, &r);

    Initialize(self, new Circle(x, y, r));
    return self;
}

//----------------------------------------------------------
mrb_value MrbCircle::draw(mrb_state *mrb, mrb_value self)
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

//----------------------------------------------------------
mrb_value MrbCircle::draw_frame(mrb_state *mrb, mrb_value self)
{
    mrb_float thickness;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|fo", &thickness, &color);

    switch (argc)
    {
        case 2:
            Self(self).drawFrame(thickness, Util::ToColor(mrb, color));
            break;
        case 1:
            Self(self).drawFrame(thickness);
            break;
        default:
            Self(self).drawFrame();
            break;
    }

    return mrb_nil_value();
}

//----------------------------------------------------------
mrb_value MrbCircle::draw_inner_outer(mrb_state *mrb, mrb_value self)
{
    mrb_float inner_thickness, outer_thickness;
    mrb_value color;
    int argc = mrb_get_args(mrb, "ff|o",
        &inner_thickness,
        &outer_thickness,
        &color
        );

    switch (argc)
    {
        case 3:
            Self(self).drawFrame(inner_thickness, outer_thickness, Util::ToColor(mrb, color));
            break;
        case 2:
            Self(self).drawFrame(inner_thickness, outer_thickness);
            break;
    }

    return mrb_nil_value();
}

}
