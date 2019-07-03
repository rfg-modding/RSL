#pragma once
#include "Globals.h"

using Microsoft::WRL::ComPtr;

static void panicF(const char * format, ...)
{
	va_list args;
	char buffer[2048] = { '\0' };

	va_start(args, format);
	std::vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	MessageBoxA(nullptr, buffer, "Fatal Error", MB_OK);
	std::abort();
}

static inline void errorF(const char * format, ...)
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
	using InputLayoutDesc = std::tuple<const D3D11_INPUT_ELEMENT_DESC *, int>;

	ComPtr<ID3D11VertexShader> vs;
	ComPtr<ID3D11PixelShader>  ps;
	ComPtr<ID3D11InputLayout>  vertexLayout;

	ShaderSetD3D11() = default;

	void loadFromFxFile(ID3D11Device * device, const wchar_t * filename,
		const char * vsEntry, const char * psEntry,
		const InputLayoutDesc & layout)
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
		hr = device->CreateVertexShader(vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), nullptr,
			vs.GetAddressOf());
		if (FAILED(hr))
		{
			panicF("Failed to create vertex shader '%s'", vsEntry);
		}

		// Create the pixel shader:
		hr = device->CreatePixelShader(psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(), nullptr,
			ps.GetAddressOf());
		if (FAILED(hr))
		{
			panicF("Failed to create pixel shader '%s'", psEntry);
		}

		// Create vertex input layout:
		hr = device->CreateInputLayout(std::get<0>(layout), std::get<1>(layout),
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			vertexLayout.GetAddressOf());
		if (FAILED(hr))
		{
			panicF("Failed to create vertex layout!");
		}
	}

	static void compileShaderFromFile(const wchar_t * fileName, const char * entryPoint,
		const char * shaderModel, ID3DBlob ** ppBlobOut)
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
			auto * details = (pErrorBlob ? static_cast<const char *>(pErrorBlob->GetBufferPointer()) : "<no info>");
			panicF("Failed to compile shader! Error info: %s", details);
		}
	}
};

class RenderInterfaceD3D11 final
	: public dd::RenderInterface
{
public:

	RenderInterfaceD3D11(const ComPtr<ID3D11Device> & pDevice, const ComPtr<ID3D11DeviceContext> & pContext)
		: d3dDevice(pDevice)
		, deviceContext(pContext)
	{
		initShaders();
		initBuffers();
	}

	void setMvpMatrixPtr(const float* const mtx)
	{
		constantBufferData.mvpMatrix = DirectX::XMMATRIX(mtx);
	}

	void setCameraFrame(const Vector3 & up, const Vector3 & right, const Vector3 & origin)
	{
		camUp = up; camRight = right; camOrigin = origin;
	}

	//
	// dd::RenderInterface overrides:
	//

	void beginDraw() override
	{
		// Update and set the constant buffer for this frame
		deviceContext->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &constantBufferData, 0, 0);
		deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

		// Disable culling for the screen text
		deviceContext->RSSetState(rasterizerState.Get());
	}

	void endDraw() override
	{
		// No work done here at the moment.
	}

	dd::GlyphTextureHandle createGlyphTexture(int width, int height, const void * pixels) override
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

		auto * texImpl = new TextureImpl{};

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

	void destroyGlyphTexture(dd::GlyphTextureHandle glyphTex) override
	{
		auto * texImpl = static_cast<TextureImpl *>(glyphTex);
		if (texImpl)
		{
			if (texImpl->d3dSampler) { texImpl->d3dSampler->Release(); }
			if (texImpl->d3dTexSRV) { texImpl->d3dTexSRV->Release(); }
			if (texImpl->d3dTexPtr) { texImpl->d3dTexPtr->Release(); }
			delete texImpl;
		}
	}

	void drawGlyphList(const dd::DrawVertex * glyphs, int count, dd::GlyphTextureHandle glyphTex) override
	{
		assert(glyphs != nullptr);
		assert(count > 0 && count <= DEBUG_DRAW_VERTEX_BUFFER_SIZE);

		auto * texImpl = static_cast<TextureImpl *>(glyphTex);
		assert(texImpl != nullptr);

		// Map the vertex buffer:
		D3D11_MAPPED_SUBRESOURCE mapInfo;
		if (FAILED(deviceContext->Map(glyphVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapInfo)))
		{
			panicF("Failed to map vertex buffer!");
		}

		// Copy into mapped buffer:
		auto * verts = static_cast<Vertex *>(mapInfo.pData);
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

	void drawPointList(const dd::DrawVertex * points, int count, bool depthEnabled) override
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
		auto * verts = static_cast<Vertex *>(mapInfo.pData);

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

	void drawLineList(const dd::DrawVertex * lines, int count, bool depthEnabled) override
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
		auto * verts = static_cast<Vertex *>(mapInfo.pData);
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

private:

	//
	// Local types:
	//

	struct ConstantBufferData
	{
		DirectX::XMMATRIX mvpMatrix = DirectX::XMMatrixIdentity();
		DirectX::XMFLOAT4 screenDimensions = { float(1920), float(1080), 0.0f, 0.0f };
	};

	struct Vertex
	{
		DirectX::XMFLOAT4A pos;   // 3D position
		DirectX::XMFLOAT4A uv;    // Texture coordinates
		DirectX::XMFLOAT4A color; // RGBA float
	};

	struct TextureImpl : public dd::OpaqueTextureType
	{
		ID3D11Texture2D          * d3dTexPtr = nullptr;
		ID3D11ShaderResourceView * d3dTexSRV = nullptr;
		ID3D11SamplerState       * d3dSampler = nullptr;
	};

	//
	// Members:
	//

	ComPtr<ID3D11Device>          d3dDevice;
	ComPtr<ID3D11DeviceContext>   deviceContext;
	ComPtr<ID3D11RasterizerState> rasterizerState;
	ComPtr<ID3D11BlendState>      blendStateText;

	ComPtr<ID3D11Buffer>          constantBuffer;
	ConstantBufferData            constantBufferData;

	ComPtr<ID3D11Buffer>          lineVertexBuffer;
	ShaderSetD3D11                lineShaders;

	ComPtr<ID3D11Buffer>          pointVertexBuffer;
	ShaderSetD3D11                pointShaders;

	ComPtr<ID3D11Buffer>          glyphVertexBuffer;
	ShaderSetD3D11                glyphShaders;

	// Camera vectors for the emulated point sprites
	Vector3                       camUp = Vector3{ 0.0f };
	Vector3                       camRight = Vector3{ 0.0f };
	Vector3                       camOrigin = Vector3{ 0.0f };

	void initShaders()
	{
		// Same vertex format used by all buffers to simplify things.
		const D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		const ShaderSetD3D11::InputLayoutDesc inputDesc{ layout, int(ARRAYSIZE(layout)) };

		// 3D lines shader:
		lineShaders.loadFromFxFile(d3dDevice.Get(), L"ddShader.fx",
			"VS_LinePoint", "PS_LinePoint", inputDesc);

		// 3D points shader:
		pointShaders.loadFromFxFile(d3dDevice.Get(), L"ddShader.fx",
			"VS_LinePoint", "PS_LinePoint", inputDesc);

		// 2D glyphs shader:
		glyphShaders.loadFromFxFile(d3dDevice.Get(), L"ddShader.fx",
			"VS_TextGlyph", "PS_TextGlyph", inputDesc);

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

	void initBuffers()
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

	void drawHelper(const int numVerts, const ShaderSetD3D11 & ss,
		ID3D11Buffer * vb, const D3D11_PRIMITIVE_TOPOLOGY topology)
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
};