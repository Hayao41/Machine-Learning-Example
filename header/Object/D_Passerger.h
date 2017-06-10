//
// Created by JoelChen on 2017/5/18.
//

#include <vector>

#ifndef NAIVEBAYES_D_PASSERGER_H
#define NAIVEBAYES_D_PASSERGER_H


class D_Passenger {
private:
    bool boat_class;
    bool age;
    bool sex;

public:
    D_Passenger(){}

    D_Passenger(bool initialClass,
                bool initialAge,
                bool initialSex){
        this->boat_class = initialClass;
        this->age = initialAge;
        this->sex = initialSex;
    }

    void setClass(bool initialClass){
        this->boat_class = initialClass;
    }

    void setAge(bool initialAge){
        this->age = initialAge;
    }

    void setSex(bool initialSex){
        this->sex = initialSex;
    }

    bool getClass(){
        return this->boat_class;
    }

    bool getAge(){
        return this->age;
    }

    bool getSex(){
        return this->sex;
    }
};

#endif //NAIVEBAYES_D_PASSERGER_H
