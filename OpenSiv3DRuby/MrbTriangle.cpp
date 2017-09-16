#include "MrbTriangle.hpp"

#include "MrbVec2.hpp"
#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Triangle>::Inner MrbTriangle::fInner;

//----------------------------------------------------------
void MrbTriangle::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Triangle");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(1));
}

//----------------------------------------------------------
mrb_value MrbTriangle::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value p0, p1, p2;
    mrb_get_args(mrb, "ooo", &p0, &p1, &p2);

    Initialize(self, new Triangle(Util::ToVec2(mrb, p0), Util::ToVec2(mrb, p1), Util::ToVec2(mrb, p2)));
    return self;
}

//----------------------------------------------------------
mrb_value MrbTriangle::draw(mrb_state *mrb, mrb_value self)
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
