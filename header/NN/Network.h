#include "layer/HiddenLayer.h"
#include "layer/OutputLayer.h"
#include "layer/DataLayer.h"
#include "../Database/DataBase.h"

#ifndef NETWORK_H
#define NETWORK_H
class Network{
private:

	std::vector<Layer*> layers;
	double accuracy;

public:

	Network(){
		this->accuracy = 0.0f;
	};

	explicit Network(Layer* datalayer){
		this->layers.push_back(datalayer);
		this->accuracy = 0.0f;
	};

	~Network(){
		size_t size = this->layers.size();
		for(int i = 0;i<size;i++){
			delete((Layer*)this->layers[i]);
			this->layers[i] = NULL;
		}
		this->layers.clear();
	};

	void addLayer(Layer* layer){
		if (!this->layers.empty()){
			(this->layers.back())->setNextLayer(layer);
			layer->setPreLayer(this->layers.back());
		}
		this->layers.push_back(layer);
	}

	inline void setDataLayer(Layer* datalayer){
		if (this->layers.empty()){
			this->layers.push_back(datalayer);
		}
		else{
			Layer* first = *this->layers.begin();
			datalayer->setNextLayer(first);
			first->setPreLayer(datalayer);
			this->layers.insert(layers.begin(),datalayer);
		}
	};

	inline void setOutputLayer(Layer* outputlayer){
		Layer* end = this->layers.back();
		end->setNextLayer(outputlayer);
		outputlayer->setPreLayer(end);
		outputlayer->initialize();
		this->layers.push_back(outputlayer);
	}

	inline void setAcurracy(double accuracy){
		this->accuracy = accuracy;
	}

	inline double getAccuracy(){
		return this->accuracy;
	}

	inline std::vector<Layer*>& getLayers(){
		return this->layers;
	}

	void initializeHiddenLayers(){
		std::vector<Layer*>::iterator hiddenlayer;
		std::vector<Layer*>::iterator begin = layers.begin() + 1;
		std::vector<Layer*>::iterator end = layers.end() - 1;
		for (hiddenlayer = begin; hiddenlayer != end; hiddenlayer++){
			(*hiddenlayer)->initialize();
		}
	}
};
#endif

