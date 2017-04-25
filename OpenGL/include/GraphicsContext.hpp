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
	HDC		mHdc;
	HGLRC	mHglrc;
	int32	mPixelFormat;
};

