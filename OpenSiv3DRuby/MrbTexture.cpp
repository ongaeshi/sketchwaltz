#include "MrbTexture.hpp"

#include "MrbEmoji.hpp"
#include "MrbTextureRegion.hpp"
#include "Util.hpp"
#include "mruby/string.h"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Texture>::Inner MrbTexture::fInner;

//----------------------------------------------------------
void MrbTexture::Init(mrb_state* mrb)
{
    MrbTextureObject::Init(mrb, "Texture");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_ARG(1, 1));
    mrb_define_method(mrb, Cc(), "[]", aref, MRB_ARGS_REQ(4));
}

//----------------------------------------------------------
mrb_value MrbTexture::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value src;
    mrb_int desc = static_cast<int>(TextureDesc::Unmipped);
    mrb_get_args(mrb, "o|i", &src, &desc);

    Texture* obj;

    if (mrb_string_p(src)) {
        obj = new Texture(CharacterSet::FromUTF8(mrb_string_value_ptr(mrb, src)), static_cast<TextureDesc>(desc));
    } else if (MrbEmoji::IsInstance(mrb, src)) {
        obj = new Texture(*MrbEmoji::ToCpp(mrb, src), static_cast<TextureDesc>(desc));
    } else {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    Initialize(self, obj);
    return self;
}

//----------------------------------------------------------
mrb_value MrbTexture::aref(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h;
    mrb_get_args(mrb, "ffff", &x, &y, &w, &h);

    return MrbTextureRegion::ToMrb(
        mrb,
        new TextureRegion(Self(self)(x, y, w, h))
        );
}

}
