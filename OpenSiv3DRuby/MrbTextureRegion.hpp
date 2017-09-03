#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbTextureRegion {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, TextureRegion *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, TextureRegion *ptr);
        static TextureRegion* ToCpp(mrb_state *mrb, mrb_value value);
        static TextureRegion* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
