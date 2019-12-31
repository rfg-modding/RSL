#pragma once

class DofStateBlock
{
public:
    DofStateBlock() { }
    ~DofStateBlock() { }

    float* FocusStartA = nullptr;
    float* FocusStartB = nullptr;
    float* FocusEndA = nullptr;
    float* FocusEndB = nullptr;
};