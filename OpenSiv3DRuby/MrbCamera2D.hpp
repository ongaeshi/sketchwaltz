#pragma once

#include "MrbObject.hpp"
#include "HamFramework.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbCamera2D
    : public MrbObject<Camera2D>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value initialize(mrb_state *mrb, mrb_value self);
    static mrb_value transform(mrb_state *mrb, mrb_value self);
};
}
