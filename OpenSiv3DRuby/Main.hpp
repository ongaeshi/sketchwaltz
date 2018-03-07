#pragma once

//----------------------------------------------------------
namespace siv3druby {
class Siv3DRubyState {
public:
    Siv3DRubyState()
    : argv()
    , filePath()
    , evalString()
    , isCapture(false)
    , isReload(false)
    {
    }

    Array<String> argv;
    FilePath filePath;
    String evalString;
    bool isCapture;
    bool isReload;
    Optional<DateTime> lastWriteTime;
};

extern Siv3DRubyState fSiv3DRubyState;

}

void Main();
