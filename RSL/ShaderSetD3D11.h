#pragma once
#include "Globals.h"

using Microsoft::WRL::ComPtr;

static void panicF(const char* format, ...)
{
    va_list args;
    char buffer[2048] = { '\0' };

    va_start(args, format);
    std::vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    MessageBoxA(nullptr, buffer, "Fatal Error", MB_OK);
    std::abort();
}

static inline void errorF(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::vfprintf(stderr, format, args);
    va_end(args);

    // Default newline and flush (like std::endl)
    std::fputc('\n', stderr);
    std::fflush(stderr);
}

struct ShaderSetD3D11 final
{
    using InputLayoutDesc = std::tuple<const D3D11_INPUT_ELEMENT_DESC*, int>;

    ComPtr<ID3D11VertexShader> vs;
    ComPtr<ID3D11PixelShader> ps;
    ComPtr<ID3D11InputLayout> vertexLayout;

    ShaderSetD3D11() = default;

    void loadFromFxFile(ID3D11Device* device, const wchar_t* filename, const char* vsEntry, const char* psEntry, const InputLayoutDesc& layout)
    {
        assert(filename != nullptr && filename[0] != L'\0');
        assert(vsEntry != nullptr && vsEntry[0] != '\0');
        assert(psEntry != nullptr && psEntry[0] != '\0');

        ComPtr<ID3DBlob> vsBlob;
        compileShaderFromFile(filename, vsEntry, "vs_4_0", vsBlob.GetAddressOf());
        assert(vsBlob != nullptr);

        ComPtr<ID3DBlob> psBlob;
        compileShaderFromFile(filename, psEntry, "ps_4_0", psBlob.GetAddressOf());
        assert(psBlob != nullptr);

        HRESULT hr;

        // Create the vertex shader:
        hr = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vs.GetAddressOf());
        if (FAILED(hr))
        {
            panicF("Failed to create vertex shader '%s'", vsEntry);
        }

        // Create the pixel shader:
        hr = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, ps.GetAddressOf());
        if (FAILED(hr))
        {
            panicF("Failed to create pixel shader '%s'", psEntry);
        }

        // Create vertex input layout:
        hr = device->CreateInputLayout(std::get<0>(layout), std::get<1>(layout),
            vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), vertexLayout.GetAddressOf());
        if (FAILED(hr))
        {
            panicF("Failed to create vertex layout!");
        }
    }

    static void compileShaderFromFile(const wchar_t* fileName, const char* entryPoint, const char* shaderModel, ID3DBlob** ppBlobOut)
    {
        UINT shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows
        // the shaders to be optimized and to run exactly the way they will run in
        // the release configuration.
#if defined(DEBUG) || defined(_DEBUG)
        shaderFlags |= D3DCOMPILE_DEBUG;
#endif // DEBUG

        ComPtr<ID3DBlob> pErrorBlob;
        HRESULT hr = D3DCompileFromFile(fileName, nullptr, nullptr, entryPoint, shaderModel,
            shaderFlags, 0, ppBlobOut, pErrorBlob.GetAddressOf());
        if (FAILED(hr))
        {
            auto* details = (pErrorBlob ? static_cast<const char*>(pErrorBlob->GetBufferPointer()) : "<no info>");
            panicF("Failed to compile shader! Error info: %s", details);
        }
    }
};