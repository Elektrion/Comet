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

	Scope<Window> Window::createWindow(const WindowProperties& props) {
#if defined(CMT_PLATFORM_WINDOWS)
		return makeScope<WindowsWindow>(props);
#elif defined(CMT_PLATFORM_MACOS)
		return makeScope<MacOSWindow>(props);
#endif
		return Scope<Window>(nullptr);
	}

}
