//
// Created by JoelChen on 2017/5/18.
//

#include "../../header/Bayes/NaiveBayesClassifier.h"

NaiveBayesClassifier::NaiveBayesClassifier(){
	this->initialize();
}

NaiveBayesClassifier::NaiveBayesClassifier(DataBase initialdatabase){
	this->database = initialdatabase;
	this->initialize();
}

NaiveBayesClassifier::~NaiveBayesClassifier(){}

void NaiveBayesClassifier::initialize(){
	this->accuracy = 0.0f;
	this->true_probability_model[true] = 0.0f;
	this->true_probability_model[false] = 0.0f;

	this->attributes_probability_model[true]["class"][true] = 0.0f;
	this->attributes_probability_model[true]["class"][false] = 0.0f;

	this->attributes_probability_model[true]["age"][true] = 0.0f;
	this->attributes_probability_model[true]["age"][false] = 0.0f;

	this->attributes_probability_model[true]["sex"][true] = 0.0f;
	this->attributes_probability_model[true]["sex"][false] = 0.0f;

	this->attributes_probability_model[false]["class"][true] = 0.0f;
	this->attributes_probability_model[false]["class"][false] = 0.0f;

	this->attributes_probability_model[false]["age"][true] = 0.0f;
	this->attributes_probability_model[false]["age"][false] = 0.0f;

	this->attributes_probability_model[false]["sex"][true] = 0.00f;
	this->attributes_probability_model[false]["sex"][false] = 0.0f;
}

void NaiveBayesClassifier::setDataBase(DataBase initialdatabase){
	this->database = initialdatabase;
}

double NaiveBayesClassifier::getAccuracy(){
	return this->accuracy;
}

void NaiveBayesClassifier::normal(double* a, double* b, double* c){
	this->database.normal(a,b,c);
}

void NaiveBayesClassifier::discretize(Passenger& inputobject){
	this->database.discretization(inputobject);
}

void NaiveBayesClassifier::train(){
	this->extractModel();
	std::vector<Passenger>::iterator test_set_ite;
	for (test_set_ite = this->database.getTestSet().begin();
		test_set_ite != this->database.getTestSet().end();
		test_set_ite++){
		this->classify((*test_set_ite));
	}
	this->caculateAccuracy();
}

void NaiveBayesClassifier::extractModel(){
	int sample_set_size = this->database.getSampleSet().size();
	int true_number = this->database.getTrueCount()[true];
	int false_number = this->database.getTrueCount()[false];

	//map for counting all attributes's distribution in the sample set
	/*            
	*                             0  5/9   
	*                     class -        9
	*                             1  4/9
	*                             0  5/9
	*             true -  age   -         9
	*                             1  5/9
	*							  0
	*                     sex   -
	*                             0
	*isSurvived -         
	*             fasle .....
	*/            
	std::hash_map<bool,
				  std::hash_map<std::string, 
											std::hash_map<bool,int>
								>
	              > attributes_value_count;

	std::vector<std::string>::iterator attribute_ite;

	this->attributesCount(attributes_value_count);

	/*caculate true and false probability*/
	this->true_probability_model[true] = (double)((double)true_number / (double)sample_set_size);
	this->true_probability_model[false] = (double)((double)false_number / (double)sample_set_size);

	//caculate all probabilities of attributes' values 

	/*
	* p(x|c) = [c][attribute][true][number] / [c][number]
	*           |      |		|	 |		   |    |
	* example  true  class	  value  10       true   20
	*/
	for (attribute_ite = this->database.getAttributesSet().begin();
		attribute_ite != this->database.getAttributesSet().end();
		attribute_ite++){
		this->attributes_probability_model[true][(*attribute_ite)][true] = 
			                                                                (double)((double)attributes_value_count[true][(*attribute_ite)][true] /
																			(double)true_number);

		this->attributes_probability_model[true][(*attribute_ite)][false] = 
																			(double)((double)attributes_value_count[true][(*attribute_ite)][false] /
																			(double)true_number);

		this->attributes_probability_model[false][(*attribute_ite)][true] = 
																			(double)((double)attributes_value_count[false][(*attribute_ite)][true] / 
																			(double)false_number);

		this->attributes_probability_model[false][(*attribute_ite)][false] = 
																			(double)((double)attributes_value_count[false][(*attribute_ite)][false] / 
																			(double)false_number);
	}
}

void NaiveBayesClassifier::attributesCount(std::hash_map<bool, std::hash_map<std::string, std::hash_map<bool, int>>>& attributes_value_count){
	std::vector<Passenger>::iterator object_ite;
	std::vector<std::string>::iterator attribute_ite;

	//record numbers of all attributes in the true or fasle situation
	for (object_ite = this->database.getSampleSet().begin(); object_ite != this->database.getSampleSet().end(); object_ite++){
		for (attribute_ite = this->database.getAttributesSet().begin();
			attribute_ite != this->database.getAttributesSet().end();
			attribute_ite++){
			std::string temp = (std::string)(*attribute_ite);
			if (temp == "class"){
				attributes_value_count[(*object_ite).isSurvived()][(*attribute_ite)][(*object_ite).getD_Passenger().getClass()]++;
			}
			else if (temp == "age"){
				attributes_value_count[(*object_ite).isSurvived()][(*attribute_ite)][(*object_ite).getD_Passenger().getAge()]++;
			}
			else{
				attributes_value_count[(*object_ite).isSurvived()][(*attribute_ite)][(*object_ite).getD_Passenger().getSex()]++;
			}
		}
	}
}

void NaiveBayesClassifier::caculateAccuracy(){
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
	this->accuracy = (double)((double)counter / (double)size);
}

void NaiveBayesClassifier::classify(Passenger& inputObject){
	double survived_probability = 0.0f;
	double died_probability = 0.0f;
	double prediction = 0.0f;

	/* ge the true and false probability*/
	double true_probability = this->true_probability_model[true];
	double false_probability = this->true_probability_model[false];

	/* get the Pre-probability of all attributes */

	//class Pre-probability
	double class_true_probability = this->attributes_probability_model[true]["class"][inputObject.getD_Passenger().getClass()];
	double class_false_probability = this->attributes_probability_model[false]["class"][inputObject.getD_Passenger().getClass()];

	//age Pre-probability
	double age_true_probability = this->attributes_probability_model[true]["age"][inputObject.getD_Passenger().getAge()];
	double age_false_probability = this->attributes_probability_model[false]["age"][inputObject.getD_Passenger().getAge()];

	//gender Pre-probability
	double gender_true_probability = this->attributes_probability_model[true]["sex"][inputObject.getD_Passenger().getSex()];
	double gender_false_probability = this->attributes_probability_model[false]["sex"][inputObject.getD_Passenger().getSex()];

	//caculate bayes Post-probability for all label
	/*
	*
	*  p(c|x) = log2(p(c)) + Sigma(log2(p(x|c)))
	*
	*/
	survived_probability = log2(true_probability) + log2(class_true_probability) + log2(age_true_probability) + log2(gender_true_probability);
	died_probability = log2(false_probability) + log2(class_false_probability) + log2(age_false_probability) + log2(gender_false_probability);

	if (survived_probability >= died_probability){
		prediction = 1.0f;
	}
	else{
		prediction = -1.0f;
	}
	inputObject.setDetect(prediction);
}