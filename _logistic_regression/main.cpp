#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    const int DATA_SIZE=0;
	const double LEARNING_RATE=0.1;
	const double REGULARIZED = 1e5;
	const int MAX_NUM_ITERATION = 1000;
	const int EPOCH_SIZE = 1e5;
	//add the constant
    const int DIMENTION = 100+1;
    double begin_time=0;
	double end_time=0;

	logistic_regression obj_lr;

	mat training_x = ones(DIMENTION,DATA_SIZE);
    mat training_y, parameters_w;
	training_x.load("training_x");	
    //add the constant;

	training_y.load("training_y");
	
	obj_lr.initLogisticRegression();
    obj_lr.begin(&begin_time);
    obj_lr.train();
	obj_lr.end(&end_time);
	
	return 0;
}
