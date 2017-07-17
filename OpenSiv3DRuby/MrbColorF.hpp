#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbColorF {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, ColorF *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, ColorF *ptr);
        static ColorF* ToCpp(mrb_state *mrb, mrb_value value);
        static ColorF* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
