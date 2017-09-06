#pragma once

//----------------------------------------------------------
namespace siv3druby {
class Siv3DRubyState {
public:
    Siv3DRubyState()
    : filePath(L"main.rb")
    , isReload(false)
    {
    }

    FilePath filePath;
    bool isReload;
    Optional<DateTime> lastWriteTime;
};

extern Siv3DRubyState fSiv3DRubyState;

}
