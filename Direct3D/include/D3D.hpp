#pragma once

#include <d3d11.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#endif

#include "Graphics/include/Graphics.hpp"

namespace D3D
{
#include "GraphicsContext.hpp"
} // D3D

extern "C" auto	GRAPHICS_EXTERNAL createContext() -> D3D::GraphicsContext*
{
	return new D3D::GraphicsContext();
}

extern "C" auto GRAPHICS_EXTERNAL destroyContext(D3D::GraphicsContext* graphicsContext) -> void
{
	if (graphicsContext)
	{
		delete graphicsContext;
	}
}