#include "MrbDrawableText.hpp"

#include "MrbColorF.hpp"
#include "MrbVec2.hpp"
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
    mrb_value pos, color;
    int argc = mrb_get_args(mrb, "|oo", &pos, &color);

    switch (argc)
    {
        case 2:
            toCpp(self).draw(
                *MrbVec2::ToCpp(mrb, pos),
                *MrbColorF::ToCpp(mrb, color)
                );
            break;
        case 1:
            toCpp(self).draw(
                *MrbVec2::ToCpp(mrb, pos)
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
    mrb_value pos, color;
    int argc = mrb_get_args(mrb, "|oo", &pos, &color);

    switch (argc)
    {
        case 2:
            toCpp(self).drawAt(
                *MrbVec2::ToCpp(mrb, pos),
                *MrbColorF::ToCpp(mrb, color)
                );
            break;
        case 1:
            toCpp(self).drawAt(
                *MrbVec2::ToCpp(mrb, pos)
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

    mrb_define_method(mrb, cc, "draw", draw, MRB_ARGS_OPT(2));
    mrb_define_method(mrb, cc, "draw_at", draw_at, MRB_ARGS_OPT(2));
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
