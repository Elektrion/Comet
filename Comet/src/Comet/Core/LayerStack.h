#pragma once

#include <vector>

#include "Comet/Core/Core.h"
#include "Comet/Core/Layer.h"

namespace comet {

	class LayerStack {
	public:
		inline LayerStack() noexcept : layers(), insertion_index(0) {}
		~LayerStack();

		inline LayerStack(const LayerStack&) noexcept = delete;
		inline LayerStack(const LayerStack&&) noexcept = delete;
		inline LayerStack& operator=(const LayerStack&) noexcept = delete;
		inline LayerStack& operator=(const LayerStack&&) noexcept = delete;

		void push(const Ref<Layer>& layer) noexcept;
		void pop(const Ref<Layer>& layer) noexcept;
		void pushOverlay(const Ref<Layer>& layer) noexcept;
		void popOverlay(const Ref<Layer>& layer) noexcept;

		void clear();

		inline std::vector<Ref<Layer>>::iterator begin() noexcept { return layers.begin(); }
		inline std::vector<Ref<Layer>>::const_iterator begin() const noexcept { return layers.begin(); }
		inline std::vector<Ref<Layer>>::iterator end() noexcept { return layers.end(); }
		inline std::vector<Ref<Layer>>::const_iterator end() const noexcept { return layers.end(); }

		inline std::vector<Ref<Layer>>::reverse_iterator rbegin() noexcept { return layers.rbegin(); }
		inline std::vector<Ref<Layer>>::const_reverse_iterator rbegin() const noexcept { return layers.rbegin(); }
		inline std::vector<Ref<Layer>>::reverse_iterator rend() noexcept { return layers.rend(); }
		inline std::vector<Ref<Layer>>::const_reverse_iterator rend() const noexcept { return layers.rend(); }
	private:
		std::vector<Ref<Layer>> layers;
		size_t insertion_index;
	};

}
