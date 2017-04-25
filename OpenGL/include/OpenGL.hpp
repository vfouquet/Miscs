#pragma once

#include <OpenGL/glew-1.13.0/include/GL/glew.h>

#ifdef _WIN32
#include <OpenGL/glew-1.13.0/include/GL/wglew.h>
#endif

#include "Graphics/include/Graphics.hpp"


namespace OpenGL
{
#include "GraphicsContext.hpp"
}

extern "C" auto GRAPHICS_EXTERNAL createContext() -> OpenGL::GraphicsContext*
{
	return new OpenGL::GraphicsContext();
}

extern "C" auto GRAPHICS_EXTERNAL destroyContext(OpenGL::GraphicsContext* graphicsContext) -> void
{
	if (graphicsContext)
	{
		delete graphicsContext;
	}
}