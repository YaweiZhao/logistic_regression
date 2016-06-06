class logistic_regression
{
    public:
    int DATA_SIZE;
	double LEARNING_RATE;
	double REGULARIZED;
	int MAX_NUM_ITERATION;
	int EPOCH_SIZE;
    int DIMENTION;
    
    public:
    //initialize the logistic regression parameter settings
    void initLogisticRegression(int data_size,
                            double learning_rate,
                            double regularized,
                            int max_num_iteration,
                            int epoch_size,
                            int dimention);
    //record the begin time of the training process
    void begin();
    //record the end time of the training process
    void end();
    //training the parameters. The fl2-regularization is added
    void train();

    //produce the samples by a certain probability distribution
    int* produceSamples(const int num_iterations);

    //set the epoch size. Defaultly, it is set by the variable: EPOCH_SIZE
    void setEpochSize(int size);

    //compute the full gradient
    double computeFullGradient();

    //update the parameters
    void updateParameters(double parameters[], double variance);

    //Identify the parameters for the next iteration
    void identifyParameters(double * parameter)
    {
        


        
    }





    
}
