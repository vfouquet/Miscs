#pragma once

class InputDevice
{
public:
	InputDevice(const InputDevice&) = delete;
	InputDevice(InputDevice&&) = delete;
	virtual ~InputDevice() = default;


	auto operator =(const InputDevice&) -> InputDevice& = delete;
	auto operator =(InputDevice&&) -> InputDevice& = delete;


	static auto	Initialize(Platform::Window::NativeHandle windowHandle) -> bool;
	static auto	Shutdown() -> void;

private:
	InputDevice() = default;
};
