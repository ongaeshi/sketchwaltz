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
}

//----------------------------------------------------------
void MrbMisc::Init(mrb_state* mrb)
{
    {
        struct RClass *krn = mrb->kernel_module;
        mrb_define_method(mrb, krn, "__printstr__", printstr, MRB_ARGS_REQ(1));
        mrb_define_method(mrb, krn, "clear", clear, MRB_ARGS_NONE());
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
}

}
