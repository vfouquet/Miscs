#include "Platform/include/Platform.hpp"


/*class DynamicLibraryManager
{
	friend class DynamicLibrary;

public:
	DynamicLibraryManager() = default;
	~DynamicLibraryManager() = default;

	auto	LoadDL(const char* dlName) -> const DynamicLibrary*;
	auto	UnloadDL(const DynamicLibrary* dl) -> void;

private:
	vector<DynamicLibrary*>	mDLs;
};


DynamicLibraryManager	gDynamicLibraryMgr;


auto DynamicLibraryManager::LoadDL(const char* dlName) -> const DynamicLibrary*
{
	/*HINSTANCE	handle = LoadLibrary(dlName);

	if (handle)
	{
		for (uint32 i = 0u; i < mDLs.size(); ++i)
		{
			if (handle == mDLs[i]->handle)
		}

		mDLs.push_back(dlName);
	}
#1#
	return nullptr;

}


auto DynamicLibraryManager::UnloadDL(const DynamicLibrary* dl) -> void
{
}*/


#ifdef _WIN32


/*auto	Platform::DynamicLibrary::LoadDL(const char* dlName) -> const DynamicLibrary*
{
	/*HINSTANCE	handle = LoadLibrary(dlName);

	if (handle)
	{
		gDynamicLibraryMgr.mDLs
	}#1#

	return nullptr;
}


auto	Platform::DynamicLibrary::UnloadDL(const DynamicLibrary* dl) -> bool
{
	return false;
}*/


Platform::DynamicLibrary::DynamicLibrary(const char* dlName)
{
	string s = dlName;
	s += ".dll";

	mHandle = LoadLibrary(s.c_str());
}

Platform::DynamicLibrary::~DynamicLibrary()
{
	if (mHandle)
	{
		FreeLibrary(mHandle);
	}
}


auto	Platform::DynamicLibrary::LoadSymbol(const char* symbolName) const -> void*
{
	if (mHandle)
	{
		return GetProcAddress(mHandle, symbolName);
	}

	return nullptr;
}


#else

Platform::DynamicLibrary::DynamicLibrary(const char* dlName)
{
	string s = "lib";
	s += dlName;
	s += ".so";

	mHandle = dlopen(s.c_str(), RTLD_LAZY);
}

Platform::DynamicLibrary::~DynamicLibrary()
{
	if (mHandle)
	{
		dlclose(mHandle);
	}
}


/*auto	Platform::DynamicLibrary::LoadDL(const string& dlName) -> const DynamicLibrary*
{

}


auto	Platform::DynamicLibrary::UnloadDL(const DynamicLibrary* dl) -> bool
{

}*/


auto	Platform::DynamicLibrary::LoadSymbol(const string& symbolName) -> void*
{
	if (mHandle)
	{
		return dlsym(mHandle, symbolName);
	}

	return nullptr;
}


#endif