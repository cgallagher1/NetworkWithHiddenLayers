#pragma once
#include <vector>
#include "Connection.h"
using namespace std;

class Neuron
{
public:
	Neuron();
	~Neuron();
	vector<Connection> connections;
	double value;
private:

};

