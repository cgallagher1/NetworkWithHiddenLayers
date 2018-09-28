#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "Neuron.h"
#include "Net.h"

using namespace std;

int main()
{
	srand(time(0));

	ifstream testData;
	testData.open("C:/Users/chuck_000/Documents/Math Thesis/TestData.txt");

	int howManyInputs;
	cout << "Please enter how many input nodes you want: ";
	cin >> howManyInputs;

	vector<vector<Neuron>> tempNet;

	vector<Neuron>inputNodeVec;

	for (int i = 0; i < howManyInputs; i++)
	{
		Neuron temp;
		inputNodeVec.push_back(temp);
	}

	tempNet.push_back(inputNodeVec);

	int howManyHiddenLayers;
	cout << "Please enter how many hidden layers you want: ";
	cin >> howManyHiddenLayers;

	int hiddenNodesPerLayer;
	cout << "Please enter how many hidden nodes per layer: ";
	cin >> hiddenNodesPerLayer;

	for (int i = 0; i < howManyHiddenLayers; i++)
	{
		vector<Neuron> temp;
		for (int j = 0; j < hiddenNodesPerLayer; j++)
		{
			Neuron tempNeuron;
			temp.push_back(tempNeuron);
		}
		tempNet.push_back(temp);
	}

	int howManyOutputs;
	cout << "Please enter how many output nodes you want: ";
	cin >> howManyOutputs;

	vector<Neuron> outputNodeVec;

	for (int i = 0; i < howManyOutputs; i++)
	{
		Neuron temp;
		outputNodeVec.push_back(temp);
	}

	tempNet.push_back(outputNodeVec);

	Net myNet = Net(tempNet);

	cin.get();
	return 0;
}