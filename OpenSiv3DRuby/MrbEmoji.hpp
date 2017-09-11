#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbEmoji
    : public MrbObject<Emoji>
{
public:
    static void Init(mrb_state *mrb);
    static bool IsInstance(mrb_state *mrb, mrb_value value);

private:
    static mrb_value initialize(mrb_state *mrb, mrb_value self);
};
}
