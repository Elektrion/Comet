#pragma once

#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"

namespace comet {

	class Layer {
	public:
		inline Layer() = default;
		virtual ~Layer() = default;

		inline Layer(const Layer&) = delete;
		inline Layer(const Layer&&) = delete;
		inline Layer& operator=(const Layer&) = delete;
		inline Layer& operator=(const Layer&&) = delete;

		virtual void onAttatch() {}
		virtual void onDetatch() {}

		virtual void onUpdate(Timestep dt) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& e) {}
	};

}
