#pragma once
#include "Functions.h"

class IpcManager
{
public:
    IpcManager();
    ~IpcManager();

    void Run();

private:
    SECURITY_ATTRIBUTES CreateEveryoneSecurityAttribute();
};