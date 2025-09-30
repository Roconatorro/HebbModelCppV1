#include <iostream>
#include <vector>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Net.h"
#include "Neuron.h"
#include "Synapse.h"
#include "SFML/Graphics.hpp"

void manualInput(Net& myNet);
std::vector<unsigned> fillInput(std::vector<unsigned> inputVals, Net myNet);

int main()
{
	//for random weight generation
	srand(time(0));

	std::vector<unsigned> layout{ 5, 5, 5, 5 }; //index0 Neurons in layer 0, index1 Neurons in layer1, ...

	//Net myNet(layout, axonHillocThreshold, hebbIncrease, hebbDecrease, inhibWeight);
	Net myNet(layout, 0.3, 0.5, 0.99, -0.5); //default values

	manualInput(myNet);
	return 0;
}

void manualInput(Net& myNet)
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Neuron window");

	while (true)
	{
		//Get Input
		std::cout << "Select Input: (ex: 001 fires 3rd Neuron)\n";
		std::vector<unsigned> inVals;
		std::string in;
		std::cin >> in;
		for (unsigned i = 0; i < in.size(); ++i)
		{
			inVals.push_back(in[i] - '0');
		}
		std::vector<unsigned> inputVals = fillInput(inVals, myNet);

		std::cout << "How many times do you want to run the input?\n";
		unsigned count;
		std::cin >> count;

		std::cout << "Running input: ";
		for (unsigned i = 0; i < inputVals.size(); ++i)
		{
			std::cout << inputVals[i] << ", ";
		}
		std::cout << count << " times \n";

		//Use Net
		for (unsigned i = 0; i < count; ++i)
		{
			myNet.feedForward(inputVals);
			//myNet.displayNet();
			myNet.paintNet(window);
		}
	}
}

std::vector<unsigned> fillInput(std::vector<unsigned> inputVals, Net myNet)
{
	std::vector<unsigned> newInput;

	for (unsigned i = 0; i < inputVals.size(); ++i)
	{
		newInput.push_back(inputVals[i]);
	}
	for (unsigned i = newInput.size(); i < myNet.layers[0].size(); ++i)
	{
		newInput.push_back(0);
	}

	return newInput;
}