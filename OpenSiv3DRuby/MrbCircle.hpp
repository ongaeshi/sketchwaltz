#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbCircle {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, Circle *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, Circle *ptr);
        static Circle* ToCpp(mrb_state *mrb, mrb_value value);
        static Circle* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
