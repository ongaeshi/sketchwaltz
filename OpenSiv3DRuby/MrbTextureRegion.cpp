#include "MrbTextureRegion.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<TextureRegion>::Inner MrbTextureRegion::fInner;

//----------------------------------------------------------
void MrbTextureRegion::Init(mrb_state* mrb)
{
    MrbTextureObject::Init(mrb, "TextureRegion");
}

}
