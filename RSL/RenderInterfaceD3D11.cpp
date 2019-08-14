#include "RenderInterfaceD3D11.h"

void RenderInterfaceD3D11::setMvpMatrixPtr(const float* const mtx)
{
    constantBufferData.mvpMatrix = DirectX::XMMATRIX(mtx);
}

void RenderInterfaceD3D11::setCameraFrame(const Vector3& up, const Vector3& right, const Vector3& origin)
{
    camUp = up; camRight = right; camOrigin = origin;
}

//
// dd::RenderInterface overrides:
//

void RenderInterfaceD3D11::beginDraw()
{
    // Update and set the constant buffer for this frame
    deviceContext->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &constantBufferData, 0, 0);
    deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

    // Disable culling for the screen text
    deviceContext->RSSetState(rasterizerState.Get());
}

void RenderInterfaceD3D11::endDraw()
{
    // No work done here at the moment.
}

dd::GlyphTextureHandle RenderInterfaceD3D11::createGlyphTexture(int width, int height, const void* pixels)
{
    UINT numQualityLevels = 0;
    d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8_UNORM, 1, &numQualityLevels);

    D3D11_TEXTURE2D_DESC tex2dDesc = {};
    tex2dDesc.Usage = D3D11_USAGE_DEFAULT;
    tex2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    tex2dDesc.Format = DXGI_FORMAT_R8_UNORM;
    tex2dDesc.Width = width;
    tex2dDesc.Height = height;
    tex2dDesc.MipLevels = 1;
    tex2dDesc.ArraySize = 1;
    tex2dDesc.SampleDesc.Count = 1;
    tex2dDesc.SampleDesc.Quality = numQualityLevels - 1;

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = pixels;
    initData.SysMemPitch = width;

    auto* texImpl = new TextureImpl{};

    if (FAILED(d3dDevice->CreateTexture2D(&tex2dDesc, &initData, &texImpl->d3dTexPtr)))
    {
        errorF("CreateTexture2D failed!");
        destroyGlyphTexture(texImpl);
        return nullptr;
    }
    if (FAILED(d3dDevice->CreateShaderResourceView(texImpl->d3dTexPtr, nullptr, &texImpl->d3dTexSRV)))
    {
        errorF("CreateShaderResourceView failed!");
        destroyGlyphTexture(texImpl);
        return nullptr;
    }
    if (FAILED(d3dDevice->CreateSamplerState(&samplerDesc, &texImpl->d3dSampler)))
    {
        errorF("CreateSamplerState failed!");
        destroyGlyphTexture(texImpl);
        return nullptr;
    }

    return static_cast<dd::GlyphTextureHandle>(texImpl);
}

void RenderInterfaceD3D11::destroyGlyphTexture(dd::GlyphTextureHandle glyphTex)
{
    auto* texImpl = static_cast<TextureImpl*>(glyphTex);
    if (texImpl)
    {
        if (texImpl->d3dSampler) { texImpl->d3dSampler->Release(); }
        if (texImpl->d3dTexSRV) { texImpl->d3dTexSRV->Release(); }
        if (texImpl->d3dTexPtr) { texImpl->d3dTexPtr->Release(); }
        delete texImpl;
    }
}

void RenderInterfaceD3D11::drawGlyphList(const dd::DrawVertex* glyphs, int count, dd::GlyphTextureHandle glyphTex)
{
    assert(glyphs != nullptr);
    assert(count > 0 && count <= DEBUG_DRAW_VERTEX_BUFFER_SIZE);

    auto* texImpl = static_cast<TextureImpl*>(glyphTex);
    assert(texImpl != nullptr);

    // Map the vertex buffer:
    D3D11_MAPPED_SUBRESOURCE mapInfo;
    if (FAILED(deviceContext->Map(glyphVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapInfo)))
    {
        panicF("Failed to map vertex buffer!");
    }

    // Copy into mapped buffer:
    auto* verts = static_cast<Vertex*>(mapInfo.pData);
    for (int v = 0; v < count; ++v)
    {
        verts[v].pos.x = glyphs[v].glyph.x;
        verts[v].pos.y = glyphs[v].glyph.y;
        verts[v].pos.z = 0.0f;
        verts[v].pos.w = 1.0f;

        verts[v].uv.x = glyphs[v].glyph.u;
        verts[v].uv.y = glyphs[v].glyph.v;
        verts[v].uv.z = 0.0f;
        verts[v].uv.w = 0.0f;

        verts[v].color.x = glyphs[v].glyph.r;
        verts[v].color.y = glyphs[v].glyph.g;
        verts[v].color.z = glyphs[v].glyph.b;
        verts[v].color.w = 1.0f;
    }

    // Unmap and draw:
    deviceContext->Unmap(glyphVertexBuffer.Get(), 0);

    // Bind texture & sampler (t0, s0):
    deviceContext->PSSetShaderResources(0, 1, &texImpl->d3dTexSRV);
    deviceContext->PSSetSamplers(0, 1, &texImpl->d3dSampler);

    const float blendFactor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    deviceContext->OMSetBlendState(blendStateText.Get(), blendFactor, 0xFFFFFFFF);

    // Draw with the current buffer:
    drawHelper(count, glyphShaders, glyphVertexBuffer.Get(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Restore default blend state.
    deviceContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
}

void RenderInterfaceD3D11::drawPointList(const dd::DrawVertex* points, int count, bool depthEnabled)
{
    (void)depthEnabled; // TODO: not implemented yet - not required by this sample

    // Emulating points as billboarded quads, so each point will use 6 vertexes.
    // D3D11 doesn't support "point sprites" like OpenGL (gl_PointSize).
    const int maxVerts = DEBUG_DRAW_VERTEX_BUFFER_SIZE / 6;

    // OpenGL point size scaling produces gigantic points with the billboarding fallback.
    // This is some arbitrary down-scaling factor to more or less match the OpenGL samples.
    const float D3DPointSpriteScalingFactor = 0.01f;

    assert(points != nullptr);
    assert(count > 0 && count <= maxVerts);

    // Map the vertex buffer:
    D3D11_MAPPED_SUBRESOURCE mapInfo;
    if (FAILED(deviceContext->Map(pointVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapInfo)))
    {
        panicF("Failed to map vertex buffer!");
    }

    const int numVerts = count * 6;
    const int indexes[6] = { 0, 1, 2, 2, 3, 0 };

    int v = 0;
    auto* verts = static_cast<Vertex*>(mapInfo.pData);

    // Expand each point into a quad:
    for (int p = 0; p < count; ++p)
    {
        const float ptSize = points[p].point.size * D3DPointSpriteScalingFactor;
        const Vector3 halfWidth = (ptSize * 0.5f) * camRight; // X
        const Vector3 halfHeigh = (ptSize * 0.5f) * camUp;    // Y
        const Vector3 origin = Vector3{ points[p].point.x, points[p].point.y, points[p].point.z };

        Vector3 corners[4];
        corners[0] = origin + halfWidth + halfHeigh;
        corners[1] = origin - halfWidth + halfHeigh;
        corners[2] = origin - halfWidth - halfHeigh;
        corners[3] = origin + halfWidth - halfHeigh;

        for (int i : indexes)
        {
            verts[v].pos.x = corners[i].getX();
            verts[v].pos.y = corners[i].getY();
            verts[v].pos.z = corners[i].getZ();
            verts[v].pos.w = 1.0f;

            verts[v].color.x = points[p].point.r;
            verts[v].color.y = points[p].point.g;
            verts[v].color.z = points[p].point.b;
            verts[v].color.w = 1.0f;

            ++v;
        }
    }
    assert(v == numVerts);

    // Unmap and draw:
    deviceContext->Unmap(pointVertexBuffer.Get(), 0);

    // Draw with the current buffer:
    drawHelper(numVerts, pointShaders, pointVertexBuffer.Get(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void RenderInterfaceD3D11::drawLineList(const dd::DrawVertex* lines, int count, bool depthEnabled)
{
    (void)depthEnabled; // TODO: not implemented yet - not required by this sample

    assert(lines != nullptr);
    assert(count > 0 && count <= DEBUG_DRAW_VERTEX_BUFFER_SIZE);

    // Map the vertex buffer:
    D3D11_MAPPED_SUBRESOURCE mapInfo;
    if (FAILED(deviceContext->Map(lineVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapInfo)))
    {
        panicF("Failed to map vertex buffer!");
    }

    // Copy into mapped buffer:
    auto* verts = static_cast<Vertex*>(mapInfo.pData);
    for (int v = 0; v < count; ++v)
    {
        verts[v].pos.x = lines[v].line.x;
        verts[v].pos.y = lines[v].line.y;
        verts[v].pos.z = lines[v].line.z;
        verts[v].pos.w = 1.0f;

        verts[v].color.x = lines[v].line.r;
        verts[v].color.y = lines[v].line.g;
        verts[v].color.z = lines[v].line.b;
        verts[v].color.w = 1.0f;
    }

    // Unmap and draw:
    deviceContext->Unmap(lineVertexBuffer.Get(), 0);

    // Draw with the current buffer:
    drawHelper(count, lineShaders, lineVertexBuffer.Get(), D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void RenderInterfaceD3D11::initShaders()
{
    // Same vertex format used by all buffers to simplify things.
    const D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    const ShaderSetD3D11::InputLayoutDesc inputDesc{ layout, int(ARRAYSIZE(layout)) };

    // 3D lines shader:
    lineShaders.loadFromFxFile(d3dDevice.Get(), L"ddShader.fx", "VS_LinePoint", "PS_LinePoint", inputDesc);
    // 3D points shader:
    pointShaders.loadFromFxFile(d3dDevice.Get(), L"ddShader.fx", "VS_LinePoint", "PS_LinePoint", inputDesc);
    // 2D glyphs shader:
    glyphShaders.loadFromFxFile(d3dDevice.Get(), L"ddShader.fx", "VS_TextGlyph", "PS_TextGlyph", inputDesc);

    // Rasterizer state for the screen text:
    D3D11_RASTERIZER_DESC rsDesc = {};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_NONE;
    rsDesc.FrontCounterClockwise = true;
    rsDesc.DepthBias = 0;
    rsDesc.DepthBiasClamp = 0.0f;
    rsDesc.SlopeScaledDepthBias = 0.0f;
    rsDesc.DepthClipEnable = false;
    rsDesc.ScissorEnable = false;
    rsDesc.MultisampleEnable = false;
    rsDesc.AntialiasedLineEnable = false;
    if (FAILED(d3dDevice->CreateRasterizerState(&rsDesc, rasterizerState.GetAddressOf())))
    {
        errorF("CreateRasterizerState failed!");
    }

    // Blend state for the screen text:
    D3D11_BLEND_DESC bsDesc = {};
    bsDesc.RenderTarget[0].BlendEnable = true;
    bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    if (FAILED(d3dDevice->CreateBlendState(&bsDesc, blendStateText.GetAddressOf())))
    {
        errorF("CreateBlendState failed!");
    }
}

void RenderInterfaceD3D11::initBuffers()
{
    D3D11_BUFFER_DESC bd;

    // Create the shared constant buffer:
    bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(ConstantBufferData);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    if (FAILED(d3dDevice->CreateBuffer(&bd, nullptr, constantBuffer.GetAddressOf())))
    {
        panicF("Failed to create shader constant buffer!");
    }

    // Create the vertex buffers for lines/points/glyphs:
    bd = {};
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(Vertex) * DEBUG_DRAW_VERTEX_BUFFER_SIZE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(d3dDevice->CreateBuffer(&bd, nullptr, lineVertexBuffer.GetAddressOf())))
    {
        panicF("Failed to create lines vertex buffer!");
    }
    if (FAILED(d3dDevice->CreateBuffer(&bd, nullptr, pointVertexBuffer.GetAddressOf())))
    {
        panicF("Failed to create points vertex buffer!");
    }
    if (FAILED(d3dDevice->CreateBuffer(&bd, nullptr, glyphVertexBuffer.GetAddressOf())))
    {
        panicF("Failed to create glyphs vertex buffer!");
    }
}

void RenderInterfaceD3D11::drawHelper(const int numVerts, const ShaderSetD3D11& ss, ID3D11Buffer* vb, const D3D11_PRIMITIVE_TOPOLOGY topology)
{
    const UINT offset = 0;
    const UINT stride = sizeof(Vertex);
    deviceContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
    deviceContext->IASetPrimitiveTopology(topology);
    deviceContext->IASetInputLayout(ss.vertexLayout.Get());
    deviceContext->VSSetShader(ss.vs.Get(), nullptr, 0);
    deviceContext->PSSetShader(ss.ps.Get(), nullptr, 0);
    deviceContext->Draw(numVerts, 0);
}