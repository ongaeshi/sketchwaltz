#include "MrbCamera2D.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Camera2D>::Inner MrbCamera2D::fInner;

//----------------------------------------------------------
void MrbCamera2D::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Camera2D");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_NONE());
    mrb_define_method(mrb, Cc(), "transform", transform, MRB_ARGS_BLOCK());
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

}
