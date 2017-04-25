#ifndef UNICODE
#define UNICODE
#endif 

#include "Engine/include/Engine.hpp"

#ifdef _DEBUG
int main()
{
	WinMain(GetModuleHandle(nullptr), nullptr, nullptr, 0);
	return 0;
}
#endif

int CALLBACK WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Device device;
	device.Initialize("Engine", CW_USEDEFAULT, CW_USEDEFAULT);

	while (device.Run())
	{
	}

	device.Shutdown();

	return 0;
}