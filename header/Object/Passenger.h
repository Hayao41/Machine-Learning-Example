//
// Created by JoelChen on 2017/5/11.
//

#ifndef KNN_PASSENGER_H
#define KNN_PASSENGER_H

#include <cfloat>
#include "D_Passerger.h"

class Passenger {
private:
    double boat_class;
    double age;
    double sex;
    double survived;
	double prediction;
    
    D_Passenger d_passenger;
    
public:

	double distance;

	Passenger(){
        this->prediction = 0;
        this->distance = FLT_MAX;
    };

    explicit Passenger(double initialClass,
					   double initialAge,
					   double initialSex,
					   double initialSurvived){
        this->boat_class = initialClass;
        this->age = initialAge;
        this->sex = initialSex;
        this->survived = initialSurvived;
		this->prediction = 0;
        this->distance = FLT_MAX;
    }

    void setClass(double initialClass){
        this->boat_class = initialClass;
    }

    void setAge(double initialAge){
        this->age = initialAge;
    }

    void setSex(double initialSex){
        this->sex = initialSex;
    }

    void setDetect(double dect){
		this->prediction = dect;
    }

    void setDistance(double dist){
        this->distance = dist;
    }

    void setD_Passenger(D_Passenger initialD_Passenger){
        this->d_passenger = initialD_Passenger;
    }

    double getClass(){
        return this->boat_class;
    }

    double getAge(){
        return this->age;
    }

    double getSex(){
        return this->sex;
    }

	bool isSurvived(){
		return this->survived == 1.0;
	}

	bool isRight(){
		return this->prediction == this->survived;
	}

	std::vector<double> getVector(){
		std::vector<double> temp;
		temp.push_back(boat_class);
		temp.push_back(age);
		temp.push_back(sex);
		return temp;
	}

	std::vector<double> getLabel(){
		std::vector<double> temp;
		if (survived == 1.0f)
			temp.push_back(1.0f);
		else
			temp.push_back(0.0f);
		return temp;
	}

    D_Passenger& getD_Passenger(){
        return this->d_passenger;
    }
};

typedef struct Passenger_Dist_Compare{
	bool operator()(const Passenger& lhs, const Passenger& rhs) const{
		return lhs.distance > rhs.distance;
	}
}Passenger_Dist_Compare;


#endif //KNN_PASSENGER_H
