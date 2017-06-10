#include "../header/KNN/KNN_Classifier.h"
#include "../header/Bayes/NaiveBayesClassifier.h"
#include "../header/NN/Network.h"
#include "../header/NN/NetworkTrainer.h"

int main() {
	KNN_Classifier cl;
	DataBase test;
	NaiveBayesClassifier test2;
	Network net;
	NetworkTrainer trainer;

#if RANDOM
	TrainMethod* method = new Random_BackPropagation();
#else
	TrainMethod* method = new BackPropagation();
#endif

	test.setPath("data/titanic.dat");
	test.setDiscretization();
	test2.setDataBase(test);
	test2.train();
	printf("Naive Bayes Accuracy : %f\n", test2.getAccuracy());
	double a = -1.87;
	double b = -0.228;
	double c = 0.521;
	test2.normal(&a,&b,&b);
	Passenger temp;
	temp.setClass(a);
	temp.setAge(b);
	temp.setSex(c);
	test2.discretize(temp);
	test2.classify(temp);
	
	std::vector<double> input;
	for (int i = 0; i < 10; i++){
		input.push_back(2);
	}

	trainer.getNetwork().addLayer(new HiddenLayer(3));
	trainer.getNetwork().addLayer(new HiddenLayer(4));
	trainer.getNetwork().addLayer(new HiddenLayer(10));
	trainer.setDataBase(test);
	trainer.setMethod(method);

	std::cout << "training network........." << std::endl;
	trainer.train();

	printf("Network Accuracy : %f\n", trainer.getNetwork().getAccuracy());

	if (temp.isSurvived())
		std::cout << "survived!" << std::endl;
	else
		std::cout << "died!" << std::endl;

	return 0;
}