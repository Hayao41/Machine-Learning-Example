#include "layer/HiddenLayer.h"
#include "layer/DataLayer.h"
#include "layer/OutputLayer.h"
#include "Network.h"

#ifndef TRAINMETHOD_H
#define TRAINMETHOD_H

class TrainMethod{
public:
	TrainMethod(){}
	virtual ~TrainMethod() = default;

	virtual void train(std::vector<Layer*>& layers,std::vector<Passenger>& sample_set) = 0;

	void forward_pass(std::vector<Layer*>& layers){
		std::vector<Layer*>::iterator layer;
		std::vector<Layer*>::iterator layer_begin = layers.begin();
		std::vector<Layer*>::iterator layer_end = layers.end();
		for (layer = layer_begin; layer != layer_end; layer++){
			(*layer)->forward();
		}
	}

	void backword_pass(std::vector<Layer*>& layers){
		std::vector<Layer*>::reverse_iterator layer;
		std::vector<Layer*>::reverse_iterator layer_end = layers.rbegin();
		std::vector<Layer*>::reverse_iterator layer_begin = layers.rend();
		for (layer = layer_end; layer != layer_begin; layer++){
			(*layer)->backward();
		}
	}

	void updateWeights(std::vector<Layer*>& layers){
		std::vector<Layer*>::iterator layer;
		std::vector<Layer*>::iterator layer_begin = layers.begin();
		std::vector<Layer*>::iterator layer_end = layers.end();
		for (layer = layer_begin; layer != layer_end; layer++){
			(*layer)->updateWeights();
		}
	}
};

#endif