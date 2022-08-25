#include "cmt_pch.h"
#include "Window.h"

#if defined(CMT_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsWindow.h"
#else
	#error "Platform not supported!"
#endif

namespace comet {

	Scope<Window> Window::createWindow(const WindowProperties& props) {
#if defined(CMT_PLATFORM_WINDOWS)
		return makeScope<WindowsWindow>(props);
#endif
		return Scope<Window>(nullptr);
	}

}
