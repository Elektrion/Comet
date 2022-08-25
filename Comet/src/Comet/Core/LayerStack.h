#pragma once

#include <vector>

#include "Comet/Core/Core.h"
#include "Comet/Core/Layer.h"

namespace comet {

	class LayerStack {
	public:
		constexpr inline LayerStack() : layers(), insertion_index(0) {}
		~LayerStack();

		void push(Ref<Layer> layer);
		void pop(Ref<Layer> layer);
		void pushOverlay(Ref<Layer> layer);
		void popOverlay(Ref<Layer> layer);

		void clear();

		constexpr inline std::vector<Ref<Layer>>::iterator begin() { return layers.begin(); }
		constexpr inline std::vector<Ref<Layer>>::const_iterator begin() const { return layers.begin(); }
		constexpr inline std::vector<Ref<Layer>>::iterator end() { return layers.end(); }
		constexpr inline std::vector<Ref<Layer>>::const_iterator end() const { return layers.end(); }
	private:
		std::vector<Ref<Layer>> layers;
		size_t insertion_index;
	};

}
