#include "Layer.h"

#ifndef DATALAYER_H
#define DATALAYER_H

class DataLayer : public Layer{
public:

	DataLayer() : Layer(){
		this->dimension = 1;
		this->initialize();
	};

	DataLayer(int dimension) : Layer(dimension){
		this->initialize();
	};

	~DataLayer(){};

	inline void setInputDimension(int input_dimension){
		this->dimension = input_dimension;
		this->initialize();
	}

	void initialize(){
		try{
			if (!neurons.empty()){
				neurons.clear();
			}
			if (dimension != 0){
				for (int i = 0; i < dimension; i++){
					Neuron temp(dimension + 1);
					neurons.push_back(temp);
				}
			}
			else{
				throw std::exception("Exception : dimension is 0!");
			}
		}
		catch (const std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}

	void backward(){
		this->caculateDelta();
	}
};

#endif