#pragma once


class DynamicLibrary
{
public:

#ifdef _WIN32
	using NativeHandle = HINSTANCE;
#else
	using NativeHandle = void*;
#endif

	DynamicLibrary() = delete;
	DynamicLibrary(const char* dlName);
	DynamicLibrary(const DynamicLibrary&) = delete;
	DynamicLibrary(DynamicLibrary&&) = delete;
	~DynamicLibrary();

//	static auto	LoadDL(const char* dlName) -> const DynamicLibrary*;
//	static auto	UnloadDL(const DynamicLibrary* dl) -> bool;

	auto	IsValid() const -> bool
	{
		return mHandle ? true : false;
	}

	auto	LoadSymbol(const char* symbolName) const -> void*;

private:
//	DynamicLibrary(NativeHandle handle)
//		: mHandle(handle) {}

	NativeHandle	mHandle;
};