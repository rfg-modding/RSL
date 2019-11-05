#include "Hooks.h"
#include "Application.h"

void __fastcall Hooks::StreamGridDoFrameHook(stream_grid* This, void* edx, vector* StreamPos, bool SingleZoneMode)
{
    if (!Globals::MainStreamGrid || Globals::MainStreamGrid != This)
    {
        Globals::MainStreamGrid = This;
        Logger::Log("StreamGridPtr changed, new address: {}\n", std::to_string(*reinterpret_cast<DWORD*>(This)));
    }
    return rfg::StreamGridDoFrame(This, edx, StreamPos, SingleZoneMode);
}