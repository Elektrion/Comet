#pragma once

#include "Comet/Core/Window.h"

namespace comet {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& props);

		virtual inline uint32_t getWidth() const override { return width; }
		virtual inline uint32_t getHeight() const override { return height; }
	private:
		uint32_t width;
		uint32_t height;
	};

}