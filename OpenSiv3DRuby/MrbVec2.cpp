#include "MrbVec2.hpp"

#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"

//----------------------------------------------------------
namespace siv3druby {
namespace {
Vec2& toCpp(mrb_value self)
{
    return *((Vec2*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((Vec2*)p);
    }
}

struct mrb_data_type data_type = { "siv3d_vec2", free };

mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_get_args(mrb, "ff", &x, &y);

    Vec2* obj = new Vec2(x, y);

    mrb_data_init(self, obj, &data_type);
    return self;
}

}

//----------------------------------------------------------
void MrbVec2::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "Vec2", mrb->object_class);

    mrb_define_method(mrb, cc, "initialize", initialize, MRB_ARGS_REQ(2));
}

//----------------------------------------------------------
mrb_value MrbVec2::ToMrb(mrb_state *mrb, Vec2 *ptr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "Vec2"), ptr);
}

//----------------------------------------------------------
mrb_value MrbVec2::ToMrb(mrb_state *mrb, struct RClass *cc, Vec2 *ptr)
{
    struct RData *data = mrb_data_object_alloc(mrb, cc, ptr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
Vec2* MrbVec2::ToCpp(mrb_state *mrb, mrb_value value)
{
    return ToCpp(mrb, mrb_class_get(mrb, "Vec2"), value);
}

//----------------------------------------------------------
Vec2* MrbVec2::ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value)
{
    if (!mrb_obj_is_instance_of(mrb, value, cc)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<Vec2*>(DATA_PTR(value));
}

}
