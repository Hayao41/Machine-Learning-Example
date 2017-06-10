//
// Created by JoelChen on 2017/5/11.
//

#include "../../header/KNN/KNN_Classifier.h"

KNN_Classifier::KNN_Classifier(std::string dataBasePath,
							   int initialK) {
	this->dataBase.setPath(dataBasePath);
	this->nearestK = initialK;
	accuracy_rate = 0;
}

KNN_Classifier::KNN_Classifier(){
	this->dataBase = DataBase();
	this->nearestK = 1;
	this->accuracy_rate = 0;
}

void KNN_Classifier::setDataBase(std::string dataBasePath){
	this->dataBase.setPath(dataBasePath);
}

void KNN_Classifier::setK(int initialK){
	this->nearestK = initialK;
}


double KNN_Classifier::train(){
	std::vector<Passenger>::iterator test_iterrator;
	std::vector<Passenger>& set = this->dataBase.getTestSet();
	for (test_iterrator = set.begin();
		test_iterrator != set.end();
		test_iterrator++) {
		if (this->classify((*test_iterrator)))
			(*test_iterrator).setDetect(1.0f);
		else
			(*test_iterrator).setDetect(-1.0f);
	}
	this->caulate_accuracy();
	return this->accuracy_rate;
}

bool KNN_Classifier::classify(Passenger& input){
	std::vector<Passenger> Knear;
	std::priority_queue<Passenger,std::vector<Passenger>,Passenger_Dist_Compare> queue;
	std::vector<Passenger>::iterator sample_ite;
	std::vector<Passenger> set = this->dataBase.getSampleSet();
	for (sample_ite = set.begin();
		sample_ite != set.end();
		sample_ite++){
		this->caculate_dist((*sample_ite), input);
		queue.push((*sample_ite));
	}
	for (int i = 0; i < this->nearestK; i++){
		Knear.push_back(queue.top());
		queue.pop();
	}
	return predict(Knear);
}

bool KNN_Classifier::predict(std::vector<Passenger>& Knear_list){
	int survived = 0;
	int died = 0;
	std::vector<Passenger>::iterator ite;
	for (ite = Knear_list.begin();
		ite != Knear_list.end();
		ite++){
		Passenger temp = (Passenger)(*ite);
		if (temp.isSurvived())
			survived++;
		else
			died++;
	}
	if (survived >= died)
		return true;
	else
		return false;
}

void KNN_Classifier::caulate_accuracy(){
	int size = this->dataBase.getTestSet().size();
	int counter = 0;
	std::vector<Passenger>::iterator ite;
	std::vector<Passenger> set = this->dataBase.getTestSet();
	for (ite = set.begin();
		ite != set.end();
		ite++){
		Passenger temp = (Passenger)(*ite);
		if (temp.isRight())
			counter++;
	}
	this->accuracy_rate = (double)((double)counter / (double)size);
}

void KNN_Classifier::caculate_dist(Passenger& sample, Passenger& input){
	double dist = 0;
	dist += pow((sample.getClass() - input.getClass()), 2) +
		pow((sample.getAge() - input.getAge()), 2) +
		pow((sample.getSex() - input.getSex()), 2);
	sample.setDistance(dist);
}

void KNN_Classifier::normal(double* a, double* b, double* c){
	this->dataBase.normal(a, b, c);
}