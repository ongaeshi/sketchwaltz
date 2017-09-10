#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {

//----------------------------------------------------------
class MrbRect
    : public MrbManager<Rect>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value Initialize(mrb_state *mrb, mrb_value self);
    static mrb_value Draw(mrb_state *mrb, mrb_value self);
};
}
