#include "MrbLineString.hpp"

#include "MrbVec2.hpp"
#include "Util.hpp"
#include "mruby/array.h"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<LineString>::Inner MrbLineString::fInner;

//----------------------------------------------------------
void MrbLineString::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "LineString");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, Cc(), "draw_catmull_rom", draw_catmull_rom, MRB_ARGS_OPT(4));
}

//----------------------------------------------------------
mrb_value MrbLineString::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value outer_array;
    mrb_get_args(mrb, "o", &outer_array);

    if (!mrb_array_p(outer_array)) {
        mrb_raise(mrb, E_TYPE_ERROR, "need Array type");
        return mrb_nil_value();
    }

    Array<Vec2> outer;
    for (int i = 0; i < RARRAY_LEN(outer_array); i++) {
        outer << Util::ToVec2(mrb, mrb_ary_ref(mrb, outer_array, i));
    }

    Initialize(self, new LineString(outer));
    return self;
}

//----------------------------------------------------------
mrb_value MrbLineString::draw(mrb_state *mrb, mrb_value self)
{
    mrb_float thickness;
    mrb_value color;
    int argc = mrb_get_args(mrb, "|fo", &thickness, &color);

    switch (argc)
    {
        case 2:
            Self(self).draw(thickness, Util::ToColor(mrb, color));
            break;
        case 1:
            Self(self).draw(thickness);
            break;
        default:
            Self(self).draw();
            break;
    }

    return mrb_nil_value();
}

//----------------------------------------------------------
mrb_value MrbLineString::draw_catmull_rom(mrb_state *mrb, mrb_value self)
{
    mrb_float thickness;
    mrb_value color;
    mrb_bool is_closed;
    mrb_int interpolation;
    int argc = mrb_get_args(mrb, "|fobi", &thickness, &color, &is_closed, &interpolation);

    switch (argc)
    {
        case 4:
            Self(self).drawCatmullRom(thickness, Util::ToColor(mrb, color), is_closed, interpolation);
            break;
        case 3:
            Self(self).drawCatmullRom(thickness, Util::ToColor(mrb, color), is_closed);
            break;
        case 2:
            Self(self).drawCatmullRom(thickness, Util::ToColor(mrb, color));
            break;
        case 1:
            Self(self).drawCatmullRom(thickness);
            break;
        default:
            Self(self).drawCatmullRom();
            break;
    }

    return mrb_nil_value();
}

}
