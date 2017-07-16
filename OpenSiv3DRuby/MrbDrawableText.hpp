#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbDrawableText {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, DrawableText *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, DrawableText *ptr);
        static DrawableText* ToCpp(mrb_state *mrb, mrb_value value);
        static DrawableText* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
