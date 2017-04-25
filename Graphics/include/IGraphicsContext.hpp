#pragma once

class IGraphicsContext
{
public:
	virtual ~IGraphicsContext() = default;

	virtual auto	Initialize(void* windowHandle) -> void* = 0;
	virtual auto	Shutdown() -> void = 0;

	virtual auto	Render() -> void = 0;
};