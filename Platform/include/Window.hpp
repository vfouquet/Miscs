#pragma once


class Window final
{
public:
#ifdef _WIN32
	using NativeHandle = HWND;
#else
	using NativeHandle = xlib::Window;
#endif

	struct WindowSize
	{
		int32 x, y;
		int32 width, height;
	};

	static auto	Size()->WindowSize;
	static auto	NativeWindow()->NativeHandle& { return mWindow.mNativeHandle; };

	static auto	Create(const char* wName, int32 wWidth, int32 wHeight) -> bool;
	static auto	Destroy() -> void;
	static auto	HandleMessage() -> bool;


private:
	Window() = default;

#ifdef _WIN32
	static LRESULT CALLBACK mWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#else

#endif

	auto	mCheckInstance() -> void;

	static Window	mWindow;

	NativeHandle	mNativeHandle;
};


