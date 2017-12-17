#include "MrbHSV.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<HSV>::Inner MrbHSV::fInner;

//----------------------------------------------------------
void MrbHSV::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "HSV");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_ARG(3, 1));
}

//----------------------------------------------------------
mrb_value MrbHSV::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float h, s, v, a = 1.0;
    mrb_get_args(mrb, "fff|f", &h, &s, &v, &a);

    Initialize(self, new HSV(h, s, v, a));
    return self;
}

}
