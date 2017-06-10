#include "../../../header/NN/layer/Layer.h"

Layer::Layer(){
	this->pre_layer = NULL;
	this->next_layer = NULL;
	this->dimension = 0;
}

Layer::Layer(int dimension){
	this->pre_layer = NULL;
	this->next_layer = NULL;
	this->dimension = dimension;
}

void Layer::setPreLayer(Layer* pre_layer){
	this->pre_layer = pre_layer;
}

void Layer::setNextLayer(Layer* next_layer){
	this->next_layer = next_layer;
}

inline void Layer::setNextDelta(std::vector<double>& next_delta){
	this->next_delta = next_delta;
}

inline void Layer::setInput(std::vector<double>& input){
	this->input = input;
	this->input.push_back(1);
}

inline std::vector<Neuron>& Layer::getNuerons(){
	return this->neurons;
}

inline int Layer::getDimension(){
	return this->dimension;
}

void Layer::initialize(){
	try{
		if (!this->neurons.empty())
			this->neurons.clear();
		if (this->pre_layer != NULL){
			for (int i = 0; i < dimension; i++){
				Neuron temp((this->pre_layer->getDimension() + 1));
				neurons.push_back(temp);
			}
		}
		else{
			throw std::exception("Exception :pre layer is NULL");
		}
	}
	catch (const std::exception& e){
		std::cout << e.what() << std::endl;
	}
}

void Layer::caculateOutput(){
	if (!this->output.empty())
		this->output.clear();
	std::vector<Neuron>::iterator ite;
	for (ite = neurons.begin(); ite != neurons.end(); ite++){
		this->output.push_back((*ite).getOutput(this->input));
	}
}

void Layer::caculateDelta(){
	try{
		if (this->next_delta.empty())
			throw std::exception("Exception : next_delta set is empty");
		if (!this->delta.empty())
			this->delta.clear();
		int delta_size = this->dimension;
		size_t next_delta_size = this->next_delta.size();
		for (int i = 0; i < delta_size; i++){
			double delta_temp = 0.0f;
			double next_delta_sum = 0.0f;

			/*
			*caculate  coefficient of delta summed from the next_layer's delta plusing weights
			*cause this weight affects the next_layer's weight
			*
			* next_delta_sum = sigma(next_delta(j) * next_layer_weights(j i))
			*
			*/
			for (int j = 0; j < next_delta_size; j++){
				next_delta_sum += (this->next_delta[j] * (this->next_layer->getNuerons()[j].getWeights()[i]));
			}
			delta_temp = next_delta_sum * this->output[i] * (1.0f - this->output[i]);
			this->delta.push_back(delta_temp);
		}
	}
	catch (std::exception& e){
		std::cout << e.what() << std::endl;
	}
}

void Layer::forward(){

	/*
	*transfer the output to the next layer as input
	*output : layer(i) -> layer(i + 1) : input
	*/

	this->caculateOutput();
	try{
		if (this->next_layer == NULL)
			throw std::exception("Exception:next layer is null");
		this->next_layer->setInput(this->output);
	}
	catch (std::exception& e){
		std::cout << e.what() << std::endl;
	}
}

void Layer::backward(){

	/*
	*backward transfer the delta to the pre layer for caculating pre layer's delta
	*(caculating delta with delta rule)
	*layer(i - 1) <- layer(i) : delta
	*/

	this->caculateDelta();
	try{
		if (this->pre_layer == NULL)
			throw std::exception("Exception:pre layer is null");
		this->pre_layer->setNextDelta(this->delta);
	}
	catch (std::exception& e){
		std::cout << e.what() << std::endl;
	}
}

void Layer::updateWeights(){

	/*
	*for every layer , delta is shared by all neuron and update equaltion is
	*
	*weight(neuroni , indexj) =  weight(neuroni , indexj)   +    LearningRate     *         delta(neuroni)             *                        input(indexj)
	*              |                        |                         |                           |                                                  |
	*           weightIJ                 weightIJ                     n       sigma(next_delta(i) * next_weightIJ)£ªderivative(g(x))       derivative(O) / derivative(weightIJ)
	*/

	size_t neuron_number = this->neurons.size();
	size_t input_dimension = this->input.size();
	for (int i = 0; i < neuron_number; i++){
		for (int j = 0; j < input_dimension; j++){
			double weightIJ = this->neurons[i].getWeights()[j];
			double updatedWeight = weightIJ + LEARNING_RATE * this->delta[i] * this->input[j];
			this->neurons[i].getWeights()[j] = updatedWeight;
		}
	}
}

