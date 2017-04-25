#pragma once

#if defined _WIN32

#define FORCEINLINE __forceinline

#else

#define FORCEINLINE inline

#endif

#ifdef _WIN32
# ifdef COMPILE_CORE
#  define CORE_EXTERNAL __declspec(dllexport) 
# else
#  define CORE_EXTERNAL __declspec(dllimport) 
# endif
#else
# define CORE_EXTERNAL
#endif

#include <functional>
#include <string>

#include "Types.hpp"

namespace Core
{
#include "Logger.hpp"
}

#include "Platform/include/Platform.hpp"