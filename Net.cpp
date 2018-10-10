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

vector<double> Net::sumWeightsAndValues()
{
	vector<double> tempSigData;
	for (int i = 1; i < realNet.size(); i++)
	{
		vector<double> preActivation;
		for (int j = 0; j < realNet[i].size(); j++)
		{
			double tempCalc = 0;
			for (int k = 0; k < realNet[i][j].connections.size(); k++)
			{
				tempCalc += realNet[i][j].connections[k].weightOld * realNet[i - 1][k].value;
			}
			realNet[i][j].value = tempCalc;
			preActivation.push_back(tempCalc);
			realNet[i][j].value = sigmoid(realNet[i][j].value);
			if (i == realNet.size() - 1)
			{
				tempSigData.push_back(realNet[i][j].value);
			}
		}
		preActivationSum.push_back(preActivation);
	}
	return tempSigData;
}

double Net::calcError(vector<vector<double>>& sigmoidData, vector<vector<double>>& outputData)
{
	double runningDifference = 0;
	for (unsigned int i = 0; i < sigmoidData.size(); i++)
	{
		for (int j = 0; j < sigmoidData[i].size(); j++)
		{
			double tempDifference = sigmoidData[i][j] - outputData[i][j];
			runningDifference += pow(tempDifference, 2);
		}
	}

	runningDifference = runningDifference * (1.00 / sigmoidData.size());

	return runningDifference;
}

void Net::backProp(vector<vector<double>>& sigmoidData, vector<vector<double>>& outputData, vector<vector<double>>& inputData)
{
	//All Layers starting from the back
	for (int i = realNet.size() - 1; i >= 0; i--)
	{
		double weightUpdate = 0;
		//Specific Layer
		for (int j = 0; j < realNet[i].size(); j++)
		{
			//Specific node has x amount of connections
			for (int k = 0; k < realNet[i][j].connections.size(); k++)
			{
				//Updating the weights
				for (int l = 0; l < sigmoidData.size(); l++)
				{
					double tempWeight = 0;
					tempWeight = 2 * (sigmoidData[k][l] - outputData[k][l]);
					if (i == realNet.size() - 1)
					{

					}
					for (int m = 0; m < (realNet.size() - 1) - i; m++)
					{

					}
					//weightUpdate += 2 * (sigmoidData[k][l] - outputData[k][l]) * derivate(preActivationSum[k][l]) * realNet[i-1][j].value;
				}
			}
		}
	}
}

Net::~Net()
{
}