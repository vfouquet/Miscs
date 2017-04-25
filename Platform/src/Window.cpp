#include "Platform/include/Platform.hpp"

#include <windowsx.h>

Platform::Window Platform::Window::mWindow;


#ifdef _WIN32


auto	Platform::Window::Create(const char* wName, int32 wWidth, int32 wHeight) -> bool
{
	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = mWindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = wName;

	RegisterClass(&wc);

	mWindow.mNativeHandle = CreateWindowEx(0, wName, wName, WS_OVERLAPPEDWINDOW | CS_OWNDC, CW_USEDEFAULT, CW_USEDEFAULT, wWidth, wHeight, nullptr, nullptr, wc.hInstance, nullptr);

	if (mWindow.mNativeHandle)
	{
		ShowWindow(mWindow.mNativeHandle, SW_SHOW);
		return true;
	}

	return false;
}


auto	Platform::Window::Destroy() -> void
{
	DestroyWindow(mWindow.mNativeHandle);
	PostQuitMessage(0);
}

auto Platform::Window::HandleMessage() -> bool
{
	static MSG msg { nullptr };

	if (!mWindow.mNativeHandle)
	{
		return false;
	}

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message != WM_QUIT)
			return true;

	return false;
}



auto Platform::Window::Size() -> WindowSize
{
	RECT rect;
	GetWindowRect(mWindow.mNativeHandle, &rect);

	return WindowSize{ rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top };
}


LRESULT Platform::Window::mWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
//		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


#else

auto	Platform::Window::Create() -> void
{

}


auto	Platform::Window::Destroy() -> void
{

}


auto Platform::Window::Size() -> WindowSize
{

}

#endif