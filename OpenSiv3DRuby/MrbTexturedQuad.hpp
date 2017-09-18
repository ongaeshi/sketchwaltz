#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbTexturedQuad
    : public MrbObject<TexturedQuad>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value draw(mrb_state *mrb, mrb_value self);
};
}
