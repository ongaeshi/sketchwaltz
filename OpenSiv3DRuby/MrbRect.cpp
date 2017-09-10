#include "MrbRect.hpp"

#include "MrbColorF.hpp"
#include "MrbPoint.hpp"
#include "Util.hpp"
#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Rect>::Inner MrbRect::fInner;

//----------------------------------------------------------
void MrbRect::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Rect");

    mrb_define_method(mrb, Cc(), "initialize", Initialize, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, Cc(), "draw", Draw, MRB_ARGS_OPT(1));
}

//----------------------------------------------------------
mrb_value MrbRect::Initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h;
    mrb_get_args(mrb, "ffff", &x, &y, &w, &h);

    auto* obj = new Rect(x, y, w, h);

    mrb_data_init(self, obj, MrbRect::DataType());
    return self;
}

//----------------------------------------------------------
mrb_value MrbRect::Draw(mrb_state *mrb, mrb_value self)
{
    mrb_value color;
    int argc = mrb_get_args(mrb, "|o", &color);

    switch (argc)
    {
        case 1:
            ToCpp(self).draw(Util::ToColor(mrb, color));
            break;
        default:
            ToCpp(self).draw();
            break;
    }

    return mrb_nil_value();
}

}
