#include <iostream>
#include <cmath>
#include "logistic_regression.hpp"

using namespace std;
using namespace arma;

//EMGD: training the parameters. The fl2-regularization is added
void logistic_regression::train_emgd()
{ 

    //produce the samples by a certain probability distribution
    default_random_engine random(time(NULL));    
    vec sample_epoch = produceSamples(random);
    //compute the full gradient
    vec full_gradient = zeros<vec>(DIMENTION);
    
    for(int i=0;i<MAX_NUM_ITERATION;i++)
    {
        //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
        setEpochSize(EPOCH_SIZE);   
        full_gradient = estimateFullGradient(parameter,0,DATA_SIZE); 
        vec local_parameter = parameter;
        for(int j=0;j<EPOCH_SIZE;j++)
        {
//parameter.print("glbal parameter:");
            //compute the reduced variance
            vec vr = computeReducedVariance(parameter, local_parameter, full_gradient, sample_epoch[i*EPOCH_SIZE+j]);
            //update the parameters
            updateParameters(local_parameter, vr, LEARNING_RATE);

            //computeLoss(local_parameter, training_x, training_y);
        }

        //Identify the parameters for the nextls iteration
        identifyParameters(local_parameter, parameter);
        
        //evaluate the loss
        if(i%1==0)
        {
            computeLoss(parameter, training_x, training_y);
            //break;
        }
    } 
    
    log_info(oss,"loss.txt");
    
}
