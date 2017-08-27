#include "MrbDrawableText.hpp"

#include "MrbColorF.hpp"
#include "MrbVec2.hpp"
#include "Util.hpp"
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
    mrb_float x, y;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|ffo", &x, &y, &color);

    switch (argc)
    {
        case 3:
            toCpp(self).draw(
                x,
                y,
                Util::ToColor(mrb, color)
                );
            break;
        case 2:
            toCpp(self).draw(
                x,
                y
                );
            break;
        default:
            toCpp(self).draw();
            break;
    }

    return mrb_nil_value();
}

mrb_value draw_at(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|ffo", &x, &y, &color);

    switch (argc)
    {
        case 3:
            toCpp(self).drawAt(
                x,
                y,
                Util::ToColor(mrb, color)
                );
            break;
        case 2:
            toCpp(self).drawAt(
                x,
                y
                );
            break;
        default:
            toCpp(self).drawAt();
            break;
    }

    return mrb_nil_value();
}

}

//----------------------------------------------------------
void MrbDrawableText::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "DrawableText", mrb->object_class);

    mrb_define_method(mrb, cc, "draw", draw, MRB_ARGS_OPT(3));
    mrb_define_method(mrb, cc, "draw_at", draw_at, MRB_ARGS_OPT(3));
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
