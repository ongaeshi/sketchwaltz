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
    MrbObject::Init(mrb, "Texture");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_ARG(1, 1));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(3));
    mrb_define_method(mrb, Cc(), "resize", resize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, Cc(), "scale", scale, MRB_ARGS_REQ(2));
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

    mrb_data_init(self, obj, DataType());
    return self;
}

//----------------------------------------------------------
mrb_value MrbTexture::draw(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|ffo", &x, &y, &color);

    switch (argc)
    {
        case 3:
            ToCpp(self).draw(x, y, Util::ToColor(mrb, color));
            break;
        case 2:
            ToCpp(self).draw(x, y);
            break;
        default:
            ToCpp(self).draw();
            break;
    }

    return mrb_nil_value();
}

//----------------------------------------------------------
mrb_value MrbTexture::resize(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    int argc = mrb_get_args(mrb, "ff", &x, &y);

    return MrbTextureRegion::ToMrb(
        mrb,
        new TextureRegion(ToCpp(self).resize(x, y))
    );
}

//----------------------------------------------------------
mrb_value MrbTexture::scale(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    int argc = mrb_get_args(mrb, "ff", &x, &y);

    return MrbTextureRegion::ToMrb(
        mrb,
        new TextureRegion(ToCpp(self).scale(x, y))
        );
}

}
