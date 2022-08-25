#include "cmt_pch.h"
#include "LayerStack.h"

namespace comet {

	LayerStack::~LayerStack() {
		clear();
	}

	void LayerStack::push(Ref<Layer> layer) {
		auto iter = std::ranges::find(layers, layer);
		if(iter == layers.end()) {
			layers.insert(layers.begin() + insertion_index, layer);
			layer->onAttatch();
			insertion_index++;
		}
		else
			CMT_CORE_WARN("Layer has already been added to the layerstack!");
	}

	void LayerStack::pop(Ref<Layer> layer) {
		auto iter = std::ranges::find(layers, layer);
		if(iter != layers.end()) {
			if(size_t(iter - layers.begin()) >= insertion_index)
				CMT_CORE_WARN("The popped layer was an overlay layer, popping it anyway");
			else
				insertion_index--;
			layers.erase(iter);
		}
		else
			CMT_CORE_WARN("Layer is not in the layerstack!");
	}

	void LayerStack::pushOverlay(Ref<Layer> layer) {
		auto iter = std::ranges::find(layers, layer);
		if(iter == layers.end()) {
			layers.push_back(layer);
			layer->onAttatch();
		}
		else
			CMT_CORE_WARN("Layer has already been added to the layerstack!");
	}

	void LayerStack::popOverlay(Ref<Layer> layer) {
		auto iter = std::ranges::find(layers, layer);
		if(iter != layers.end()) {
			if(size_t(iter - layers.begin()) < insertion_index) {
				CMT_CORE_WARN("The popped layer wasn't an overlay layer, popping it anyway");
				insertion_index--;
			}
			layers.erase(iter);
		}
		else
			CMT_CORE_WARN("Layer is not in the layerstack!");
	}

	void LayerStack::clear() {
		for(auto layer : layers)
			layer->onDetatch();
		insertion_index = 0;
		layers.clear();
	}

}
