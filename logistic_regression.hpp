#ifndef _INCLUDE_LOGISTIC_REGRESSION_HPP_
#define _INCLUDE_LOGISTIC_REGRESSION_HPP_

#include <iostream>
#include <random>
#include <armadillo>
using namespace arma;
using namespace std;

class logistic_regression
{
    public:
    int DATA_SIZE;
	double LEARNING_RATE;
	double REGULARIZED;
	int MAX_NUM_ITERATION;
	int EPOCH_SIZE;
    int DIMENTION;
    double THETA;// used to improved SVRG
    mat training_x;
    vec training_y;
    vec parameter;
    vec momentum;
    double GAMMA;
    bool do_full_gradient;
    std::ostringstream oss;
    std::ostringstream oss_gradient;
    double DISTANCE;
    /*S2GD*/
    int MAX_EPOCH_SIZE;
    double LOWER_BOUND_S2GD;
   
    public:
    //initialize the logistic regression parameter settings
    logistic_regression();
    logistic_regression(int data_size,
                            double learning_rate,
                            double regularized,
                            int max_num_iteration,
                            int epoch_size,
                            int dimention,
                            double gamma);
    //record the begin time of the training process
    void begin(time_t& begin);
    //record the end time of the training process
    void end(time_t& end);
    //SVRG: training the parameters. The fl2-regularization is added.
    void train_svrg();
    //SAG: training the parameters. The fl2-regularization is added.
    void train_sag();
    //SDCA: training the parameters. The fl2-regularization is added.
    void train_sdca();
    //S2GD: training the parameters. The fl2-regularization is added.
    void train_s2gd();
    //EMGD: training the parameters. The fl2-regularization is added.
    void train_emgd();
    //SVR-GHT: training the parameters. The fl2-regularization is added.
    void train_svr_ght();
    //SVRG++: training the parameters. The fl2-regularization is added.
    void train_svrg_plus_plus();
    //KATYUSHA: training the parameters. The fl2-regularization is added.
    //void train_katyusha();

    //produce the samples by a certain probability distribution
    vec produceSamples(default_random_engine random);

    //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
    void setEpochSize(int size);

    //compute the stochastic local gradient
    vec computeStochasticGradient(vec& local_parameter, int index);

    //compute the full gradient; while the constant part is not included.
    vec estimateFullGradient(vec& global_parameter,int start_index, int num);

    //compute the regularized norm's gradient
    vec computeRegularizedGradient(vec& global_parameter);

    //compute the reduced variance
    vec computeReducedVariance(vec& global_parameter, vec& local_parameter, vec& full_gradient, int index);


    //update the parameters
    void updateParameters(vec& local_parameter, vec& vr, double learning_rate);

    //Identify the parameters for the next iteration
    void identifyParameters(vec& local_parameter, vec& global_parameter);

    //compute the loss function
    double computeLoss(vec& parameter, mat& x, vec& y);

//log the loss
    void log_info(ostringstream &oss, string filename);

    //set the base of the fraction of S2GD
    vec getBase_S2GD();
    //set the epoch size's distribution.
    vec setEpochSize_S2GD(vec value);
    //set the epoch size for a specific epoch .
    int setSpecificEpochSize_S2GD(int i);





};

#endif
