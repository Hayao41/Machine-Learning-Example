//
// Created by JoelChen on 2017/5/11.
//

#include "../../header/Database/DataBase.h"

DataBase::DataBase(){
	this->path = "";
}

DataBase::DataBase(std::string initialPath){
	this->true_cout[true] = 0;
	this->true_cout[false] = 0;
	this->path = initialPath;
	if (initialPath == "test")
		this->buildTestDataBase();
	else
		this->buildWithPath();
}

void DataBase::buildTestDataBase() {
		/* sample_set for testing*/
		this->sample_set.push_back(Passenger(-1.87, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(-0.923, -0.228, -1.92, 1.0));
		this->sample_set.push_back(Passenger(-0.923, -0.228, -1.92, 1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, 0.521, 1.0));
		this->sample_set.push_back(Passenger(0.0214, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.0214, -0.228, -1.92, -1.0));
		this->sample_set.push_back(Passenger(0.0214, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(-1.87, 4.38, 0.521, 1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, 0.521, 1.0));
		this->sample_set.push_back(Passenger(-1.87, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.0214, -0.228, -1.92, -1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.0214, -0.228, 0.521, 1.0));
		this->sample_set.push_back(Passenger(0.0214, 4.38, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, -1.92, 1.0));
		this->sample_set.push_back(Passenger(-0.923, -0.228, -1.92, 1.0));
		this->sample_set.push_back(Passenger(-0.923, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.0214, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, 0.521, -1.0));
		this->sample_set.push_back(Passenger(-1.87, -0.228, -1.92, 1.0));
		this->sample_set.push_back(Passenger(-0.923, -0.228, -1.92, 1.0));
		this->sample_set.push_back(Passenger(0.965, -0.228, 0.521, 1.0));

		/* test set for testing */
		this->test_set.push_back(Passenger(-1.87, -0.228, 0.521, -1.0));
		this->test_set.push_back(Passenger(-0.923, -0.228, -1.92, 1.0));
		this->test_set.push_back(Passenger(-0.923, -0.228, -1.92, 1.0));
		this->test_set.push_back(Passenger(0.965, -0.228, 0.521, 1.0));
		this->test_set.push_back(Passenger(0.0214, -0.228, 0.521, -1.0));
		this->test_set.push_back(Passenger(0.965, -0.228, 0.521, -1.0));
		this->test_set.push_back(Passenger(0.0214, -0.228, -1.92, -1.0));
		this->test_set.push_back(Passenger(0.0214, -0.228, 0.521, -1.0));
		this->test_set.push_back(Passenger(-1.87, 4.38, 0.521, 1.0));
		this->test_set.push_back(Passenger(0.965, -0.228, 0.521, 1.0));
		this->test_set.push_back(Passenger(-1.87, -0.228, 0.521, -1.0));
		this->test_set.push_back(Passenger(0.0214, -0.228, -1.92, -1.0));
		this->test_set.push_back(Passenger(0.965, -0.228, 0.521, -1.0));
		this->test_set.push_back(Passenger(0.0214, -0.228, 0.521, 1.0));
		this->test_set.push_back(Passenger(0.0214, 4.38, 0.521, -1.0));
		this->test_set.push_back(Passenger(0.965, -0.228, -1.92, 1.0));
		this->test_set.push_back(Passenger(-0.923, -0.228, -1.92, 1.0));
		this->test_set.push_back(Passenger(-0.923, -0.228, 0.521, -1.0));

		this->setDiscretization();
}

void DataBase::buildWithPath(){
	std::ifstream fin;
	std::string temp;
	int sample_num = 0;
	int sample_end = 0;
	int counter = 0;
	double left_bundary = 0;
	double right_bundary = 0;

	//open file stream
	fin.open(this->path);
	if (!fin){
		std::cout << " Error opening " << this->path << " for input " << std::endl;
		this->buildTestDataBase();
		return;
	}

	//split the file steam and create Passenger object to add into the database dataset
	while (std::getline(fin, temp)){

		//label split for attribute
		if (temp.find("@") != std::string::npos){
			if (temp.find("line number") != std::string::npos){
				std::size_t mark = temp.find_last_of(" ");
				std::string num(temp.substr(mark + 1, temp.length()-1));
				sample_num = (int)std::atoi(num.c_str());
				sample_end = (int)(SPLIT * (double)sample_num);
			}
			else if (temp.find("real") != std::string::npos){
				std::string temp2 = temp;
				std::size_t a = temp.find_first_of("[") + 1;
				std::size_t b = temp.find_first_of("]");
				temp = temp.substr(a,b);
				std::size_t mark = temp.find_first_of(",");
				left_bundary = std::atof(temp.substr(0,mark).c_str());
				right_bundary = std::atof(temp.substr(mark + 1, temp.length()).c_str());
				double length = right_bundary - left_bundary;

				if (temp2.find("attribute Class real") != std::string::npos){
					this->class_boundary[0] = left_bundary;
					this->class_boundary[1] = right_bundary;
					this->class_length = length;
					this->attributes_set.push_back(std::string("class"));
				}

				if (temp2.find("attribute Age real") != std::string::npos){
					this->age_boundary[0] = left_bundary;
					this->age_boundary[1] = right_bundary;
					this->age_length = length;
					this->attributes_set.push_back(std::string("age"));
				}

				if (temp2.find("attribute Sex real") != std::string::npos){
					this->sex_boundary[0] = left_bundary;
					this->sex_boundary[1] = right_bundary;
					this->sex_length = length;
					this->attributes_set.push_back(std::string("sex"));
				}
			}
		}

		//data split for creating Passenger object
		else{
			double b_class = 0;
			double age = 0;
			double sex = 0;
			double survived = 0;
			std::string tokens[4];

			for (int i = 0; i < 4; i++){
				std::size_t mark = temp.find_first_of(',');
				tokens[i] = temp.substr(0, mark);
				temp = temp.substr(mark + 1, temp.length());
			}

			b_class = std::atof(tokens[0].c_str());
			age = std::atof(tokens[1].c_str());
			sex = std::atof(tokens[2].c_str());
			survived = std::atof(tokens[3].c_str());
			this->normal(&b_class,&age,&sex);
			

			if (counter < sample_end){

				//record the number of survived and died
				this->true_cout[(survived == 1.0f)] ++;

				//add objects to sample set
				this->sample_set.push_back(Passenger(b_class,
													 age, 
													 sex, 
													 survived));

				//create util nodes for discretization
				this->class_set.push_back(UtilNode(b_class,survived));
				this->age_set.push_back(UtilNode(age,survived));
				this->sex_set.push_back(UtilNode(sex,survived));


				counter++;
			}
			else{

				//add objects to test set
				this->test_set.push_back(Passenger(b_class,
												   age,
												   sex,
												   survived));
			}
		}
	}
	fin.close();
}

void DataBase::normal(double* a, double* b, double* c){

	/*x - lower boundary / range*/
	*a = (double)((double)((*a) - this->class_boundary[0])	/ (double)this->class_length);

	*b = (double)((double)((*b) - this->age_boundary[0]) / (double)this->age_length);

	*c = (double)((double)((*c) - this->sex_boundary[0]) / (double)this->sex_length);
}

void DataBase::setPath(std::string initialPath){
	this->path = initialPath;
	if (initialPath == "test")
		this->buildTestDataBase();
	else
		this->buildWithPath();
}

std::vector<Passenger>& DataBase::getSampleSet(){
	return this->sample_set;
}

std::vector<Passenger>& DataBase::getTestSet(){
	return this->test_set;
}

std::hash_map<bool, int>& DataBase::getTrueCount(){
	return this->true_cout;
}
std::vector<std::string>& DataBase::getAttributesSet(){
	return this->attributes_set;
}

void DataBase::setDiscretization() {

	/* find all attributes' threshold for discretization*/
	this->class_threshold = this->findThreshold(this->class_set);
	this->age_threshold = this->findThreshold(this->age_set);
	this->sex_threshold = this->findThreshold(this->sex_set);

	/* discretize all onjects in the sample and test set */
	std::vector<Passenger>::iterator ite;
	for(ite = this->sample_set.begin();ite != this->sample_set.end();ite++){
		this->discretization(*ite);
	}
	for(ite = this->test_set.begin();ite != this->test_set.end();ite++){
		this->discretization(*ite);
	}
}

void DataBase::discretization(Passenger& inputobject) {

	//threshold operator
	/*
	*               0   if x <= threshold
	* delta(x)  = 
	*               1   if x >  thrshold
	*/
	inputobject.getD_Passenger().setClass(inputobject.getClass() > this->class_threshold);
	inputobject.getD_Passenger().setAge(inputobject.getAge() > this->age_threshold);
	inputobject.getD_Passenger().setSex(inputobject.getSex() > this->sex_threshold);
}

double DataBase::findThreshold(std::vector<UtilNode>& set) {
	double left_entropie = 0.0f;
	double right_entropie = 0.0f;
	UtilNode goal_node;
	std::vector<int> index;
	std::priority_queue<UtilNode, 
						std::vector<UtilNode>, 
						Set_Attributes2_Compare> 
						entropie_queue;

	int end = set.size() - 1;
	std::vector<int>::iterator ite;

	std::sort(set.begin(),
			  set.end(),
			  Set_Attributes1_Compare());


	/* record all discontinuity points' index into the index vector */
	for (int i = 0; i < end; i++){
		if (set[i].attribute_1 != set[i + 1].attribute_1)
			index.push_back(i);
	}
	if (set[end - 1].attribute_1 != set[end].attribute_1)
		index.push_back(end);

	/*caculate all discontinuity points' entropies for finding the best point to be the threshold*/
	for (ite = index.begin(); ite != index.end(); ite++){
		UtilNode temp(set[*ite].attribute_1,0);
		left_entropie = this->getEntropie(0, (*ite), set);
		right_entropie = this->getEntropie((*ite) + 1, end, set);
		temp.setAttribute_2(left_entropie + right_entropie);

		//push into the min heap
		entropie_queue.push(temp);
	}

	//get the lowest entropie point cause it can for getting a best gain
	goal_node = (UtilNode)entropie_queue.top();
	return goal_node.attribute_1;
}

double DataBase::getEntropie(int start, int end, std::vector<UtilNode>& set){
	double entropie = 0.0f;					//subset information entropie
	double coefficient = 0.0f;				//the coefficient of subset information entropie
	double true_probability = 0.0f;			//the probability of to be true
	double false_probability = 0.0f;		//the probability of to be false
	int total = set.size();					//the length of set
	int numbers = end - start + 1;			//length of subset
	std::hash_map<double, int> trueCount;	//map for true counting
	trueCount[1.0] = 0;
	trueCount[-1.0] = 0;

	//caculate the coefficient
	/*  subset length 
	*devide -
	*   set length
	*/
	coefficient = (double)((double)numbers / (double)total);

	/*count number of true and false objects in the subset*/
	for (int i = start; i <= end; i++){
		trueCount[set[i].attribute_2]++;
	}

	/* caculate the true_probability and false_probability*/
	true_probability = (double)((double)trueCount[1.0] / (double)numbers);
	false_probability = (double)((double)trueCount[-1.0] / (double)numbers);

	//caculate the subset information entropie
	/*
	* - c * ( (tp * log2(tp)) + (fp * log2(fp)) )
	*/
	double true_entropie = true_probability * log2(true_probability);
	double false_entropie = false_probability * log2(false_probability);
	entropie = -(coefficient * ((true_probability * log2(true_probability)) + (false_probability * log2(false_probability))));

	return entropie;
}

