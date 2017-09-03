#include "MrbEmoji.hpp"

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
Emoji& toCpp(mrb_value self)
{
    return *((Emoji*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((Emoji*)p);
    }
}

struct mrb_data_type data_type = { "siv3d_texture", free };

mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value src;
    mrb_get_args(mrb, "o", &src);

    Emoji* obj;

    if (mrb_string_p(src)) {
        obj = new Emoji(CharacterSet::FromUTF8(mrb_string_value_ptr(mrb, src)));
    } else {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    mrb_data_init(self, obj, &data_type);
    return self;
}
}

//----------------------------------------------------------
void MrbEmoji::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "Emoji", mrb->object_class);

    mrb_define_method(mrb, cc, "initialize", initialize, MRB_ARGS_REQ(1));
}

//----------------------------------------------------------
mrb_value MrbEmoji::ToMrb(mrb_state *mrb, Emoji *ptr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "Emoji"), ptr);
}

//----------------------------------------------------------
mrb_value MrbEmoji::ToMrb(mrb_state *mrb, struct RClass *cc, Emoji *ptr)
{
    struct RData *data = mrb_data_object_alloc(mrb, cc, ptr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
Emoji* MrbEmoji::ToCpp(mrb_state *mrb, mrb_value value)
{
    return ToCpp(mrb, mrb_class_get(mrb, "Emoji"), value);
}

//----------------------------------------------------------
Emoji* MrbEmoji::ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value)
{
    if (!mrb_obj_is_instance_of(mrb, value, cc)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<Emoji*>(DATA_PTR(value));
}

//----------------------------------------------------------
bool MrbEmoji::IsInstance(mrb_state *mrb, mrb_value value)
{
    return mrb_obj_is_instance_of(mrb, value, mrb_class_get(mrb, "Emoji"));
}

}
