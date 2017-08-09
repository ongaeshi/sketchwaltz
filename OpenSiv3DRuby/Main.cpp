#include <Siv3D.hpp>
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
#include <codecvt>

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

    FILE* fp;
    fopen_s(&fp, "main.rb", "r");
    {
        mrb_value ret = mrb_load_file(mrb, fp);

		if (mrb->exc) {
			Graphics::SetBackground(Palette::Black);

			mrb_value msg = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
			const char* cstr = mrb_string_value_ptr(mrb, msg);
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			Print << converter.from_bytes(cstr);

			while (System::Update()) {
			}
		}
    }
    fclose(fp);

    mrb_close(mrb);
}
