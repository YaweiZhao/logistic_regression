#include <iostream>
#include <armadillo>
#include "logistic_regression.hpp"

using namespace std;
using namespace arma;

int main()
{

    extern int DATA_SIZE;
	extern double LEARNING_RATE;
	extern double REGULARIZED;
	extern  int MAX_NUM_ITERATION;
	extern  int EPOCH_SIZE;

    extern  int DIMENTION;
    extern  double GAMMA;
    extern time_t begin_time;
    extern time_t end_time;
    extern bool SPARSE;
    extern bool DENSE;
    //traning file
    extern char* fn_x;
    extern char* fn_y;
    
    extern logistic_regression obj_lr;
    
    mat x_mat;
    x_mat.load(fn_x,arma::raw_binary);
    x_mat.reshape(DATA_SIZE,DIMENTION-1);
    x_mat.insert_cols(x_mat.n_cols,1);
    x_mat.col(DIMENTION-1).fill(1);

    obj_lr.training_x = x_mat.t();
    
	obj_lr.training_y.load(fn_y);
	
	obj_lr.begin(begin_time);
    obj_lr.train_svrg();
    //obj_lr.train_s2gd();
    //obj_lr.train_emgd();
    //obj_lr.train_svr_ght();
    //obj_lr.train_svrg_plus_plus();
    //obj_lr.train_katyusha();
    //obj_lr.train_sag();
    //obj_lr.train_sdca();


	obj_lr.end(end_time);
	return 0;
}



