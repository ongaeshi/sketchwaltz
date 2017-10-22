#include "MrbPolygon.hpp"

#include "MrbVec2.hpp"
#include "Util.hpp"
#include "mruby/array.h"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Polygon>::Inner MrbPolygon::fInner;

//----------------------------------------------------------
void MrbPolygon::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Polygon");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, Cc(), "moved_by", moved_by, MRB_ARGS_OPT(2));
}

//----------------------------------------------------------
mrb_value MrbPolygon::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value outer_array;
    mrb_get_args(mrb, "o", &outer_array);

    if (!mrb_array_p(outer_array)) {
        mrb_raise(mrb, E_TYPE_ERROR, "need Array type");
        return mrb_nil_value();
    }

    Array<Vec2> outer;
    for (int i = 0; i < mrb_ary_len(mrb, outer_array); i++) {
        outer << Util::ToVec2(mrb, mrb_ary_ref(mrb, outer_array, i));
    }

    Initialize(self, new Polygon(outer));
    return self;
}

//----------------------------------------------------------
mrb_value MrbPolygon::draw(mrb_state *mrb, mrb_value self)
{
    mrb_value color;
    int argc = mrb_get_args(mrb, "|o", &color);

    switch (argc)
    {
        case 1:
            Self(self).draw(Util::ToColor(mrb, color));
            break;
        default:
            Self(self).draw();
            break;
    }

    return mrb_nil_value();
}

//----------------------------------------------------------
mrb_value MrbPolygon::moved_by(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    int argc = mrb_get_args(mrb, "|ff", &x, &y);
    return ToMrb(mrb, new Polygon(Self(self).movedBy(x, y)));
}

}
