#include "NeuronInhibitory.h"

NeuronInhibitory::NeuronInhibitory(unsigned& numOutputs, std::vector<unsigned>& pos, double iWeight)
{
	inhibWeight = iWeight;

	for (int s = 0; s < numOutputs; ++s)
	{
		outputSynapses.push_back(Synapse(-1, inhibWeight));
	}

	position = pos;
}

void NeuronInhibitory::feedForward(std::vector<Neuron>& targetLayer)
{

	for (unsigned n = 0; n < targetLayer.size(); ++n)
	{
		targetLayer[n].addPsp(outputSynapses[n].getWeight());
	}

}

void NeuronInhibitory::setOutputVal(double val)
{
	outputVal = val;
}
double NeuronInhibitory::getOutputVal()
{
	return outputVal;
}
std::vector<Synapse>& NeuronInhibitory::getOutputSynapses()
{
	return outputSynapses;
}
