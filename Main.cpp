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

	double currentError = 100.00;

	//Gets user input about charcteristics about the net
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

	double threshold;
	cout << "Please enter threshold: ";
	cin >> threshold;

	vector<Neuron> outputNodeVec;

	for (int i = 0; i < howManyOutputs; i++)
	{
		Neuron temp;
		outputNodeVec.push_back(temp);
	}

	tempNet.push_back(outputNodeVec);

	//Creates Net
	Net myNet = Net(tempNet);

	//Where to pull data
	ifstream testData;
	testData.open("C:/Users/chuck/Documents/Math Thesis/TestData.txt");


	//Holds input and output data
	vector<vector<double>> inputData;
	vector<vector<double>> outputData;

	int numDataSet = 0;
	//Collects data from file
	while (!testData.eof())
	{
		numDataSet++;

		vector<double> inputValues;
		vector<double> outputValues;

		string inputs;
		getline(testData, inputs);
		inputs.erase(0, 7);
		cout << "Inputs: " << inputs << endl;

		for (int i = 0; i < howManyInputs; i++)
		{
			int pos = inputs.find(",");
			if (pos == -1)
			{
				int intInputVal = stoi(inputs);
				inputValues.push_back((double)intInputVal);
			}
			else
			{
				string inputVal;
				inputVal = inputs.substr(0, pos);
				int intInputVal = stoi(inputVal);
				inputValues.push_back((double)intInputVal);
				inputs.erase(0, pos + 1);
			}
		}

		inputData.push_back(inputValues);

		string outputs;
		getline(testData, outputs);
		outputs.erase(0, 8);
		cout << "Desired outputs: " << outputs << endl;
		for (int i = 0; i < howManyOutputs; i++)
		{
			int pos = outputs.find(",");
			
			if (pos == -1)
			{
				int intOutVal = stoi(outputs);
				outputValues.push_back((double)intOutVal);
			}
			else
			{
				string outputVal = outputs.substr(0, pos);
				int intOutVal = stoi(outputVal);
				outputValues.push_back((double)intOutVal);
				outputs.erase(0, pos + 1);
			}

		}

		outputData.push_back(outputValues);
	}

	testData.close();

	int numTests = 0;
	vector<vector<double>> sigmoidData;

	//Begins testing
	while (currentError > threshold)
	{
		numTests++;
		
		cout << "Test Number: " << numTests << endl;
		sigmoidData.clear();

		//For each data set
		for (int i = 0; i < numDataSet; i++)
		{
			//Initialize the inputs
			myNet.initializeInput(inputData[i]);
		}
	}

	cin.get();
	return 0;
}