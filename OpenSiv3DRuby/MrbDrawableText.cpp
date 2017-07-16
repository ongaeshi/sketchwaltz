#include "MrbDrawableText.hpp"

#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"

//----------------------------------------------------------
namespace siv3druby {
namespace {
DrawableText& toCpp(mrb_value self)
{
    return *((DrawableText*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((DrawableText*)p);
    }
}

struct mrb_data_type data_type = { "siv3d_drawable_string", free };

mrb_value draw(mrb_state *mrb, mrb_value self)
{
    toCpp(self).draw();
    return mrb_nil_value();
}
}

//----------------------------------------------------------
void MrbDrawableText::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "DrawableText", mrb->object_class);

    mrb_define_method(mrb, cc, "draw", draw, MRB_ARGS_NONE());
}

//----------------------------------------------------------
mrb_value MrbDrawableText::ToMrb(mrb_state *mrb, DrawableText *ptr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "DrawableText"), ptr);
}

//----------------------------------------------------------
mrb_value MrbDrawableText::ToMrb(mrb_state *mrb, struct RClass *cc, DrawableText *ptr)
{
    struct RData *data = mrb_data_object_alloc(mrb, cc, ptr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
DrawableText* MrbDrawableText::ToCpp(mrb_state *mrb, mrb_value value)
{
    return ToCpp(mrb, mrb_class_get(mrb, "DrawableText"), value);
}

//----------------------------------------------------------
DrawableText* MrbDrawableText::ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value)
{
    if (!mrb_obj_is_instance_of(mrb, value, cc)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<DrawableText*>(DATA_PTR(value));
}

}
