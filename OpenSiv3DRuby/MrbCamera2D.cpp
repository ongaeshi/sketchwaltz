#include "MrbCamera2D.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Camera2D>::Inner MrbCamera2D::fInner;

//----------------------------------------------------------
void MrbCamera2D::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Camera2D");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_NONE());
    mrb_define_method(mrb, Cc(), "transform", transform, MRB_ARGS_BLOCK());
    mrb_define_method(mrb, Cc(), "update", update, MRB_ARGS_NONE());
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(1));
}

//----------------------------------------------------------
mrb_value MrbCamera2D::initialize(mrb_state *mrb, mrb_value self)
{
    Initialize(self, new Camera2D());
    return self;
}

//----------------------------------------------------------
mrb_value MrbCamera2D::transform(mrb_state *mrb, mrb_value self)
{
    mrb_value blk;
    mrb_get_args(mrb, "&", &blk);

    {
        auto t = Self(self).createTransformer();
        mrb_value ret = mrb_yield_argv(mrb, blk, 0, NULL);
        return ret;
    }
}

//----------------------------------------------------------
mrb_value MrbCamera2D::update(mrb_state *mrb, mrb_value self)
{
    Self(self).update();
    return self;
}

//----------------------------------------------------------
mrb_value MrbCamera2D::draw(mrb_state *mrb, mrb_value self)
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

    return self;
}

}
