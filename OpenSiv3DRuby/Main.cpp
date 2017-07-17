#include <Siv3D.hpp>
#include "MrbCircle.hpp"
#include "MrbColorF.hpp"
#include "MrbDrawableText.hpp"
#include "MrbFont.hpp"
#include "MrbMisc.hpp"
#include "MrbPoint.hpp"
#include "mruby.h"
#include "mruby/compile.h"

void Main()
{
    mrb_state* mrb = mrb_open();

    siv3druby::MrbCircle::Init(mrb);
    siv3druby::MrbColorF::Init(mrb);
    siv3druby::MrbDrawableText::Init(mrb);
    siv3druby::MrbFont::Init(mrb);
    siv3druby::MrbMisc::Init(mrb);
    siv3druby::MrbPoint::Init(mrb);

    FILE* fp;
    fopen_s(&fp, "main.rb", "r");
    {
        mrb_value ret = mrb_load_file(mrb, fp);
    }
    fclose(fp);

    mrb_close(mrb);
}
