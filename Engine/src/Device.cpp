#include "Engine/include/Engine.hpp"

#include <iostream>

auto	DefaultOutput(const string& log) -> void
{
	std::cout << log << std::endl;
}

auto	Device::Initialize(const char* windowName, int32 windowWidth, int32 windowHeight) -> void
{
	Core::Logger::Initialize();
	Core::Logger::RegisterOutputCallback(DefaultOutput);
	LOG("Initializing Device...");

	if (!Platform::Window::Create(windowName, windowWidth, windowHeight))
		return;

	Platform::Window::WindowSize size = Platform::Window::Size();

	LOG("Window width : " + std::to_string(size.width) + ", height : " + std::to_string(size.height));

	Graphics::GraphicsDevice::Initialize(Platform::Window::NativeWindow());
	LOG("Device initialized.");
}


auto	Device::Run() -> bool
{
	if (Platform::Window::HandleMessage())
	{
		Graphics::GraphicsDevice::Context()->Render();
		return true;
	}

	/*Platform::Event	event;

	while (Platform::Event::GetEvent(event))
	{
		if (event.Type() == Platform::Event::EType::WINDOW_CLOSE)
			return false;
	}

	Graphics::GraphicsDevice::Context()->Render();*/

	return false;
}


auto	Device::Shutdown() -> void
{
	Graphics::GraphicsDevice::Shutdown();
	Core::Logger::Shutdown();
}
