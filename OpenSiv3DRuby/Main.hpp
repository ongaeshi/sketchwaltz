#pragma once

//----------------------------------------------------------
namespace siv3druby {
class Siv3DRubyState {
public:
    Siv3DRubyState()
    : isReload(false)
    {
    }

    bool isReload;
};

extern Siv3DRubyState fSiv3DRubyState;

}
