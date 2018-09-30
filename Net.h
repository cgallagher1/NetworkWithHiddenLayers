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
	double sumWeightsAndValues();

	~Net();

private:
	vector<Neuron>outputVec;
	vector<Neuron>inputVec;
};

