#include "MrbPoint.hpp"

#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"

//----------------------------------------------------------
namespace siv3druby {
namespace {
Point& toCpp(mrb_value self)
{
    return *((Point*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((Point*)p);
    }
}

struct mrb_data_type data_type = { "siv3d_point", free };

mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    mrb_get_args(mrb, "ii", &x, &y);

    Point* obj = new Point(x, y);

    mrb_data_init(self, obj, &data_type);
    return self;
}

mrb_value to_s(mrb_state *mrb, mrb_value self)
{
    std::stringstream stream;
    stream << toCpp(self);
    return mrb_str_new_cstr(mrb, stream.str().c_str());
}
}

//----------------------------------------------------------
void MrbPoint::Init(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "Point", mrb->object_class);

    mrb_define_method(mrb, cc, "initialize", initialize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc, "to_s", to_s, MRB_ARGS_NONE());
}

//----------------------------------------------------------
mrb_value MrbPoint::ToMrb(mrb_state *mrb, Point *ptr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "Point"), ptr);
}

//----------------------------------------------------------
mrb_value MrbPoint::ToMrb(mrb_state *mrb, struct RClass *cc, Point *ptr)
{
    struct RData *data = mrb_data_object_alloc(mrb, cc, ptr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
Point* MrbPoint::ToCpp(mrb_state *mrb, mrb_value value)
{
    return ToCpp(mrb, mrb_class_get(mrb, "Point"), value);
}

//----------------------------------------------------------
Point* MrbPoint::ToCpp(mrb_state *mrb, struct RClass *cc, mrb_value value)
{
    if (!mrb_obj_is_instance_of(mrb, value, cc)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<Point*>(DATA_PTR(value));
}

}
