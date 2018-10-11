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
	void backProp(vector<vector<double>> & sigmoidData, vector<vector<double>> & outputData, vector<vector<double>> & inputData);
	~Net();

private:
	vector<vector<double>> preActivationSum;
	vector<vector<double>> hiddenLayers;
	double learningRate;
};

