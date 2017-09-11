#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbVec2
    : public MrbObject<Vec2>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value initialize(mrb_state *mrb, mrb_value self);
    static mrb_value x(mrb_state *mrb, mrb_value self);
    static mrb_value y(mrb_state *mrb, mrb_value self);
};
}
