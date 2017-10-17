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
    mrb_define_method(mrb, Cc(), "height", height, MRB_ARGS_NONE());
    mrb_define_method(mrb, Cc(), "map", map, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, Cc(), "repeat", repeat, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, Cc(), "uv", uv, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, Cc(), "width", width, MRB_ARGS_NONE());
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

//----------------------------------------------------------
mrb_value MrbTexture::height(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, Self(self).height());
}

//----------------------------------------------------------
mrb_value MrbTexture::map(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_get_args(mrb, "ff", &x, &y);

    return MrbTextureRegion::ToMrb(
        mrb,
        new TextureRegion(Self(self).map(x, y))
        );
}

//----------------------------------------------------------
mrb_value MrbTexture::repeat(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_get_args(mrb, "ff", &x, &y);

    return MrbTextureRegion::ToMrb(
        mrb,
        new TextureRegion(Self(self).repeat(x, y))
        );
}

//----------------------------------------------------------
mrb_value MrbTexture::uv(mrb_state *mrb, mrb_value self)
{
    mrb_float u, v, w, h;
    mrb_get_args(mrb, "ffff", &u, &v, &w, &h);

    return MrbTextureRegion::ToMrb(
        mrb,
        new TextureRegion(Self(self).uv(u, v, w, h))
        );
}

//----------------------------------------------------------
mrb_value MrbTexture::width(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, Self(self).width());
}
}
