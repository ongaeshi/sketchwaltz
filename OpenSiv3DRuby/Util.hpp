#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
class Util {
public:
    static Color ToColor(mrb_state *mrb, mrb_value obj);
    static Vec2 ToVec2(mrb_state *mrb, mrb_value obj);
};
}
