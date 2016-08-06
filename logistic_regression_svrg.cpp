#include <iostream>
#include <random>
#include <cmath>
#include "armadillo"
#include "logistic_regression.hpp"

using namespace std;
using namespace arma;

//#define SVRG
#define ESTIMATE_SVRG

//SVRG: training the parameters. The fl2-regularization is added
void logistic_regression::train_svrg()
{
    const bool EVALUATE_FULL_GRADIENT = true;    
 
    //produce the samples by a certain probability distribution
    default_random_engine random(time(NULL));    
    vec sample_epoch = produceSamples(random);
    //compute the full gradient
    vec full_gradient = zeros<vec>(DIMENTION); 
    wall_clock timer;
    int num_gradient = 0;
    
    double alpha = 0.01;//1-alpha = 0.99, i.e. the confidence level 
    double rho_begin = 0.03;
    int k = DATA_SIZE;
    int begin_index = 0;
   
    for(int i=0;i<MAX_NUM_ITERATION;i++)
    {
        //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
        setEpochSize(k);
        
        vec local_parameter = parameter;
        for(int j=0;j<EPOCH_SIZE;j++)
        {
            //compute the reduced variance
            vec vr = computeReducedVariance(parameter, local_parameter, full_gradient, sample_epoch[i*EPOCH_SIZE+j]);
            //update the parameters
            updateParameters(local_parameter, vr, LEARNING_RATE);
        }

        //Identify the parameters for the nextls iteration
        identifyParameters(local_parameter, parameter);
#ifdef  ESTIMATE_SVRG
        double rho = 1.0*rho_begin/(i+1);
        int temp = (int)((-1)*log(1.0*alpha/2)/rho);
        k = min(DATA_SIZE, temp);
        cout<<"k is :"<<k<<endl;
        begin_index = (begin_index + k)%DATA_SIZE;
#endif
#ifdef SVRG
        begin_index = 0;
        k=DATA_SIZE;
#endif

        full_gradient = estimateFullGradient(parameter, begin_index,k);

        //evaluate the loss
        if(i%1==0)
        {
            computeLoss(parameter, training_x, training_y);
        }
        //double elapsed_seconds = timer.toc();
        //cout<<"the total elapsed seconds is: "<<elapsed_seconds<<endl;
      
        num_gradient = num_gradient+(EPOCH_SIZE+k);
        cout<<"the total atomic gradient computation is: "<<num_gradient<<endl;
        oss_gradient<<num_gradient<<"\n";
        
    } 
    log_info(oss,"loss.txt");
    log_info(oss_gradient, "num_gradient.txt");
}













