#pragma once
#include "ShaderSetD3D11.h"

class RenderInterfaceD3D11 final : public dd::RenderInterface
{
public:
	RenderInterfaceD3D11(const ComPtr<ID3D11Device>& pDevice, const ComPtr<ID3D11DeviceContext>& pContext) : d3dDevice(pDevice), deviceContext(pContext)
	{
		initShaders();
		initBuffers();
	}

    void setMvpMatrixPtr(const float* const mtx);
    void setCameraFrame(const Vector3& up, const Vector3& right, const Vector3& origin);

	//dd::RenderInterface overrides:
    void beginDraw() override;
    void endDraw() override;

    dd::GlyphTextureHandle createGlyphTexture(int width, int height, const void* pixels) override;
    void destroyGlyphTexture(dd::GlyphTextureHandle glyphTex) override;
    
    void drawGlyphList(const dd::DrawVertex* glyphs, int count, dd::GlyphTextureHandle glyphTex) override;
    void drawPointList(const dd::DrawVertex* points, int count, bool depthEnabled) override;

    void drawLineList(const dd::DrawVertex* lines, int count, bool depthEnabled) override;

private:

	//Local types:
	struct ConstantBufferData
	{
		DirectX::XMMATRIX mvpMatrix = DirectX::XMMatrixIdentity();
		DirectX::XMFLOAT4 screenDimensions = { float(1920), float(1080), 0.0f, 0.0f };
	};

	struct Vertex
	{
		DirectX::XMFLOAT4A pos; //3D position
		DirectX::XMFLOAT4A uv; //Texture coordinates
		DirectX::XMFLOAT4A color; //RGBA float
	};

	struct TextureImpl : public dd::OpaqueTextureType
	{
		ID3D11Texture2D* d3dTexPtr = nullptr;
		ID3D11ShaderResourceView* d3dTexSRV = nullptr;
		ID3D11SamplerState* d3dSampler = nullptr;
	};

	//Members:

	ComPtr<ID3D11Device> d3dDevice;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<ID3D11RasterizerState> rasterizerState;
	ComPtr<ID3D11BlendState> blendStateText;

	ComPtr<ID3D11Buffer> constantBuffer;
	ConstantBufferData constantBufferData;

	ComPtr<ID3D11Buffer> lineVertexBuffer;
	ShaderSetD3D11 lineShaders;

	ComPtr<ID3D11Buffer> pointVertexBuffer;
	ShaderSetD3D11 pointShaders;

	ComPtr<ID3D11Buffer> glyphVertexBuffer;
	ShaderSetD3D11 glyphShaders;

	// Camera vectors for the emulated point sprites
	Vector3 camUp = Vector3{ 0.0f };
	Vector3 camRight = Vector3{ 0.0f };
	Vector3 camOrigin = Vector3{ 0.0f };

    void initShaders();
    void initBuffers();
    void drawHelper(const int numVerts, const ShaderSetD3D11& ss, ID3D11Buffer* vb, const D3D11_PRIMITIVE_TOPOLOGY topology);
};