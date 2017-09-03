#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbEmoji {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, Emoji *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, Emoji *ptr);
        static Emoji* ToCpp(mrb_state *mrb, mrb_value value);
        static Emoji* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
        static bool IsInstance(mrb_state *mrb, mrb_value value);
    };
}
