#pragma once

#include <Siv3D.hpp>
#include "mruby.h"

//----------------------------------------------------------
namespace siv3druby {
    class MrbPoint {
    public:
        static void Init(mrb_state *mrb);
        static mrb_value ToMrb(mrb_state *mrb, Point *ptr);
        static mrb_value ToMrb(mrb_state *mrb, struct RClass *cc, Point *ptr);
        static Point* ToCpp(mrb_state *mrb, mrb_value value);
        static Point* ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value);
    };
}
