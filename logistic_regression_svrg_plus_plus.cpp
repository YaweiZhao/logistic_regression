#include <iostream>
#include <cmath>
#include "logistic_regression.hpp"

using namespace std;
using namespace arma;

//SVRG++: training the parameters. The fl2-regularization is added
void logistic_regression::train_svrg_plus_plus()
{
    //produce the samples by a certain probability distribution
    default_random_engine random(time(NULL));    
    vec sample_epoch = produceSamples(random);
    //compute the full gradient
    vec full_gradient = zeros<vec>(DIMENTION);
    int num_gradient = 0;
    setEpochSize(DATA_SIZE/1024);//the initial epoch size is set 1/1024*DATA_SIZE
    int start_index = 0;
    for(int i=0;i<MAX_NUM_ITERATION;i++)
    {
        //increase the epoch size
        setEpochSize(2*EPOCH_SIZE);
        full_gradient = estimateFullGradient(parameter,0,DATA_SIZE); 
        
        vec local_parameter = parameter;
        vec accumulate_parameter = zeros<vec>(DIMENTION);
        start_index = (start_index+EPOCH_SIZE)%((int)(sample_epoch.n_rows));
        for(int j=0;j<EPOCH_SIZE;j++)
        {
            //compute the reduced variance
            vec vr = computeReducedVariance(parameter, local_parameter, full_gradient, sample_epoch[(start_index+j)%((int)(sample_epoch.n_rows))]);
            //update the parameters
            updateParameters(local_parameter, vr, LEARNING_RATE);
            accumulate_parameter = accumulate_parameter + local_parameter;
        }

        //Identify the parameters for the nextls iteration
        accumulate_parameter = accumulate_parameter/EPOCH_SIZE;
        identifyParameters(accumulate_parameter, parameter);
        //evaluate the loss
        if(i%1==0)
        {
            computeLoss(parameter, training_x, training_y);
            //break;
        }
        num_gradient = num_gradient+(EPOCH_SIZE+DATA_SIZE);
        cout<<"the epoch size is: "<<EPOCH_SIZE<<endl;
        cout<<"the total atomic gradient computation is: "<<num_gradient<<endl;
        oss_gradient<<num_gradient<<"\n";
    } 
    log_info(oss,"loss.txt");
    log_info(oss_gradient, "num_gradient.txt");
}
