#include "MrbColorF.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<ColorF>::Inner MrbColorF::fInner;

//----------------------------------------------------------
void MrbColorF::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "ColorF");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_ARG(3, 1));
}

//----------------------------------------------------------
mrb_value MrbColorF::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float r, g, b, a = 1.0;
    mrb_get_args(mrb, "fff|f", &r, &g, &b, &a);

    ColorF* obj = new ColorF(r, g, b, a);

    mrb_data_init(self, obj, DataType());
    return self;
}

}
