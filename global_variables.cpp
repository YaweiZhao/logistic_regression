#include <iostream>
#include <random>
#include <armadillo>
#include "logistic_regression.hpp"

using namespace arma;
using namespace std;

enum {
SVRG=0,
SDCA=1,
SAG=2,
S2GD=3,
EMGD=4,
SVR_GHT=5,
SVRG_PLUS_PLUS=6,
KATYUSHA=7,
}ALGORITHM;

int DATA_SIZE=581012;/*581012*/
double LEARNING_RATE=1e-3;
double REGULARIZED = 1e-5;/*regularization*/
int MAX_NUM_ITERATION = 800;
int EPOCH_SIZE = DATA_SIZE;/*1/256*DATA_SIZE for the initial value when conducting svrg++*/
//add the constant
int DIMENTION = 54+1;/*DIMENTION+1*/
double GAMMA = 0;/*momentum*/
time_t begin_time=0;
time_t end_time=0;
bool SPARSE = false;
bool DENSE = true;
//traning file
char* fn_x = "raw_dense.bin"/*"raw_dense.bin"*/;
char* fn_y = "label.txt";



//S2GD
vec epoch_size_distribution = zeros<vec>(EPOCH_SIZE);


logistic_regression obj_lr(DATA_SIZE,
                                  LEARNING_RATE,
                                  REGULARIZED,
                                  MAX_NUM_ITERATION,
                                  EPOCH_SIZE,
                                  DIMENTION,
                                  GAMMA);



