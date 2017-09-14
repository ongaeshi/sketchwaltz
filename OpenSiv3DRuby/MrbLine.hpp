#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbLine
    : public MrbObject<Line>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value initialize(mrb_state *mrb, mrb_value self);
    static mrb_value draw(mrb_state *mrb, mrb_value self);
    static mrb_value draw_arrow(mrb_state *mrb, mrb_value self);
};
}
