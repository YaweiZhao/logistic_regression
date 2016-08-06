#include <iostream>
#include <random>
#include <cmath>
#include "armadillo"
#include "logistic_regression.hpp"


using namespace std;
using namespace arma;

//#define SVRG
#define ESTIMATE_SVRG



//logistic_regression obj_lr;
//initialize the logistic regression parameter settings
logistic_regression::logistic_regression(){}
logistic_regression::logistic_regression(int data_size,
                            double learning_rate,
                            double regularized,
                            int max_num_iteration,
                            int epoch_size,
                            int dimention,
                            double gamma/*momentum*/)
{
    DATA_SIZE = data_size;
	LEARNING_RATE = learning_rate;
	REGULARIZED = regularized;
	MAX_NUM_ITERATION = max_num_iteration;
	EPOCH_SIZE = epoch_size;
    //THETA = 1;
    DIMENTION = dimention;
    parameter = zeros<vec>(DIMENTION);
    momentum = zeros<vec>(DIMENTION);
    GAMMA = gamma;
    do_full_gradient = true;
    oss.str("");
    oss_gradient.str("");
    DISTANCE = 1e-5;
    /*S2GD*/
    MAX_EPOCH_SIZE = DATA_SIZE;
    LOWER_BOUND_S2GD = REGULARIZED;
}



//record the begin time of the training process
void logistic_regression::begin(time_t& begin)
{
    time(&begin);
}
//record the end time of the training process
void logistic_regression::end(time_t& end)
{
    time(&end);
}

//produce the samples by a certain probability distribution
vec logistic_regression::produceSamples(default_random_engine random)
{
    int n_instances = EPOCH_SIZE*MAX_NUM_ITERATION;
    vec samples = zeros<vec>(n_instances);
    uniform_int_distribution<int> dis1(0, DATA_SIZE-1);
    for (int i=0;i<n_instances;i++)
    {
        //samples(i) = dis1(random);/*sample instances randomly*/
	samples(i) = i%DATA_SIZE;
    }
    return samples;
}

//set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
void logistic_regression::setEpochSize(int size)
{
    EPOCH_SIZE = size;
}


//compute the regularized norm's gradient
vec logistic_regression::computeRegularizedGradient(vec& parameter)
{
    vec regularized_gradient = 2*REGULARIZED*parameter;
    return regularized_gradient;
}

//compute the stochastic local gradient
vec logistic_regression::computeStochasticGradient(vec& parameters, int index)
{
    double w_x = as_scalar(parameters.t()*training_x.col(index));
    double y = training_y[index];
    double temp0 = (1/(1+std::exp(y*w_x)))*(-1*y);
    //add the regularized norm's gradient
    vec temp_regularized = computeRegularizedGradient(parameters);
    vec gradient(temp0*training_x.col(index)+temp_regularized);
    return gradient;
}

//compute the full gradient
vec logistic_regression::estimateFullGradient(vec& global_parameter,int start_index, int num)
{
    vec full_gradient = zeros<vec>(DIMENTION);
    for(int i=start_index;i<(start_index+num);i++)//consider the constant
    {
        int real_start = i%DATA_SIZE;
        vec temp0 = computeStochasticGradient(global_parameter, real_start);
        full_gradient += temp0;
    }
    full_gradient = full_gradient/num;

    return full_gradient;
}



//compute the reduced variance
vec logistic_regression::computeReducedVariance(vec& global_parameter, vec& local_parameter, vec& full_gradient, int index)
{
    vec vr = zeros<vec>(DIMENTION);
    vec temp0 = computeStochasticGradient(local_parameter, index);
    vec temp1 = computeStochasticGradient(global_parameter, index); //used for basic SVRG
    vr=temp0-temp1+full_gradient;/*SVRG update rule*/
    return vr;
}


//update the parameters
void logistic_regression::updateParameters(vec& local_parameter, vec& vr, double learning_rate)
{
    vec temp = learning_rate*vr + GAMMA*momentum/*momentum*/;
    local_parameter = local_parameter - temp;
    momentum = temp;
}

//Identify the parameters for the next iteration
void logistic_regression::identifyParameters(vec& local_parameter, vec& global_parameter)
{
    global_parameter = local_parameter;//used for basic SVRG
    //used fot testoi
}

//compute the loss function
double logistic_regression::computeLoss(vec& parameter, mat& x, vec& y)
{
    double loss=0;
    for(int i=0;i<DATA_SIZE;i++)
    {
        double temp = as_scalar(parameter.t()*x.col(i));
        loss = loss + -1*log(1/(1+exp(-1*temp*y(i))));
        //add the regularized item
        loss = loss + REGULARIZED*as_scalar(parameter.t()*parameter);
    }
    loss = loss/DATA_SIZE;
    oss<<loss<<"\n";
    cout<<"The loss now is: "<<loss<<endl;
    return loss;
}

//log the loss 
void logistic_regression::log_info(ostringstream &oss1, string filename)
{
    ofstream fout(filename);
    fout<<oss1.str();
    oss1.str("");
    fout.close();
    fout.clear();
}

