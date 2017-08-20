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
                    if (fSiv3DRubyState.isReload) {
                        break;
                    }
                }
            }
        }
    }

    void threadLoop()
    {
        while (true) {
            auto writeTime = FileSystem::WriteTime(L"main.rb");

            if (writeTime > fSiv3DRubyState.lastWriteTime) {
                fSiv3DRubyState.lastWriteTime = writeTime;
                fSiv3DRubyState.isReload = true;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void Main()
{
    using namespace siv3druby;

    mrb_state* mrb = mrb_open();

    MrbCircle::Init(mrb);
    MrbColorF::Init(mrb);
    MrbDrawableText::Init(mrb);
    MrbFont::Init(mrb);
    MrbMisc::Init(mrb);
    MrbPoint::Init(mrb);
    MrbVec2::Init(mrb);

    fSiv3DRubyState.lastWriteTime = FileSystem::WriteTime(L"main.rb");

    std::thread t([&] {
        threadLoop();
    });
    t.detach();

    do {
        fSiv3DRubyState.isReload = false;
        mainLoop(mrb);
    } while (fSiv3DRubyState.isReload);

    mrb_close(mrb);
}
