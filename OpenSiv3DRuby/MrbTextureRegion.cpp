#include "MrbTextureRegion.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<TextureRegion>::Inner MrbTextureRegion::fInner;

//----------------------------------------------------------
void MrbTextureRegion::Init(mrb_state* mrb)
{
    MrbTextureObject::Init(mrb, "TextureRegion");

    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(3));
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

}
