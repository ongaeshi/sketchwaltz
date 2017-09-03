#include "MrbTextureRegion.hpp"

#include "MrbColorF.hpp"
#include "Util.hpp"
#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/value.h"

//----------------------------------------------------------
namespace siv3druby {
namespace {
TextureRegion& toCpp(mrb_value self)
{
    return *((TextureRegion*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((TextureRegion*)p);
    }
}

struct mrb_data_type data_type = { "siv3d_texture", free };

mrb_value draw(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|ffo", &x, &y, &color);

    switch (argc)
    {
        case 3:
            toCpp(self).draw(x, y, Util::ToColor(mrb, color));
            break;
        case 2:
            toCpp(self).draw(x, y);
            break;
        default:
            toCpp(self).draw();
            break;
    }

    return mrb_nil_value();
}

}

//----------------------------------------------------------
void MrbTextureRegion::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "TextureRegion", mrb->object_class);

    mrb_define_method(mrb, cc, "draw", draw, MRB_ARGS_OPT(3));
}

//----------------------------------------------------------
mrb_value MrbTextureRegion::ToMrb(mrb_state *mrb, TextureRegion *ptr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "TextureRegion"), ptr);
}

//----------------------------------------------------------
mrb_value MrbTextureRegion::ToMrb(mrb_state *mrb, struct RClass *cc, TextureRegion *ptr)
{
    struct RData *data = mrb_data_object_alloc(mrb, cc, ptr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
TextureRegion* MrbTextureRegion::ToCpp(mrb_state *mrb, mrb_value value)
{
    return ToCpp(mrb, mrb_class_get(mrb, "TextureRegion"), value);
}

//----------------------------------------------------------
TextureRegion* MrbTextureRegion::ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value)
{
    if (!mrb_obj_is_instance_of(mrb, value, cc)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<TextureRegion*>(DATA_PTR(value));
}

}
