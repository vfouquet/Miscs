#pragma once

#include "Core/include/Core.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif

namespace Platform
{
#include "Timer.hpp"
#include "Window.hpp"
#include "DynamicLibrary.hpp"
#include "Event.hpp"
}
