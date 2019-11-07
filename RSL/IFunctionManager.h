#pragma once

class IFunctionManager
{
public:
    IFunctionManager(const IFunctionManager&) = delete;
    IFunctionManager& operator=(const IFunctionManager&) = delete;
    virtual ~IFunctionManager() noexcept = default;

    virtual void RegisterFunctions() = 0;

protected:
    IFunctionManager() = default;
};