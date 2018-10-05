#pragma once
#include "Neuron.h"
#include <vector>
#include <iostream>

class Net
{
public:
	Net(vector<vector<Neuron>> & tempNet);
	vector<vector<Neuron>> realNet;
	void initializeInput(vector<double> & inputs);
	double sigmoid(double & sum);
	double derivate(double & sum);
	vector<double> sumWeightsAndValues();
	double calcError(vector<vector<double>> & sigmoidData, vector<vector<double>> & outputData);
	double currentError;
	~Net();

private:
};

