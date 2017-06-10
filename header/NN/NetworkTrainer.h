#include "BackPropagation.h"
#include "Random_BackPropagation.h"
#include "OnlineTrainer.h"
#include "../DataBase/DataBase.h"

#ifndef NETWORKTRAINER_H
#define NETWORKTRAINER_H

class NetworkTrainer{

private:
	Network nn;
	DataBase database;
	TrainMethod* trainmethod;

	void pre_work(){
		int input_dimension = 0;
		int label_dimension = 0;
		DataLayer* datalayer = new DataLayer();
		OutputLayer* outputlayer = new OutputLayer();
		input_dimension = this->database.getSampleSet().begin()->getVector().size();
		label_dimension = this->database.getSampleSet().begin()->getLabel().size();
		datalayer->setInputDimension(input_dimension);
		outputlayer->setLabelDimension(label_dimension);
		this->nn.setDataLayer(datalayer);
		this->nn.setOutputLayer(outputlayer);
		this->nn.initializeHiddenLayers();
	}

	double caculateAccuracy(){
		double accuracy = 0.0f;
		int size = this->database.getTestSet().size();
		int counter = 0;
		std::vector<Passenger>::iterator ite;
		std::vector<Passenger> set = this->database.getTestSet();
		for (ite = set.begin();
			ite != set.end();
			ite++){
			Passenger temp = (Passenger)(*ite);
			if (temp.isRight())
				counter++;
		}
		accuracy = (double)((double)counter / (double)size);
		return accuracy;
	}

public:

	NetworkTrainer(){
		trainmethod = new BackPropagation();
	}

	explicit NetworkTrainer(TrainMethod* trainmethod){
		this->trainmethod = trainmethod;
	}

	~NetworkTrainer(){
		this->nn.~Network();
		delete(trainmethod);
		trainmethod = NULL;
	}

	inline void setNetwork(Network& nn){
		this->nn = nn;
	}

	inline void setMethod(TrainMethod* trainmethod){
		if (this->trainmethod != NULL){
			delete(this->trainmethod);
			this->trainmethod = NULL;
		}
		this->trainmethod = trainmethod;
	}

	inline void setDataBase(DataBase& database){
		this->database = database;
	}

	inline void train(){
		double accuracy = 0.0f;
		this->pre_work();
		this->trainmethod->train(nn.getLayers(),database.getSampleSet());
		std::vector<Passenger>::iterator test;
		std::vector<Passenger>::iterator test_set_begin = this->database.getTestSet().begin();
		std::vector<Passenger>::iterator test_set_end = this->database.getTestSet().end();
		for (test = test_set_begin; test != test_set_end; test++){
			double prediction = this->classify(*test);
			if (prediction > 0.5f)
				prediction = 1.0f;
			else
				prediction = -1.0f;
			test->setDetect(prediction);
		}
		accuracy = this->caculateAccuracy();
		this->nn.setAcurracy(accuracy);
	}

	inline Network& getNetwork(){
		return this->nn;
	}

	double classify(Passenger& sample){
		double prediction = 0.0f;
		std::vector<Layer*>::iterator layer;
		std::vector<Layer*>::iterator layer_begin = nn.getLayers().begin();
		std::vector<Layer*>::iterator layer_end = nn.getLayers().end();
		DataLayer* inputlayer = (DataLayer*)nn.getLayers()[0];
		OutputLayer* outputlayer = (OutputLayer*)nn.getLayers().back();
		inputlayer->setInput(sample.getVector());
		outputlayer->setLabel(sample.getLabel());
		for (layer = layer_begin; layer != layer_end; layer++){
			(*layer)->forward();
		}
		prediction = outputlayer->getOutput()[0];
		return prediction;
	}
};

#endif
