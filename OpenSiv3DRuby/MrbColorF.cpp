#include "MrbColorF.hpp"

#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"

//----------------------------------------------------------
namespace siv3druby {
namespace {
ColorF& toCpp(mrb_value self)
{
    return *((ColorF*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((ColorF*)p);
    }
}

struct mrb_data_type data_type = { "siv3d_colorf", free };

mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float r, g, b, a = 1.0;
    mrb_get_args(mrb, "fff|f", &r, &g, &b, &a);

    ColorF* obj = new ColorF(r, g, b, a);

    mrb_data_init(self, obj, &data_type);
    return self;
}

}

//----------------------------------------------------------
void MrbColorF::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "ColorF", mrb->object_class);

    mrb_define_method(mrb, cc, "initialize", initialize, MRB_ARGS_ARG(3, 1));
}

//----------------------------------------------------------
mrb_value MrbColorF::ToMrb(mrb_state *mrb, ColorF *ptr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "ColorF"), ptr);
}

//----------------------------------------------------------
mrb_value MrbColorF::ToMrb(mrb_state *mrb, struct RClass *cc, ColorF *ptr)
{
    struct RData *data = mrb_data_object_alloc(mrb, cc, ptr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
ColorF* MrbColorF::ToCpp(mrb_state *mrb, mrb_value value)
{
    return ToCpp(mrb, mrb_class_get(mrb, "ColorF"), value);
}

//----------------------------------------------------------
ColorF* MrbColorF::ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value)
{
    if (!mrb_obj_is_instance_of(mrb, value, cc)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<ColorF*>(DATA_PTR(value));
}

}
