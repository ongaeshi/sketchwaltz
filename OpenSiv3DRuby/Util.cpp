#include "Util.hpp"

#include "MrbColorF.hpp"
#include "MrbHSV.hpp"
#include "MrbVec2.hpp"
#include "mruby/array.h"
#include "mruby/numeric.h"

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
    } else if (MrbHSV::IsInstance(mrb, obj)) {
        return MrbHSV::ToCpp(mrb, obj)->toColor();
    } else if (mrb_obj_is_instance_of(mrb, obj, mrb_class_get(mrb, "ColorF"))) {
        return MrbColorF::ToCpp(mrb, obj)->toColor();
    } else {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
        return Color();
    }
}

//----------------------------------------------------------
Vec2 Util::ToVec2(mrb_state *mrb, mrb_value obj)
{
    if (mrb_array_p(obj)) {
        switch (mrb_ary_len(mrb, obj)) {
            case 2:
                return Vec2(
                    mrb_to_flo(mrb, mrb_ary_ref(mrb, obj, 0)),
                    mrb_to_flo(mrb, mrb_ary_ref(mrb, obj, 1))
                );
            default:
                mrb_raise(mrb, E_TYPE_ERROR, "Vec2 Array size is 2");
                return Vec2();
        }
    } else if (MrbVec2::IsInstance(mrb, obj)) {
        return *MrbVec2::ToCpp(mrb, obj);
    } else {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
        return Vec2();
    }
}

}
