#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbVec2 {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, Vec2 *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, Vec2 *ptr);
        static Vec2* ToCpp(mrb_state *mrb, mrb_value value);
        static Vec2* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
