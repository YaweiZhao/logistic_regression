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
    sp_mat training_x;
    vec training_y;
    vec parameter;
    vec momentum;
    double GAMMA;

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
    //training the parameters. The fl2-regularization is added
    void train();

    //produce the samples by a certain probability distribution
    vec produceSamples(default_random_engine random);

    //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
    void setEpochSize(int size);

    //compute the stochastic local gradient
    vec computeStochasticGradient(vec& local_parameter, int index);

    //compute the full gradient; while the constant part is not included.
    vec computeFullGradient(vec& global_parameter);

    //compute the regularized norm's gradient
    vec computeRegularizedGradient(vec& global_parameter);

    //compute the reduced variance
    vec computeReducedVariance(vec& global_parameter, vec& local_parameter, vec& full_gradient, int index);


    //update the parameters
    void updateParameters(vec& local_parameter, vec& vr, double learning_rate);

    //Identify the parameters for the next iteration
    void identifyParameters(vec& local_parameter, vec& global_parameter);

    //compute the loss function
    double computeLoss(vec& parameter, sp_mat& x, vec& y);
    
};
