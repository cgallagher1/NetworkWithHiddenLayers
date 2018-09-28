#pragma once
#include "Neuron.h"
#include <vector>
#include <iostream>

class Net
{
public:
	Net(vector<vector<Neuron>> & tempNet);
	vector<vector<Neuron>> realNet;
	void initializeInput();
	~Net();

private:

};

