class logistic_regression
{
    public:
    int DATA_SIZE;
	double LEARNING_RATE;
	double REGULARIZED;
	int MAX_NUM_ITERATION;
	int EPOCH_SIZE;
    
    public:
    //initialize the logistic regression parameter settings
    void initLogisticRegression(int data_size,
                            double learning_rate,
                            double regulazied,
                            int max_num_iteration,
                            int epoch_size);
    //record the begin time of the training process
    void begin();
    //record the end time of the training process
    void end();
    //training the parameters. The fl2-regularization is added
    void train();



}
