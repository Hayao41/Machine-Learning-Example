#include "TrainMethod.h"
#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

class BackPropagation : public TrainMethod{
private:

	/*
	*Standard Back Propagation
	*ervery iter sacns all of sample set
	*@param std::vector<Layer*>& layers
	*							 layers of network for training
	*@param std::vector<Passenger>& sample_set
	*							 inputed sample set for traning
	*
	*/
	void backpropagation(std::vector<Layer*>& layers, std::vector<Passenger>& sample_set){
		for (int i = 0; i < MAX_ITER; i++){
			double Loss = FLT_MAX;
			std::vector<Passenger>::iterator sample;
			std::vector<Passenger>::iterator sample_set_begin = sample_set.begin();
			std::vector<Passenger>::iterator sample_set_end = sample_set.end();

			for (sample = sample_set_begin; sample != sample_set_end; sample++){
				DataLayer* inputlayer = (DataLayer*)layers[0];
				OutputLayer* outputlayer = (OutputLayer*)layers.back();
				//set input to network
				inputlayer->setInput(sample->getVector());
				//set label to outputlayer
				outputlayer->setLabel(sample->getLabel());

				//three phase of bp
				this->forward_pass(layers);
				this->backword_pass(layers);
				this->updateWeights(layers);
				Loss = outputlayer->getLoss();
				if (Loss <= LOSS)
					break;
			}
			if (i == MAX_ITER - 1)
				printf("May the Loss don't convergent or with a too slow speed: %f\n", Loss);
			if (Loss <= LOSS)
				break;
		}
	}

public:
	BackPropagation() : TrainMethod(){}
	~BackPropagation(){}

	void train(std::vector<Layer*>& layers, std::vector<Passenger>& sample_set){
		this->backpropagation(layers, sample_set);
	}
};

#endif
