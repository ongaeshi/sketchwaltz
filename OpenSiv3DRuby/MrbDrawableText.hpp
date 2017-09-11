#pragma once

#include "MrbObject.hpp"

//----------------------------------------------------------
namespace siv3druby {
class MrbDrawableText
    : public MrbObject<DrawableText>
{
public:
    static void Init(mrb_state *mrb);

private:
    static mrb_value MrbDrawableText::draw(mrb_state *mrb, mrb_value self);
    static mrb_value MrbDrawableText::draw_at(mrb_state *mrb, mrb_value self);
};
}
