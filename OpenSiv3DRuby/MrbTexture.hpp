#pragma once

#include "MrbTextureObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbTexture
    : public MrbTextureObject<Texture>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value initialize(mrb_state *mrb, mrb_value self);
    static mrb_value aref(mrb_state *mrb, mrb_value self);
    static mrb_value map(mrb_state *mrb, mrb_value self);
    static mrb_value repeat(mrb_state *mrb, mrb_value self);
};
}
