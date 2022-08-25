#pragma once

#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"

namespace comet {

	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void onAttatch() {}
		virtual void onDetatch() {}

		virtual void onUpdate(Timestep dt) {}
		virtual void onEvent(Event& e) {}
	};

}
