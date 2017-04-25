#include "Direct3D/include/D3D.hpp"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#endif

auto	D3D::GraphicsContext::Initialize(void* windowHandle) -> void*
{
	LOG("Initializing D3D Context...");
	const D3D_FEATURE_LEVEL featureLevelArray[] = { D3D_FEATURE_LEVEL_11_0
		, D3D_FEATURE_LEVEL_10_1
		, D3D_FEATURE_LEVEL_10_0
		, D3D_FEATURE_LEVEL_9_3 };

	uint32 featureLevelCount = 4u;

	HRESULT hr = S_OK;
	HWND hwnd = static_cast<HWND>(windowHandle);


	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.Windowed = TRUE;
	sd.OutputWindow = hwnd;
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.SampleDesc.Count = 1;

	UINT createDeviceFlag = 0u;

#ifdef _DEBUG
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel;
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlag, featureLevelArray
		, featureLevelCount, D3D11_SDK_VERSION, &sd, &mSwapChain, &mD3dDevice, &featureLevel, &mD3dDeviceImmediateContext);

	if FAILED(hr)
		return &hr;

	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_0: mFeatureLevelIndex = 0; break;
	case D3D_FEATURE_LEVEL_10_1: mFeatureLevelIndex = 1; break;
	case D3D_FEATURE_LEVEL_10_0: mFeatureLevelIndex = 2; break;
	case D3D_FEATURE_LEVEL_9_3: mFeatureLevelIndex = 3; break;
	default:
		return &hr;
	}

	UINT backBufferWidth, backBufferHeight;
	ID3D11Texture2D* pBackBuffer;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if FAILED(hr)
		return &hr;
	D3D11_TEXTURE2D_DESC backBufferTextureDesc;
	pBackBuffer->GetDesc(&backBufferTextureDesc);
	backBufferWidth = backBufferTextureDesc.Width;
	backBufferHeight = backBufferTextureDesc.Height;
	hr = mD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mMainRenderTargetView);
	if FAILED(hr)
		return &hr;
	mD3dDeviceImmediateContext->OMSetRenderTargets(1, &mMainRenderTargetView, nullptr);
	pBackBuffer->Release();

	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof D3D11_VIEWPORT);
	vp.MinDepth = 0.0;
	vp.MaxDepth = 1.0f;
	vp.Width = (float)backBufferWidth;
	vp.Height = (float)backBufferHeight;
	mD3dDeviceImmediateContext->RSSetViewports(1, &vp);

	LOG("D3D Context initialized.");
	return &hr;
}


auto	D3D::GraphicsContext::Shutdown() -> void
{
	if (mD3dDeviceImmediateContext)
	{
		mD3dDeviceImmediateContext->ClearState();
	}

	SAFE_RELEASE(mMainRenderTargetView);
	SAFE_RELEASE(mSwapChain);
	SAFE_RELEASE(mD3dDeviceImmediateContext);
	SAFE_RELEASE(mD3dDevice);
}


auto	D3D::GraphicsContext::Render() -> void
{
	static float c = 0.2f;

	static float clearColor[] = { c, c, c, 1.0f };

/*	clearColor[0] = c;
	clearColor[1] = c;
	clearColor[2] = c;*/

	mD3dDeviceImmediateContext->ClearRenderTargetView(mMainRenderTargetView, clearColor);

	mD3dDeviceImmediateContext->VSSetShader(nullptr, nullptr, 0);
	mD3dDeviceImmediateContext->PSSetShader(nullptr, nullptr, 0);

	mSwapChain->Present(0, 0);

/*	c += 0.1f;

	if (c > 0.8f)
		c = 0.2f;*/
}
