#include <queue>
#include <math.h>
#include "../../header/Database/DataBase.h"
#ifndef KNN_KNN_CLASSFIER_H
#define KNN_KNN_CLASSFIER_H



/**
*@Author :  JoelChen
*@Time   :	2017/5/11
*This class is the KNN classifiler which implements the KNN algorithm.
*The KNN's train approch is that classifier scans the sample set and caculates all disatance between 
*sample and input.Secondlly chooses the K most similar sample to determine the detectation of input
*/
class KNN_Classifier {
private:
    DataBase dataBase;						//input database which is contains sample set and test set
    int nearestK;							//super parameters of KNN k is the most similar object in the sample set
    double accuracy_rate;					//accuracy rate of KNN


	/**
	*caculate the distance between sample and input object
	*@para Passenger& 		
	*				sample object
	*@para Passenger& 		
	*				input object
	*@return void
	*/
	void caculate_dist(Passenger& sample, Passenger& input);

	/**
	*caculate sample detectation accuracy
	*@return void
	*/
	void caulate_accuracy();

	/**
	*predict by the Knear sample object
	*@return bool
	*/
	bool predict(std::vector<Passenger>& Knear_list);

public:

	/**
	*explicit contructor
	*/
	explicit KNN_Classifier(std::string dataBasePath,
							int initialK);
	/**
	*implicit contructor
	*/
	KNN_Classifier();

	/**
	*set the data base file path into classifier
	*@para std::string  
	*				database file path
	*@return void
	*/
	void setDataBase(std::string dataBasePath);

	/**
	*set the super parameter K
	*@para int 
	*		super parameter K
	*@return void
	*/
	void setK(int initialK);

	/**
	*normalize input object's attributes
	*@return void
	*/
	void normal(double* a, double* b, double* c);

	/**
	*train the KNN based on input data base
	*@return double 
	*			train accuracy
	*/
	double train();

	/**
	*classify the input object
	*@para Passenger& 
	*				input object waitting for to be calssified
	*/
	bool classify(Passenger& input);
};

#endif //KNN_KNN_CLASSFIER_H
