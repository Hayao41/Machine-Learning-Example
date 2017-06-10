#include <iostream>
#include <vector>
#include <cmath>
#include <exception>

#ifndef NEURON_H
#define NEURON_H

/*
*@Author : JoelChen
*@Time   : 2017/5/25
*@Description : Neurons element class
*/
class Neuron{
private:

	std::vector<double> weights;
	double output;
	int dimension;

	void initialize(){
		double iW = 1.0f / sqrt((double)dimension - 1);
		/*
		*initial all weight by random number in range [-1/sqrt(input_dimen),1/sqrt(input_dimen)]
		*/
		for (int i = 0; i < dimension; i++){
			this->weights.push_back((((double)(rand() % 100) + 1) / 100 * 2 * iW) - iW);
		}
	}

	void sigmoid(std::vector<double>& input){
		double sum = 0.0f;
		/*
		*Logistic Function
		*out = 1 / (1 - exp(-wx))
		*/
		for (int i = 0; i < dimension; i++){
			sum += (double)((double)this->weights[i] * (double)input[i]);
		}
		this->output = (double)1.0f / (double)(1.0f + exp(-sum));
	}

public:
	Neuron(){
		this->dimension = 0;
		this->output = FLT_MAX;
	}

	explicit Neuron(int initialdimension){
		this->dimension = initialdimension;
		this->initialize();
	}

	~Neuron(){}

	inline double getOutput(std::vector<double>& input){
		this->sigmoid(input);
		return this->output;
	}

	inline void updateWeights(std::vector<double>& initialweights){
		this->weights = initialweights;
	}

	inline void setDimension(int initialdimension){
		this->dimension = initialdimension;
		this->initialize();
	}

	inline std::vector<double>& getWeights(){
		return this->weights;
	}
};

#endif

