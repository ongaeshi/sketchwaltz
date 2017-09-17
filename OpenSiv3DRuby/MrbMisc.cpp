#include "MrbMisc.hpp"

#include "Main.hpp"
#include "MrbPoint.hpp"
#include "MrbVec2.hpp"
#include "Util.hpp"
#include "mruby.h"
#include "mruby/irep.h"
#include "mruby/string.h"

//----------------------------------------------------------
namespace siv3druby {

namespace {
static mrb_value printstr(mrb_state *mrb, mrb_value self)
{
    mrb_value str;
    mrb_get_args(mrb, "S", &str);
    Print << CharacterSet::FromUTF8(mrb_string_value_ptr(mrb, str));
    return str;
}

static mrb_value clear(mrb_state *mrb, mrb_value self)
{
    ClearPrint();
    return mrb_nil_value();
}

static mrb_value random(mrb_state *mrb, mrb_value self)
{
    mrb_float v1, v2;
    mrb_int argc = mrb_get_args(mrb, "|ff", &v1, &v2);

    switch (argc) {
        case 2:
            return mrb_float_value(mrb, Random(v1, v2));
        case 1:
            return mrb_float_value(mrb, Random(v1));
        default:
            return mrb_float_value(mrb, Random());
    }
}

static mrb_value system_update(mrb_state *mrb, mrb_value self)
{
    if (DragDrop::HasNewFilePaths()) {
        const auto items = DragDrop::GetDroppedFilePaths();

        for (const auto& item : items) {
            fSiv3DRubyState.filePath = item.path;
            fSiv3DRubyState.isReload = true;
        }
    }

    if (fSiv3DRubyState.isReload) {
        return mrb_bool_value(false);
    } else {
        return mrb_bool_value(System::Update());
    }
}

static mrb_value cursor_pos(mrb_state *mrb, mrb_value self)
{
    return MrbPoint::ToMrb(mrb, new Point(Cursor::Pos()));
}

static mrb_value set_background(mrb_state *mrb, mrb_value self)
{
    mrb_value color;
    mrb_get_args(mrb, "o", &color);

    Graphics::SetBackground(Util::ToColor(mrb, color));
    return mrb_nil_value();
}

static mrb_value center(mrb_state *mrb, mrb_value self)
{
    return MrbVec2::ToMrb(mrb, new Vec2(Window::Center()));
}

static mrb_value width(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(Window::Width());
}

static mrb_value height(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(Window::Height());
}

mrb_value radians(mrb_state *mrb, mrb_value self)
{
    mrb_float deg;
    mrb_get_args(mrb, "f", &deg);
    return mrb_float_value(mrb, Math::Radians(deg));
}
}

//----------------------------------------------------------
void MrbMisc::Init(mrb_state* mrb)
{
    {
        struct RClass *krn = mrb->kernel_module;
        mrb_define_method(mrb, krn, "__printstr__", printstr, MRB_ARGS_REQ(1));
        mrb_define_method(mrb, krn, "clear", clear, MRB_ARGS_NONE());
        mrb_define_method(mrb, krn, "random", random, MRB_ARGS_OPT(2));
    }

    {
        struct RClass *cc = mrb_define_module(mrb, "System");

        mrb_define_class_method(mrb, cc, "update", system_update, MRB_ARGS_NONE());
    }

    {
        struct RClass *cc = mrb_define_module(mrb, "Cursor");

        mrb_define_class_method(mrb, cc, "pos", cursor_pos, MRB_ARGS_NONE());
    }

    {
        struct RClass *cc = mrb_define_module(mrb, "Graphics");

        mrb_define_class_method(mrb, cc, "set_background", set_background, MRB_ARGS_NONE());
    }

    {
        struct RClass *cc = mrb_define_module(mrb, "Window");

        mrb_define_class_method(mrb, cc, "center", center, MRB_ARGS_NONE());
        mrb_define_class_method(mrb, cc, "width", width, MRB_ARGS_NONE());
        mrb_define_class_method(mrb, cc, "height", height, MRB_ARGS_NONE());
    }

    {
        struct RClass *cc = mrb_define_module(mrb, "TextureDesc");

        mrb_define_const(mrb, cc, "Unmipped",  mrb_fixnum_value((int)TextureDesc::Unmipped));
        mrb_define_const(mrb, cc, "UnmippedSRGB",  mrb_fixnum_value((int)TextureDesc::UnmippedSRGB));
        mrb_define_const(mrb, cc, "Mipped",  mrb_fixnum_value((int)TextureDesc::Mipped));
        mrb_define_const(mrb, cc, "MippedSRGB",  mrb_fixnum_value((int)TextureDesc::MippedSRGB));
        mrb_define_const(mrb, cc, "SDF",  mrb_fixnum_value((int)TextureDesc::SDF));
        mrb_define_const(mrb, cc, "For3D",  mrb_fixnum_value((int)TextureDesc::For3D));
    }

    {
        struct RClass *cc = mrb_module_get(mrb, "Math");
        mrb_define_class_method(mrb, cc, "radians", radians, MRB_ARGS_REQ(1));
    }
}

}
