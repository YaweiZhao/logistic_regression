#include <iostream>
#include <random>
#include <armadillo>

using namespace arma;

class logistic_regression
{
    public:
    int DATA_SIZE;
	double LEARNING_RATE;
	double REGULARIZED;
	int MAX_NUM_ITERATION;
	int EPOCH_SIZE;
    int DIMENTION;
    mat training_x;
    mat training_y;
    vec parameter;

    public:
    //initialize the logistic regression parameter settings
    void initLogisticRegression(int data_size,
                            double learning_rate,
                            double regularized,
                            int max_num_iteration,
                            int epoch_size,
                            int dimention);
    //record the begin time of the training process
    void begin(time_t begin);
    //record the end time of the training process
    void end(time_t end);
    //training the parameters. The fl2-regularization is added
    void train();

    //produce the samples by a certain probability distribution
    vec produceSamples(int epoch_size);

    //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
    void setEpochSize(int size);

    //compute the stochastic local gradient
    vec computeStochasticGradient(vec parameters, int index);

    //compute the full gradient; while the constant part is not included.
    vec computeFullGradient(vec global_parameter);

    //compute the reduced variance
    vec computeReducedVariance(vec global_parameter, vec local_parameter, vec full_gradient, int index);


    //update the parameters
    void updateParameters(vec local_parameter, double vr, double learning_rate);

    //Identify the parameters for the next iteration
    void identifyParameters(vec local_parameter, vec global_parameter);

    //compute the loss function
    double computeLoss(vec parameter, mat x, vec y);
    
};
