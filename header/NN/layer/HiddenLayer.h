#include "Layer.h"

#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H
class HiddenLayer : public Layer{
public:
	HiddenLayer() : Layer(){};
	explicit HiddenLayer(int dimension) : Layer(dimension){};
	~HiddenLayer(){}

	/*
	*Override Layer class's caculate vitrual methd
	*/
	void caculateDelta(){
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
				*next_delta_sum = sigma(next_delta(j) * next_layer_weights(j i))
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
};

#endif

