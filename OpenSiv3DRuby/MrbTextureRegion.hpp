#pragma once

#include "MrbTextureObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbTextureRegion
    : public MrbTextureObject<TextureRegion>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value draw(mrb_state *mrb, mrb_value self);
};
}
