#include "Platform/include/Platform.hpp"

#ifdef _WIN32
auto	Platform::Event::GetEvent(Platform::Event& event) -> bool
{
	static MSG msg{ nullptr };

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_DESTROY)
		{
			event.mType = EType::WINDOW_CLOSE;
		}
		else
		{
			event.mType = EType::UNKNOWN;
		}
		
		return true;
	}
	event.mType = EType::NONE;
	return false;
}

#else

auto	Platform::Event::GetEvent(Platform::Event& event) -> bool
{
	return false;
}
#endif
