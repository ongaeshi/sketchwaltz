#include "MrbTextureRegion.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<TextureRegion>::Inner MrbTextureRegion::fInner;

//----------------------------------------------------------
void MrbTextureRegion::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "TextureRegion");

    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(3));
    mrb_define_method(mrb, Cc(), "mirror", mirror, MRB_ARGS_NONE());
}

//----------------------------------------------------------
mrb_value MrbTextureRegion::draw(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|ffo", &x, &y, &color);

    switch (argc)
    {
        case 3:
            Self(self).draw(x, y, Util::ToColor(mrb, color));
            break;
        case 2:
            Self(self).draw(x, y);
            break;
        default:
            Self(self).draw();
            break;
    }

    return mrb_nil_value();
}

//----------------------------------------------------------
mrb_value MrbTextureRegion::mirror(mrb_state *mrb, mrb_value self)
{
    return ToMrb(
        mrb,
        new TextureRegion(Self(self).mirror())
        );
}

}
