#pragma once

class IIpcManager
{
public:
    IIpcManager(const IIpcManager&) = delete;
    IIpcManager& operator=(const IIpcManager&) = delete;
    virtual ~IIpcManager() noexcept = default;

    virtual void StartIpcThread() = 0;

protected:
    IIpcManager() = default;
};