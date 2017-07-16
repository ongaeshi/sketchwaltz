#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbFont {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, Font *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, Font *ptr);
        static Font* ToCpp(mrb_state *mrb, mrb_value value);
        static Font* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
