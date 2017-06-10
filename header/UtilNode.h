//
// Created by JoelChen on 2017/5/23.
//

#ifndef NAIVEBAYES_UTILNODE_H
#define NAIVEBAYES_UTILNODE_H

class UtilNode {   
public:
	double attribute_1;
	double attribute_2;

    UtilNode(){}

    explicit UtilNode(  double initialAttribute1,
						double initialAttribute2){
		this->attribute_1 = initialAttribute1;
		this->attribute_2 = initialAttribute2;
    }

	void setAttribute(double initialAttribute1){
		this->attribute_1 = initialAttribute1;
    }

	void setAttribute_2(double initialAttribute2){
		this->attribute_2 = initialAttribute2;
    }
};

struct Set_Attributes1_Compare{
	bool operator()(const UtilNode& lhs, const UtilNode& rhs) const{
		return lhs.attribute_1 < rhs.attribute_1;
	}
};

struct Set_Attributes2_Compare{
	bool operator()(const UtilNode& lhs, const UtilNode& rhs) const{
		return lhs.attribute_2 > rhs.attribute_2;
	}
};



#endif //NAIVEBAYES_UTILNODE_H
