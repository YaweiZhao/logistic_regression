#include <iostream>
#include <armadillo>
#include "logistic_regression.hpp"

using namespace std;
using namespace arma;

//initialize the logistic regression parameter settings
void initLogisticRegression(int data_size,
                            double learning_rate,
                            double regularized,
                            int max_num_iteration,
                            int epoch_size,
                            int dimention);
{
    DATA_SIZE = data_size;
	LEARNING_RATE = learning_rate;
	REGULARIZED = regularized;
	MAX_NUM_ITERATION = max_num_iteration;
	EPOCH_SIZE = epoch_size;
    DIMENTION = dimention;
}

//record the begin time of the training process
void begin();
{
    



}
//record the end time of the training process
void end();
{
    





}
//training the parameters. The fl2-regularization is added
void train();
{
    double* parameters = new double(DIMENTION+1);
    
    //produce the samples by a certain probability distribution
    produceSamples();
    //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
    setEpochSize();
    for(int i=0;i<MAX_NUM_ITERATION;i++)
    {
        //compute the full gradient
        double full_gradient = computeFullGradient();
        for(int j=0;i<EPOCH_SIZE;j++)
        {
            //compute the reduced variance
            double variance = computeReducedVariance();
            //update the parameters
            updateParameters();
        }
        //Identify the parameters for the next iteration
        identifyParameters();
    }

    
}

//produce the samples by a certain probability distribution
int* produceSamples(const int num_iterations)
{
    int samples[num_iterations] = -1;
    


    
    return samples;
}

//set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
void setEpochSize(int size)
{
    EPOCH_SIZE = size;
}

//compute the full gradient
double computeFullGradient()
{
    double full_gradient = 0;



    return full_gradient;
}

//update the parameters
void updateParameters(double parameters[], double variance)
{
    




    
}

//Identify the parameters for the next iteration
void identifyParameters(double * parameter)
{
        


        
}

