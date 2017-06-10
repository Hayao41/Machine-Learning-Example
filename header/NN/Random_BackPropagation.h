#include "TrainMethod.h"

#ifndef RANDOM_BACKPROPAGATION_H
#define RANDOM_BACKPROPAGATION_H

class Random_BackPropagation : public TrainMethod{
private:

	/*
	*Random Back Propagation
	*ervery iter does not sacn all of sample set but scan with a tride
	*@param std::vector<Layer*>& layers
	*							 layers of network for training
	*@param std::vector<Passenger>& sample_set
	*							 inputed sample set for traning
	*
	*/
	void random_backpropagation(std::vector<Layer*>& layers, std::vector<Passenger>& sample_set){
		for (int i = 0; i < MAX_ITER; i++){
			double Loss = FLT_MAX;
			std::vector<Passenger>::iterator sample;
			std::vector<Passenger>::iterator sample_set_begin = sample_set.begin();
			std::vector<Passenger>::iterator sample_set_end = sample_set.end();

			for (sample = sample_set_begin; sample <= sample_set_end; sample += SAMPLE_STRIDE){
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
	Random_BackPropagation() : TrainMethod(){}
	~Random_BackPropagation(){}

	void train(std::vector<Layer*>& layers, std::vector<Passenger>& sample_set){
		this->random_backpropagation(layers, sample_set);
	}
};

#endif