#include "MrbPoint.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Point>::Inner MrbPoint::fInner;

//----------------------------------------------------------
void MrbPoint::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Point");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, Cc(), "x", x, MRB_ARGS_NONE());
    mrb_define_method(mrb, Cc(), "y", y, MRB_ARGS_NONE());
    mrb_define_method(mrb, Cc(), "to_s", to_s, MRB_ARGS_NONE());
}

//----------------------------------------------------------
mrb_value MrbPoint::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    mrb_get_args(mrb, "ii", &x, &y);

    Initialize(self, new Point(x, y));
    return self;
}

//----------------------------------------------------------
mrb_value MrbPoint::x(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(Self(self).x);
}

//----------------------------------------------------------
mrb_value MrbPoint::y(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(Self(self).y);
}

//----------------------------------------------------------
mrb_value MrbPoint::to_s(mrb_state *mrb, mrb_value self)
{
    std::stringstream stream;
    stream << Self(self);
    return mrb_str_new_cstr(mrb, stream.str().c_str());
}

}
