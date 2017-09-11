#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbPoint
    : public MrbObject<Point>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value initialize(mrb_state *mrb, mrb_value self);
    static mrb_value x(mrb_state *mrb, mrb_value self);
    static mrb_value y(mrb_state *mrb, mrb_value self);
    static mrb_value to_s(mrb_state *mrb, mrb_value self);

};
}
