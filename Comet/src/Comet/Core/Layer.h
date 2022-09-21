#pragma once

#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"

namespace comet {

	class Layer {
	public:
		inline Layer() noexcept = default;
		virtual ~Layer() noexcept = default;

		inline Layer(const Layer&) noexcept = delete;
		inline Layer(const Layer&&) noexcept = delete;
		inline Layer& operator=(const Layer&) noexcept = delete;
		inline Layer& operator=(const Layer&&) noexcept = delete;

		virtual void onAttatch() {}
		virtual void onDetatch() {}

		virtual void onUpdate(Timestep dt) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& e) {}
	};

}
