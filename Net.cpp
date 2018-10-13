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
	learningRate = .1;
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
	vector<double> preActivation;
	for (int i = 1; i < realNet.size(); i++)
	{
		vector<double> tempHidden;
		for (int j = 0; j < realNet[i].size(); j++)
		{
			double tempCalc = 0;
			for (int k = 0; k < realNet[i][j].connections.size(); k++)
			{
				tempCalc += realNet[i][j].connections[k].weightOld * realNet[i - 1][k].value;
			}
			preActivation.push_back(tempCalc);
			realNet[i][j].value = sigmoid(tempCalc);
			if (i == realNet.size() - 1)
			{
				tempSigData.push_back(realNet[i][j].value);
			}
			else
			{
				tempHidden.push_back(realNet[i][j].value);
			}
		}
		if (i != realNet.size() - 1)
		{
			hiddenLayers.push_back(tempHidden);
		}
	}
	preActivationSum.push_back(preActivation);
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
	for (int i = realNet.size() - 1; i >= 1; i--)
	{
		double weightUpdate = 0;
		//How many nodes in a specific layer
		for (int j = 0; j < realNet[i].size(); j++)
		{
			//Updating Weights
			if (i == realNet.size() - 1)
			{
				int preActStart = hiddenLayers.size();
				for (int n = 0; n < realNet[i][j].connections.size(); n++)
				{
					for (int k = 0; k < sigmoidData.size(); k++)
					{
						double tempWeight = 1;
						tempWeight = 2 * (sigmoidData[k][j] - outputData[k][j]);
						double sum = preActivationSum[k][preActStart];
						tempWeight = tempWeight * derivate(sum) * hiddenLayers[k][n];
						realNet[i][j].connections[k].weightDelta = tempWeight * -1;
						realNet[i][j].connections[k].weightOld = realNet[i][j].connections[k].weightOld + (learningRate * realNet[i][j].connections[k].weightDelta);
					}
				}
				preActStart++;
			}
			/*
			//How many weights in a node
			for (int k = 0; k < realNet[i][j].connections.size(); k++)
			{
				//Updating the weights
				if (i == realNet.size() -1)
				{
					int preActStart = hiddenLayers.size();
					for (int n = 0; n < sigmoidData.size(); n++)
					{
						double tempWeight = 1;
						tempWeight = 2 * (sigmoidData[k][j] - outputData[k][j]);
						double sum = preActivationSum[k][preActStart];
						tempWeight = tempWeight * derivate(sum) * hiddenLayers[k][n];
						realNet[i][j].connections[k].weightDelta = tempWeight * -1;
						realNet[i][j].connections[k].weightOld = realNet[i][j].connections[k].weightOld + (learningRate * realNet[i][j].connections[k].weightDelta);
					}
					preActStart++;
					for (int l = 0; l < sigmoidData.size(); l++)
					{
						
					}
				}
				else
				{
					double sigmoidSum = 0;
					double overallSum = 0;
					for (int m = 0; m < sigmoidData.size(); m++)
					{
						double tempWeight = 1;
						tempWeight = 2 * (sigmoidData[k][m] - outputData[k][m]);
						double sum = preActivationSum[k][m];
						tempWeight = tempWeight * derivate(sum) * hiddenLayers[k][m];
						sigmoidSum += tempWeight;
					}
				}
			}*/
		}
	}
}

Net::~Net()
{
}