//
// Created by JoelChen on 2017/5/11.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <hash_map>
#include "../Object/Passenger.h"
#include "../UtilNode.h"
#include "../Parameters.h"
#ifndef KNN_DATABASE_H
#define KNN_DATABASE_H

/*
*@Author : JoelChen
*@Time   : 2017/5/11
*@Description : data base for data storing and pre-operation to support the classifier
*/
class DataBase {
private:
	double class_boundary[2];
	double age_boundary[2];
	double sex_boundary[2];
	double class_length;
	double age_length;
	double sex_length;
	double class_threshold;
	double age_threshold;
	double sex_threshold;
        std::string path;
        std::vector<UtilNode> class_set;
        std::vector<UtilNode> age_set;
        std::vector<UtilNode> sex_set;
        std::vector<Passenger> sample_set;
        std::vector<Passenger> test_set;
	std::vector<std::string> attributes_set;
	std::hash_map<bool,int> true_cout;

	
	/*
	*find the best theshold which can get the best gain in the sample set
	*@param  set  the set for caculate thrshold
	*@return double
	*the soft threshold point which can get the best gain
	*/
	double findThreshold(std::vector<UtilNode>& set);

	/*
	*caulate the information entropie on the subset which split by the discontinuity point
	*@param  start  
	*			start index of subset
	*@param  end    
	*			end index of subset
	*@param  set    
	*			set for caculating 
	*@return double
	*			entropie caculatted by the subset from start to end
	*/
	double getEntropie(int start, int end ,std::vector<UtilNode>& set);

public:
	explicit DataBase(std::string initialPath);

	DataBase();

	/*
	*set the data set file path into data base for traning
	*@param initialPath 
	*				data set file path
	*@return void
	*/
	void setPath(std::string initialPath);

	/* build data base bsaed on the input data set*/
	void buildWithPath();

	void buildTestDataBase();

	/*discretization the input data set in the data base*/
	void setDiscretization();

	/*discretization the input object*/
	void discretization(Passenger& inputobject);

	/*
	*normalize all attributes to range[0,1]
	*@param a..   
	*		attributes of passenger object
	*@return void
	*/
	void normal(double* a, double* b, double* c);

	std::vector<Passenger>& getSampleSet();

	std::vector<Passenger>& getTestSet();

	std::hash_map<bool, int>& getTrueCount();

	std::vector<std::string>& getAttributesSet();
};

#endif //KNN_DATABASE_H
