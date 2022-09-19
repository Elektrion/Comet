#include "cmt_pch.h"
#include "Window.h"

#if defined(CMT_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsWindow.h"
#elif defined(CMT_PLATFORM_MACOS)
	#include "Platform/MacOS/MacOSWindow.h"
#else
	#error "Platform not supported!"
#endif

namespace comet {

	Scope<Window> Window::create(const WindowProperties& props) {
#if defined(CMT_PLATFORM_WINDOWS)
		return createScope<WindowsWindow>(props);
#elif defined(CMT_PLATFORM_MACOS)
		return createScope<MacOSWindow>(props);
#endif
		return nullptr;
	}

}
