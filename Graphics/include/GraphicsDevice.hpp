#pragma once

class GraphicsDevice
{
public:
	~GraphicsDevice() = default;

	static auto	Context() -> IGraphicsContext*;

	static auto Initialize(void* windowHandle) -> void;
	static auto	Shutdown() -> void;

private:
	GraphicsDevice() = default;

	auto	mInitialize(void* windowHandle) -> void;
	auto	mShutdown() -> void;

	Platform::DynamicLibrary*	mGraphicsDL;
	IGraphicsContext*			mGraphicsContext;
};