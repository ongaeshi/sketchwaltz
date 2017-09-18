#include <Siv3D.hpp>
#include "Main.hpp"
#include "MrbCircle.hpp"
#include "MrbEmoji.hpp"
#include "MrbColorF.hpp"
#include "MrbDrawableText.hpp"
#include "MrbFont.hpp"
#include "MrbLine.hpp"
#include "MrbLineString.hpp"
#include "MrbMisc.hpp"
#include "MrbPoint.hpp"
#include "MrbPolygon.hpp"
#include "MrbQuad.hpp"
#include "MrbRect.hpp"
#include "MrbRoundRect.hpp"
#include "MrbTexture.hpp"
#include "MrbTextureRegion.hpp"
#include "MrbTriangle.hpp"
#include "MrbVec2.hpp"
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"
#include "mruby/dump.h"

extern "C" const uint8_t __declspec(align(4)) mrb_siv3druby_builtin[];

namespace siv3druby {

    Siv3DRubyState fSiv3DRubyState;

    void loadBuiltin(mrb_state* mrb)
    {
        mrb_load_irep(mrb, mrb_siv3druby_builtin);
    }

    void mainLoop()
    {
        Window::SetTitle(L"RubyPen");

        mrb_state* mrb = mrb_open();

        loadBuiltin(mrb);
        MrbCircle::Init(mrb);
        MrbEmoji::Init(mrb);
        MrbColorF::Init(mrb);
        MrbDrawableText::Init(mrb);
        MrbFont::Init(mrb);
        MrbLine::Init(mrb);
        MrbLineString::Init(mrb);
        MrbMisc::Init(mrb);
        MrbPoint::Init(mrb);
        MrbPolygon::Init(mrb);
        MrbQuad::Init(mrb);
        MrbRect::Init(mrb);
        MrbRoundRect::Init(mrb);
        MrbTexture::Init(mrb);
        MrbTextureRegion::Init(mrb);
        MrbTriangle::Init(mrb);
        MrbVec2::Init(mrb);

        TextReader reader(fSiv3DRubyState.filePath);
        const String s = reader.readAll();

        {
            mrb_value ret = mrb_load_string(mrb, s.toUTF8().c_str());

            if (mrb->exc) {
                Graphics::SetBackground(Palette::Black);

                mrb_value msg = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
                const char* cstr = mrb_string_value_ptr(mrb, msg);
                Print << CharacterSet::FromUTF8(cstr);

                while (System::Update()) {
                    if (fSiv3DRubyState.isReload) {
                        break;
                    }
                }
            }
        }

        mrb_close(mrb);
    }

    void threadLoop()
    {
        while (true) {
            auto writeTime = FileSystem::WriteTime(fSiv3DRubyState.filePath);

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

    fSiv3DRubyState.lastWriteTime = FileSystem::WriteTime(fSiv3DRubyState.filePath);

    std::thread t([&] {
        threadLoop();
    });
    t.detach();

    do {
        ClearPrint();
        fSiv3DRubyState.isReload = false;
        mainLoop();
    } while (fSiv3DRubyState.isReload);
}
