#pragma once

#include <vector>

#include "Comet/Core/Core.h"
#include "Comet/Core/Layer.h"

namespace comet {

	class LayerStack {
	public:
		inline LayerStack() : layers(), insertion_index(0) {}
		~LayerStack();

		void push(Ref<Layer> layer);
		void pop(Ref<Layer> layer);
		void pushOverlay(Ref<Layer> layer);
		void popOverlay(Ref<Layer> layer);

		void clear();

		inline std::vector<Ref<Layer>>::iterator begin() { return layers.begin(); }
		inline std::vector<Ref<Layer>>::const_iterator begin() const { return layers.begin(); }
		inline std::vector<Ref<Layer>>::iterator end() { return layers.end(); }
		inline std::vector<Ref<Layer>>::const_iterator end() const { return layers.end(); }

		inline std::vector<Ref<Layer>>::reverse_iterator rbegin() { return layers.rbegin(); }
		inline std::vector<Ref<Layer>>::const_reverse_iterator rbegin() const { return layers.rbegin(); }
		inline std::vector<Ref<Layer>>::reverse_iterator rend() { return layers.rend(); }
		inline std::vector<Ref<Layer>>::const_reverse_iterator rend() const { return layers.rend(); }
	private:
		std::vector<Ref<Layer>> layers;
		size_t insertion_index;
	};

}
