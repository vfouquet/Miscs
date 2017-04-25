#include "Graphics/include/Graphics.hpp"

Graphics::GraphicsDevice* gGraphicsDevice = nullptr;

using CreateContextFunc = Graphics::IGraphicsContext* (*)();
using DestroyContextFunc = void(*)(Graphics::IGraphicsContext*);

auto	Graphics::GraphicsDevice::Context() -> IGraphicsContext*
{
	if (gGraphicsDevice)
	{
		return gGraphicsDevice->mGraphicsContext;
	}

	return nullptr;
}


auto	Graphics::GraphicsDevice::Initialize(void* windowHandle) -> void
{
	if (!gGraphicsDevice)
	{
		gGraphicsDevice = new GraphicsDevice();
		gGraphicsDevice->mInitialize(windowHandle);
	}
}


auto Graphics::GraphicsDevice::Shutdown() -> void
{
	if (gGraphicsDevice)
	{
		gGraphicsDevice->mShutdown();
		delete gGraphicsDevice;
	}
}


auto	Graphics::GraphicsDevice::mInitialize(void* windowHandle) -> void
{
	mGraphicsDL = new Platform::DynamicLibrary("Direct3D");
	
	if (mGraphicsDL->IsValid())
	{
		CreateContextFunc func = reinterpret_cast<CreateContextFunc>(mGraphicsDL->LoadSymbol("createContext"));
		if (func)
		{
			mGraphicsContext = func();

			if (mGraphicsContext)
			{
				mGraphicsContext->Initialize(windowHandle);
			}
			else
			{
				LOG_ERROR("Failed to create graphics context");
			}
		}
		else
		{
			LOG_ERROR("Failed to load function");
			return;
		}
	}
	else
	{
		LOG_ERROR("Failed to load \"OpenGL\" dynamic library")
		return;
	}
}


auto	Graphics::GraphicsDevice::mShutdown() -> void
{
	if (mGraphicsDL)
	{
		if (mGraphicsContext)
		{
			mGraphicsContext->Shutdown();
			
			DestroyContextFunc func = (DestroyContextFunc)mGraphicsDL->LoadSymbol("destroyContext");

			if (func)
			{
				func(mGraphicsContext);
			}
		}

		delete mGraphicsDL;
	}

}
