#pragma once

class GraphicsContext : public Graphics::IGraphicsContext
{
public:
	GraphicsContext() = default;
	~GraphicsContext() = default;

	auto	Initialize(void* windowHandle) -> void* override;
	auto	Shutdown() -> void override;
	auto	Render() -> void override;


private:
	ID3D11Device*			mD3dDevice = nullptr;
	ID3D11DeviceContext*	mD3dDeviceImmediateContext = nullptr;
	IDXGISwapChain*			mSwapChain = nullptr;

	ID3D11RenderTargetView*	mMainRenderTargetView = nullptr;

	INT32					mFeatureLevelIndex;
};
