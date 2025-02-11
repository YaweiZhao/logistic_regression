#include <iostream>
#include <armadillo>
#include "logistic_regression.hpp"

using namespace std;
using namespace arma;

int main()
{
    const int DATA_SIZE=32000;
	const double LEARNING_RATE=1e-3;
	const double REGULARIZED = 1e-5;/*regularization*/
	const int MAX_NUM_ITERATION = 1000;
	const int EPOCH_SIZE = 32000;
	//add the constant
    const int DIMENTION = 123+1;
    const double GAMMA = 0.99;/*momentum*/
    time_t begin_time=0;
	time_t end_time=0;
    const bool SPARSE = true;
    const bool DENSE = false;
    //traning file
    char* fn_x = "data.txt";
    char* fn_y = "label.txt";
    
	logistic_regression obj_lr(DATA_SIZE,
                                  LEARNING_RATE,
                                  REGULARIZED,
                                  MAX_NUM_ITERATION,
                                  EPOCH_SIZE,
                                  DIMENTION,
                                  GAMMA);
    if(SPARSE)//sparse dataset
    {
	sp_mat x_mat;
        x_mat.load(fn_x,arma::coord_ascii);
	obj_lr.training_x = x_mat.t();
        obj_lr.training_x.row(DIMENTION-1).fill(1);
    }
    else//dense dataset 
    {   //obj_lr.training_x = ones(DIMENTION,DATA_SIZE);
    	//obj_lr.training_x.load(fn_x,arma::coord_ascii);	
    }
    //add the constant;
	obj_lr.training_y.load(fn_y);
	
	obj_lr.begin(begin_time);

    obj_lr.train();
	obj_lr.end(end_time);
	return 0;
}


