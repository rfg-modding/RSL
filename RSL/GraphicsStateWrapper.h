#pragma once
#include "HdrStateBlock.h"
#include "ShadowStateBlock.h"
#include "SsaoStateBlock.h"
#include "TerrainStateBlock.h"
#include "DofStateBlock.h"
#include "SunShaftsStateBlock.h"
#include "LightingStateBlock.h"
#include "MiscStateBlock.h"

class GraphicsStateWrapper
{
public:
    GraphicsStateWrapper() {};
    ~GraphicsStateWrapper() {};

    void Init();
    [[nodiscard]] bool Ready() const;

    HdrStateBlock HdrState;
    ShadowStateBlock ShadowState;
    SsaoStateBlock SsaoState;
    TerrainStateBlock TerrainState;
    DofStateBlock DofState;
    SunShaftsStateBlock SunShaftsState;
    LightingStateBlock LightingState;
    MiscStateBlock MiscState;

private:
    bool ReadyForUse = false;
};

