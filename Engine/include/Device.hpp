#pragma once

class Device
{
public:
	Device() = default;
	~Device() = default;

	auto	Initialize(const char* windowName, int32 windowWidth, int32 windowHeight) -> void;
	auto	Run() -> bool;
	auto	Shutdown() -> void;
};