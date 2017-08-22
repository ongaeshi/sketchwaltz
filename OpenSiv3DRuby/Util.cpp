#include "Util.hpp"

#include "MrbColorF.hpp"
#include "mruby/array.h"

//----------------------------------------------------------
namespace siv3druby {
//----------------------------------------------------------
Color Util::ToColor(mrb_state *mrb, mrb_value obj)
{
    if (mrb_array_p(obj)) {
        switch (mrb_ary_len(mrb, obj)) {
            case 3:
                return Color(
                    mrb_int(mrb, mrb_ary_ref(mrb, obj, 0)),
                    mrb_int(mrb, mrb_ary_ref(mrb, obj, 1)),
                    mrb_int(mrb, mrb_ary_ref(mrb, obj, 2))
                );
            case 4:
                return Color(
                    mrb_int(mrb, mrb_ary_ref(mrb, obj, 0)),
                    mrb_int(mrb, mrb_ary_ref(mrb, obj, 1)),
                    mrb_int(mrb, mrb_ary_ref(mrb, obj, 2)),
                    mrb_int(mrb, mrb_ary_ref(mrb, obj, 3))
                    );
            default:
                mrb_raise(mrb, E_TYPE_ERROR, "Color Array size is 3 or 4");
                return Color(0, 0, 0);
        }
    } else if (mrb_obj_is_instance_of(mrb, obj, mrb_class_get(mrb, "ColorF"))) {
        return MrbColorF::ToCpp(mrb, obj)->toColor();
    } else {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
        return Color();
    }
}

}
