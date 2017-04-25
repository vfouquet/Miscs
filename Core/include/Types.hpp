#pragma once

#include <vector>
#include <list>
#include <map>

#if defined _WIN32

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using int128 = long long int;

#else

using int8 = short int;
using int16 = short int;
using int32 = int;
using int64 = long int;
using int128 = long long int;

#endif

using uint8 = unsigned short int;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long int;
using uint128 = unsigned long long int;

using string = std::string;

#define vector	std::vector
#define list	std::list
#define map		std::map