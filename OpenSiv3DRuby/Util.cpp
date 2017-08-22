#include "Util.hpp"

#include "MrbColorF.hpp"

//----------------------------------------------------------
namespace siv3druby {
//----------------------------------------------------------
Color Util::ToColor(mrb_state *mrb, mrb_value obj)
{
    if (mrb_obj_is_instance_of(mrb, obj, mrb_class_get(mrb, "ColorF"))) {
        return MrbColorF::ToCpp(mrb, obj)->toColor();
    } else {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
        return Color();
    }
}

}
