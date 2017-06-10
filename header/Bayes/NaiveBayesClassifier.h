//
// Created by JoelChen on 2017/5/18.
//

#include "../Object/Passenger.h"
#include "../Database/DataBase.h"
#include "../UtilNode.h"
#ifndef NAIVEBAYES_NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYES_NAIVEBAYESCLASSIFIER_H

/*
*@Author : JoelChen
*@Time   : 2017/5/18
*@Description : NaiveBayesClassifier class implemented Naive Bayes Algorithm
*/
class NaiveBayesClassifier {
private:
	//data base
	DataBase database;

	//accuracy of classifier
	double   accuracy;			

	//true_probability_model extracted from sample set
	std::hash_map<bool, double> true_probability_model;	

	//attributes_probability_model extracted from sample set
	std::hash_map<bool,std::hash_map<std::string, std::hash_map<bool, double>>> attributes_probability_model;	

	/*
	*extract model from sample set
	*@return void
	*/
	void extractModel();

	/*
	*@param std::hash_map<bool, std::hash_map<std::string, std::hash_map<bool, int>>>& attributes_value_count
	*					hash map for counting all attributes's frequency
	*example attributes_value_count[true]["class"][true] means that the number of object with label is true 
	*and it is class attribute and survived
	*@return void
	*/
	void attributesCount(std::hash_map<bool, std::hash_map<std::string, std::hash_map<bool, int>>>& attributes_value_count);

	/**
	*caculate sample detectation accuracy
	*@return void
	*/
	void caculateAccuracy();

	/*
	*initialize classifier
	*@return void 
	*/
	void initialize();

public:
	NaiveBayesClassifier();

	explicit NaiveBayesClassifier(DataBase initialdatabase);

	~NaiveBayesClassifier();

	void setDataBase(DataBase initialdatabase);

	/*
	*train classifier on sample set and extract model
	*@return void
	*/
	void train();

	/*
	*classify inputObject and set its prediction to computed prediction
	*@param Passenger& inputObject
	*					inputtd Passenger object for classifying
	*@return void
	*/
	void classify(Passenger& inputObject);

	/*
	*normalize all attributes
	*@param a...
	*		value of Passenger object's attributes
	*@return void
	*/
	void normal(double* a, double* b, double* c);

	/*
	*discretize all attributes of inputobject
	*@param Passenger& inputObject
	*					inputtd Passenger object for classifying
	*@return void
	*/
	void discretize(Passenger& inputobject);

	double getAccuracy();
};


#endif //NAIVEBAYES_NAIVEBAYESCLASSIFIER_H
