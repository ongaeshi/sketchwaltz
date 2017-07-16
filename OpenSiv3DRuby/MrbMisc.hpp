#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbMisc {
    public:
        static void Init(mrb_state *mrb);
    };
}
