#include <iostream>
#include <cmath>
#include <random>
#include "logistic_regression.hpp"

using namespace std;
using namespace arma;


extern vec epoch_size_distribution;

//get the base of the fraction of S2GD
vec logistic_regression::getBase_S2GD()
{
    vec value = zeros<vec>(EPOCH_SIZE);
    for (int i=0;i<EPOCH_SIZE;i++)
    {
        value[i] = pow(1-LEARNING_RATE*LOWER_BOUND_S2GD, EPOCH_SIZE-i);
    }
    return value;
}

//set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
vec logistic_regression::setEpochSize_S2GD(vec value)
{
    vec factor = ones<vec>(EPOCH_SIZE);
    double sum = as_scalar(factor.t()*value);
    vec temp = zeros<vec>(EPOCH_SIZE);
    for(int i=0;i<EPOCH_SIZE;i++)
    {
        temp[i] = value[i]/sum;
    }
    vec cum_epoch_size(cumsum(temp));
    return cum_epoch_size;
}

//set the epoch size for a specific epoch .
int logistic_regression::setSpecificEpochSize_S2GD(int i)
{
    std::random_device rd;
    std::mt19937 gen(rd());    
    std::uniform_real_distribution<> dist(0,1);
    double a = dist(gen);
    mat::iterator start = epoch_size_distribution.begin();
    mat::iterator end = epoch_size_distribution.end();
    int current_epoch_size = 0;
    for(mat::iterator i = start+1; i!=end;i++)
    {
        current_epoch_size++;
        if(*(i-1)<= a && a < *(i)) return current_epoch_size;
    }
    
}


//S2GD: training the parameters. The fl2-regularization is added
void logistic_regression::train_s2gd()
{
    //produce the samples by a certain probability distribution
    default_random_engine random(time(NULL));    
    vec sample_epoch = produceSamples(random);
    //compute the full gradient
    vec full_gradient = zeros<vec>(DIMENTION);
    int num_gradient = 0;
    vec value = getBase_S2GD();
    //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
    epoch_size_distribution = setEpochSize_S2GD(value);

    for(int i=0;i<MAX_NUM_ITERATION;i++)
    {
        full_gradient = estimateFullGradient(parameter,0,DATA_SIZE);  
        vec local_parameter = parameter;
        //set the epoch size for a specific epoch .
        int current_epoch_size = setSpecificEpochSize_S2GD(i);
        cout<<"the current epoch size is: "<<current_epoch_size<<endl;
        for(int j=0;j<current_epoch_size;j++)
        {
            //compute the reduced variance
            vec vr = computeReducedVariance(parameter, local_parameter, full_gradient, sample_epoch[i*EPOCH_SIZE+j]);
            //update the parameters
            updateParameters(local_parameter, vr, LEARNING_RATE);
        }

        //Identify the parameters for the nextls iteration
        identifyParameters(local_parameter, parameter);
        //evaluate the loss
        if(i%1==0)
        {
            computeLoss(parameter, training_x, training_y);
            //break;
        }
        num_gradient = num_gradient+(current_epoch_size+DATA_SIZE);
        cout<<"the total atomic gradient computation is: "<<num_gradient<<endl;
        oss_gradient<<num_gradient<<"\n";
    } 
    log_info(oss_gradient, "num_gradient.txt");
    log_info(oss,"loss.txt");
}
