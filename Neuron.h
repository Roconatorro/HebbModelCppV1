#pragma once

#include <iostream>
#include <vector>

#include "Synapse.h"

class Neuron
{
public:
	Neuron(unsigned& numOutputs, std::vector<unsigned>& pos, double aHThreshold, double hIncrease, double hDecrease);

	void feedForward(std::vector<Neuron>& prevLayer);
	void calcHebbPlast(std::vector<Neuron>& prevLayer, unsigned neuronI);

	void addPsp(double val);
	void normalize();

	void setOutputVal(double val);
	double getOutputVal();
	std::vector<Synapse>& getOutputSynapses();

private:
	std::vector<unsigned> position;

	double summatedAP = 0;

	std::vector<Synapse> outputSynapses;
	double outputVal;

	double magnitude = 0;

	double axonHillockThreshold;
	double hillockIncrease = 1.1;
	double hillockDecrease = 0.9;
	double hebbIncrease;
	double hebbDecrease;
};