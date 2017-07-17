#include "MrbCircle.hpp"

#include "MrbColorF.hpp"
#include "MrbPoint.hpp"
#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"

//----------------------------------------------------------
namespace siv3druby {
namespace {
Circle& toCpp(mrb_value self)
{
    return *((Circle*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((Circle*)p);
    }
}

struct mrb_data_type data_type = { "siv3d_point", free };

mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value pos;
    mrb_int radius;
    mrb_get_args(mrb, "oi", &pos, &radius);

    Circle* obj = new Circle(*siv3druby::MrbPoint::ToCpp(mrb, pos), radius);

    mrb_data_init(self, obj, &data_type);
    return self;
}

mrb_value draw(mrb_state *mrb, mrb_value self)
{
    mrb_value color;
    int argc = mrb_get_args(mrb, "|o", &color);

    switch (argc)
    {
        case 1:
            toCpp(self).draw(*siv3druby::MrbColorF::ToCpp(mrb, color));
            break;
        default:
            toCpp(self).draw();
            break;
    }

    return mrb_nil_value();
}

}

//----------------------------------------------------------
void MrbCircle::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "Circle", mrb->object_class);

    mrb_define_method(mrb, cc, "initialize", initialize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc, "draw", draw, MRB_ARGS_OPT(1));
}

//----------------------------------------------------------
mrb_value MrbCircle::ToMrb(mrb_state *mrb, Circle *ptr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "Circle"), ptr);
}

//----------------------------------------------------------
mrb_value MrbCircle::ToMrb(mrb_state *mrb, struct RClass *cc, Circle *ptr)
{
    struct RData *data = mrb_data_object_alloc(mrb, cc, ptr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
Circle* MrbCircle::ToCpp(mrb_state *mrb, mrb_value value)
{
    return ToCpp(mrb, mrb_class_get(mrb, "Circle"), value);
}

//----------------------------------------------------------
Circle* MrbCircle::ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value)
{
    if (!mrb_obj_is_instance_of(mrb, value, cc)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<Circle*>(DATA_PTR(value));
}

}
