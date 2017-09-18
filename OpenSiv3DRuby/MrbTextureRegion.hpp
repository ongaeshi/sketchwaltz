#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbTextureRegion
    : public MrbObject<TextureRegion>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value draw(mrb_state *mrb, mrb_value self);
    static mrb_value flip(mrb_state *mrb, mrb_value self);
    static mrb_value mirror(mrb_state *mrb, mrb_value self);
    static mrb_value scale(mrb_state *mrb, mrb_value self);
};
}
