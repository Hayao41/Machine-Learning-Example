#include "../Neuron.h"
#include "../../Parameters.h"

#ifndef LAYER_H
#define LAYER_H

/*
*@Author : JoelChen
*@Time   : 2017/5/25
*@Description : Network Layer Super Class
*/
class Layer{
protected:

	std::vector<Neuron> neurons;
	std::vector<double> input;
	std::vector<double> output;
	std::vector<double> delta;
	std::vector<double> next_delta;
	Layer* pre_layer;
	Layer* next_layer;
	int dimension;

	void caculateOutput();

public:
	Layer();

	Layer(int dimension);

	virtual ~Layer() = default;

	void setPreLayer(Layer* pre_layer);

	void setNextLayer(Layer* next_layer);

	inline void setNextDelta(std::vector<double>& next_delta);

	inline void setInput(std::vector<double>& input);

	inline std::vector<Neuron>& getNuerons();

	inline int getDimension();

	virtual void initialize();

	virtual void caculateDelta();

	virtual void forward();

	virtual void backward();

	void updateWeights();
};
#endif
