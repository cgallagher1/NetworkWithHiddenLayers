#include "Net.h"
#include "Neuron.h"
#include "Connection.h"
#include <vector>

const double e = 2.7182818284590452353602874713527;

Net::Net(vector<vector<Neuron>> & tempNet)
{
	realNet = tempNet;
	if (realNet.size() == 2)
	{
		for (int i = 0; i < realNet[1].size(); i++)
		{
			for (int j = 0; j < realNet[0].size(); j++)
			{
				Connection temp;
				realNet[1][i].connections.push_back(temp);
			}
		}
	}
	else if(realNet.size() == 3)
	{
		for (int i = 0; i < realNet[1].size(); i++)
		{
			for (int j = 0; j < realNet[0].size(); j++)
			{
				Connection temp;
				realNet[1][i].connections.push_back(temp);
			}
		}
		for (int i = 0; i < realNet[2].size(); i++)
		{
			for (int j = 0; j < realNet[1].size(); j++)
			{
				Connection temp;
				realNet[2][i].connections.push_back(temp);
			}
		}
	}
	else
	{
		//For input to hidden
		for (int i = 0; i < realNet[1].size(); i++)
		{
			for (int j = 0; j < realNet[0].size(); j++)
			{
				Connection temp;
				realNet[1][i].connections.push_back(temp);
			}
		}
		//For hidden to hidden
		for (int i = realNet.size() - 2; i > 1; i--)
		{
			for (int j = 0; j < realNet[i].size(); j++)
			{
				for (int k = 0; k < realNet[i-1].size(); k++)
				{
					Connection temp;
					realNet[i][j].connections.push_back(temp);
				}
			}
		}
		//For last hidden to output
		for (int i = 0; i < realNet[realNet.size() - 1].size(); i++)
		{
			for (int j = 0; j < realNet[realNet.size() -2].size(); j++)
			{
				Connection temp;
				realNet[realNet.size() - 1][i].connections.push_back(temp);
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

double Net::sigmoid(double & sum)
{
	double afterSigmoid = (1 / (1 + pow(e, (sum * -1))));
	return afterSigmoid;
}

double Net::derivate(double & sum)
{
	double afterDer = (pow(e, -sum)) / pow((1 + pow(e, -sum)), 2);
	return afterDer;
}

double Net::sumWeightsAndValues()
{
	double sum;
	for (int i = 1; i < realNet.size(); i++)
	{
		for (int j = 0; j < realNet[i].size(); j++)
		{
			for (int k = 0; k < realNet[i][j].connections.size(); k++)
			{

			}
		}
	}
	return 0.0;
}

Net::~Net()
{
}