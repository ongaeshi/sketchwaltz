#include <Siv3D.hpp>
#include "MrbPoint.hpp"
#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"

static Circle& to_obj(mrb_value self)
{
    return *((Circle*)DATA_PTR(self));
}

static void free(mrb_state *mrb, void *p)
{
	if (p) {
		delete ((Circle*)p);
	}
}

struct mrb_data_type data_type = { "siv3d_circle", free };

static mrb_value mrb_siv3druby_circle_initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value pos;
    mrb_int radius;
    mrb_get_args(mrb, "oi", &pos, &radius);

    Circle* obj = new Circle(*siv3druby::MrbPoint::ToCpp(mrb, pos), radius);

    mrb_data_init(self, obj, &data_type);
    return self;
}

static mrb_value mrb_siv3druby_circle_draw(mrb_state *mrb, mrb_value self)
{
    to_obj(self).draw();
    return mrb_nil_value();
}

void mrb_siv3druby_circle_init(mrb_state *mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "Circle", mrb->object_class);

    mrb_define_method(mrb, cc, "initialize", mrb_siv3druby_circle_initialize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc, "draw", mrb_siv3druby_circle_draw, MRB_ARGS_NONE());
}

