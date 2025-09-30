#pragma once

#include <iostream>
#include <vector>

#include "Synapse.h"
#include "Neuron.h"

class NeuronInhibitory
{
public:
	NeuronInhibitory(unsigned& numOutputs, std::vector<unsigned>& pos, double iWeight);

	void feedForward(std::vector<Neuron>& targetLayer);

	void setOutputVal(double val);
	double getOutputVal();
	std::vector<Synapse>& getOutputSynapses();

private:
	std::vector<unsigned> position;
	double inhibWeight;

	std::vector<Synapse> outputSynapses;
	double outputVal;
};