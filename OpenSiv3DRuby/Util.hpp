#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
class Util {
public:
    static Color ToColor(mrb_state *mrb, mrb_value obj);
};
}
