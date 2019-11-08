#pragma once
#include "Functions.h"
#include "IIPCManager.h"

class IpcManager : public IIpcManager
{
public:
    IpcManager();
    ~IpcManager();

    void StartIpcThread() override;

private:
    void Run();
    SECURITY_ATTRIBUTES CreateEveryoneSecurityAttribute();
};
