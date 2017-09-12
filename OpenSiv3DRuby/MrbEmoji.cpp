#include "MrbEmoji.hpp"

#include "Util.hpp"
#include "mruby/string.h"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Emoji>::Inner MrbEmoji::fInner;

//----------------------------------------------------------
void MrbEmoji::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Emoji");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(1));
}

//----------------------------------------------------------
mrb_value MrbEmoji::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value src;
    mrb_get_args(mrb, "o", &src);

    Emoji* obj;

    if (mrb_string_p(src)) {
        obj = new Emoji(CharacterSet::FromUTF8(mrb_string_value_ptr(mrb, src)));
    } else {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    Initialize(self, obj);
    return self;
}

}
