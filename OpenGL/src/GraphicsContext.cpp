#include "OpenGL/include/OpenGL.hpp"

#include <iostream>

auto	OpenGL::GraphicsContext::Initialize(void* windowHandle) -> void*
{
	mHdc = GetDC((HWND)windowHandle);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	mPixelFormat = ChoosePixelFormat(mHdc, &pfd);
	SetPixelFormat(mHdc, mPixelFormat, &pfd);

	HGLRC tempContext = wglCreateContext(mHdc);
	wglMakeCurrent(mHdc, tempContext);

//	glewExperimental = TRUE;
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		std::cout << "GLEW is not initialized !" << std::endl;
		return nullptr;
	}

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 5,
		WGL_CONTEXT_FLAGS_ARB, 0,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		0
	};
	
	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		mHglrc = wglCreateContextAttribsARB(mHdc, nullptr, attribs);
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(tempContext);
		wglMakeCurrent(mHdc, mHglrc);
	}
	else
	{
		mHglrc = tempContext;
	}

	LOG_INFO("OpenGL Version : "  + string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
	LOG_INFO("Vendor : " + reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	LOG_INFO("Driver : " + reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

	return nullptr;
}

auto	OpenGL::GraphicsContext::Shutdown() -> void
{
	wglMakeCurrent(mHdc, nullptr);
	wglDeleteContext(mHglrc);
}

auto	OpenGL::GraphicsContext::Render() -> void
{
	glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	wglSwapLayerBuffers(mHdc, WGL_SWAP_MAIN_PLANE);
}