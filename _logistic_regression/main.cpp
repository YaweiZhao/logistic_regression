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
	
	double begin_time=0;
	double end_time=0;

	logistic_regression obj_lr;

	mat training_x, training_y, parameters_w;
	training_x.load("training_x");	
	training_y.load("training_y");
	
	obj_lr.begin();
	obj_lr.initLogisticRegression();
    obj_lr.train();
	obj_lr.end();
		
		
		
		
	return 0;
}
