#include <Siv3D.hpp>
#include "Main.hpp"
#include "MrbCircle.hpp"
#include "MrbColorF.hpp"
#include "MrbDrawableText.hpp"
#include "MrbFont.hpp"
#include "MrbMisc.hpp"
#include "MrbPoint.hpp"
#include "MrbVec2.hpp"
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"

namespace siv3druby {
Siv3DRubyState fSiv3DRubyState;

void mainLoop(mrb_state* mrb)
{
    TextReader reader(L"main.rb");
    const String s = reader.readAll();

    {
        mrb_value ret = mrb_load_string(mrb, s.toUTF8().c_str());

        if (mrb->exc) {
            Graphics::SetBackground(Palette::Black);

            mrb_value msg = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
            const char* cstr = mrb_string_value_ptr(mrb, msg);
            Print << CharacterSet::UTF8ToUTF16(cstr);

            while (System::Update()) {
            }
        }
    }
}
}

void Main()
{
    mrb_state* mrb = mrb_open();

    siv3druby::MrbCircle::Init(mrb);
    siv3druby::MrbColorF::Init(mrb);
    siv3druby::MrbDrawableText::Init(mrb);
    siv3druby::MrbFont::Init(mrb);
    siv3druby::MrbMisc::Init(mrb);
    siv3druby::MrbPoint::Init(mrb);
    siv3druby::MrbVec2::Init(mrb);

    do {
        siv3druby::mainLoop(mrb);
    } while (siv3druby::fSiv3DRubyState.isReload);

    mrb_close(mrb);
}
