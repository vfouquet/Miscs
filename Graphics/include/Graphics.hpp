#pragma once

#ifdef _WIN32
# ifdef COMPILE_GRAPHICS
#  define GRAPHICS_EXTERNAL __declspec(dllexport) 
# else
#  define GRAPHICS_EXTERNAL __declspec(dllimport) 
# endif
#else
# define EXTERNAL
#endif

#include "Core/include/Core.hpp"

namespace Graphics
{
#include "IGraphicsContext.hpp"

#include "GraphicsDevice.hpp"
} // Graphics
