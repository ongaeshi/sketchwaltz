#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbTexture {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, Texture *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, Texture *ptr);
        static Texture* ToCpp(mrb_state *mrb, mrb_value value);
        static Texture* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
