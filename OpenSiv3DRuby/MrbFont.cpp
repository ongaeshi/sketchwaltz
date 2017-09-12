#include "MrbFont.hpp"

#include "MrbDrawableText.hpp"
#include "mruby/string.h"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Font>::Inner MrbFont::fInner;

//----------------------------------------------------------
void MrbFont::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Font");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, Cc(), "[]", aref, MRB_ARGS_REQ(1));
}

//----------------------------------------------------------
mrb_value MrbFont::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_int size;
    mrb_get_args(mrb, "i", &size);

    Initialize(self, new Font(size));
    return self;
}

//----------------------------------------------------------
mrb_value MrbFont::aref(mrb_state *mrb, mrb_value self)
{
    mrb_value str;
    mrb_get_args(mrb, "S", &str);

    auto cstr = mrb_string_value_ptr(mrb, str);
    auto dstr = new DrawableText(Self(self)(CharacterSet::FromUTF8(cstr)));
    return MrbDrawableText::ToMrb(mrb, dstr);
}

}
