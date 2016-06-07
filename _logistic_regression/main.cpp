#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    const int DATA_SIZE=32561;
	const double LEARNING_RATE=1e-3;
	const double REGULARIZED = 1e-5;
	const int MAX_NUM_ITERATION = 1000;
	const int EPOCH_SIZE = 1e3;
	//add the constant
    const int DIMENTION = 123+1;
    double begin_time=0;
	double end_time=0;
    const bool SPARSE = true;
    const bool DENSE = false;
    //traning file
    char* training_x = "data.txt";
    char* training_y = "label.txt";
    
	logistic_regression obj_lr(DATA_SZIE,
                                  LEARNING_RATE,
                                  REGULARIZED,
                                  MAX_NUM_ITERATION,
                                  EPOCH_SIZE,
                                  DIMENTION);
    mat training_x, training_y, parameters_w;
    if(SPARSE)//sparse dataset
    {
        training_x = zeros(DIMENTION,DATA_SIZE);
        training_x.row(0).fill(1);
    }
    else//dense dataset 
        training_x = ones(DIMENTION,DATA_SIZE);
    	training_x.load(training_x);	
    //add the constant;

	training_y.load(training_y);
	
	obj_lr.begin(&begin_time);
    obj_lr.train();
	obj_lr.end(&end_time);
	return 0;
}
