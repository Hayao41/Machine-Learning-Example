#include "Layer.h"

#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H

class OutputLayer : public Layer{
private:

	std::vector<double> label;

public:
	OutputLayer() : Layer(){};
	explicit OutputLayer(int dimension) : Layer(dimension){}
	~OutputLayer(){};

	/*
	*Override Layer class's caculate vitrual methd
	*/
	void caculateDelta(){
		try{
			if (this->pre_layer == NULL)
				throw std::exception("Exception : pre_layer is null");
			if (!this->delta.empty())
				this->delta.clear();
			int end = this->dimension;
			for (int i = 0; i < end; i++){
				double delta_temp = 0.0f;
				/*
				*caculate output layer's delta
				*deltak = sigma((Lk - Ok) * Ok * (1 - Ok))
				*/
				delta_temp = (this->label[i] - this->output[i]) * this->output[i] * (1.0f - this->output[i]);
				this->delta.push_back(delta_temp);
			}
		}
		catch (std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}

	inline void setLabelDimension(int label_dimension){
		this->dimension = label_dimension;
	}

	inline void setLabel(std::vector<double>& label){
		this->label = label;
	}

	inline const std::vector<double>& getOutput(){
		return this->output;
	}

	inline void forward(){
		this->caculateOutput();
	}


	double getLoss(){
		double loss = 0.0f;
		int end = this->dimension;
		/*
		*Square Loss
		*Sigma((labeli - outi)^2 / max(labeli,outi))
		*/
		for (int i = 0; i < end; i++){
			loss += pow(this->label[i] - this->output[i],2) / std::max(this->label[i], this->output[i]);
		}
		return loss;
	}
};

#endif

