#include "Net.h"
#include "Neuron.h"
#include "Connection.h"
#include <vector>

Net::Net(vector<vector<Neuron>> & tempNet)
{
	realNet = tempNet;
	for (int i = 0; i < realNet[realNet.size() - 1].size(); i++)
	{
		for (int j = realNet[realNet.size() - 2 - i].size() - 1; j >= 0 ; j--)
		{
			Connection temp;
			realNet[realNet.size() - 1][i].connections.push_back(temp);
			for (int k = 0; k < realNet[0].size(); k++)
			{
				Connection temp;
				realNet[realNet.size() - 2 - i][j].connections.push_back(temp);
			}
		}
	}
}

void Net::initializeInput(vector<double> & inputs)
{
	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		realNet[0][i].value = inputs[i];
	}
}

Net::~Net()
{
}