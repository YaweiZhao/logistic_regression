#include <iostream>
#include <armadillo>
#include <random>
#include "logistic_regression.hpp"


using namespace std;
using namespace arma;

//initialize the logistic regression parameter settings
logistic_regression(){}
logistic_regression(int data_size,
                            double learning_rate,
                            double regularized,
                            int max_num_iteration,
                            int epoch_size,
                            int dimention)
{
    DATA_SIZE = data_size;
	LEARNING_RATE = learning_rate;
	REGULARIZED = regularized;
	MAX_NUM_ITERATION = max_num_iteration;
	EPOCH_SIZE = epoch_size;
    DIMENTION = dimention;
    parameter = zeros<vec>(DIMENTION);
}

//record the begin time of the training process
void begin(time_t begin)
{
    time(&begin);
}
//record the end time of the training process
void end(time_t end)
{
    time(&end);
}
//training the parameters. The fl2-regularization is added
void train()
{
    for(int i=0;i<MAX_NUM_ITERATION;i++)
    {
        //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
        setEpochSize(epoch_size);
        //produce the samples by a certain probability distribution
        default_random_engine random(time(NULL));    
        vec sample_epoch = produceSamples(epoch_size,random);
        //compute the full gradient
        vec full_gradient = computeFullGradient(parameter);
        vec local_parameter = zeros<vec>(DIMENTION);
        for(int j=0;i<EPOCH_SIZE;j++)
        {
            //compute the reduced variance
            vec vr = computeReducedVariance(parameter, local_parameter, full_gradient, j);
            //update the parameters
            updateParameters(local_parameter, vr, learning_rate);
        }
        //Identify the parameters for the next iteration
        identifyParameters(local_parameter, parameter);

        //evaluate the loss
        if(i%5==0)
        {
            computeLoss(parameter, training_x, training_y);
        }
    }

    
}

//produce the samples by a certain probability distribution
vec produceSamples(int epoch_size, default_random_engine random)
{
    vec samples = zeros<vec>(epoch_size);
    uniform_int_distribution<int> dis1(0, DATA_SIZE);
    for (int i=0;i<epoch_size;i++)
    {
        samples(i) = dis1(random);
    }
    return samples;
}

//set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
void setEpochSize(int size)
{
    EPOCH_SIZE = size;
}

//compute the regularized norm's gradient
vec computeRegulrizedGradient(vec parameter)
{
    return 2*REGULARIZED*parameter;
}
//compute the stochastic local gradient
vec computeStochasticGradient(vec parameters, int index)
{
    vec w_x = parameters.t()*training_x.col(index);
    vec temp0 = (1/(1+exp(training_y(index)*w_x)))*(-1*training_y(index)*training_x.col(index));
    
    return temp0;
}

//compute the full gradient
vec computeFullGradient(vec global_parameter)
{
    vec full_gradient = zeros<vec>(DIMENTION);
    for(int i=0;i<DATA_SIZE;i++)//consider the constant
    {
        vec temp0 = computeStochasticGradient(global_parameter, i);
        full_gradient += temp0;
    }
    //add the regularized norm's gradient
    vec temp_regularized = computeRegularizedGradient(global_parameter);
    full_gradient += temp_regularized;
    full_gradient = full_gradient/DATA_SIZE;

    return full_gradient;
}

//compute the reduced variance
vec computeReducedVariance(vec global_parameter, vec local_parameter, vec full_gradient, int index)
{
    vec vr = zeros<vec>(DIMENTION);
    vec temp0 = computeStochasticGradient(local_parameter, index);
    vec temp1 = computeStochasticGradient(global_parameter, index);
    vr=temp0-temp1+full_gradient;

    return vr;
}


//update the parameters
void updateParameters(vec local_parameter, vec vr, double learning_rate)
{
    local_parameter = local_parameter - learning_rate*vr;
}

//Identify the parameters for the next iteration
void identifyParameters(vec local_parameter, vec global_parameter)
{
    global_parameter = local_parameter;
}

//compute the loss function
double computeLoss(vec parameter, mat x, vec y)
{
    double loss=0;
    for(int i=0;i<DATA_SIZE;i++)
    {
        loss += -1*log(1/(1+exp(-1*parameter.t()*x.col(i)*y(i))));
    }
    loss = loss/DATA_SIZE;
    return loss;
}

