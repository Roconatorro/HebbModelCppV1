#include "Neuron.h"

Neuron::Neuron(unsigned& numOutputs, std::vector<unsigned>& pos, double aHThreshold, double hIncrease, double hDecrease)
{
	for (int s = 0; s < numOutputs; ++s)
	{
		outputSynapses.push_back(Synapse(1, 1));
	}

	position = pos;
	axonHillockThreshold = aHThreshold;
	hebbIncrease = hIncrease;
	hebbDecrease = hDecrease;
}

void Neuron::feedForward(std::vector<Neuron>& prevLayer)
{

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		double prevOutputVal = prevLayer[n].getOutputVal();

		addPsp(prevOutputVal * prevLayer[n].getOutputSynapses()[position[1]].getWeight());

	}

	//summatedAP > axonHillockThreshold ? setOutputVal(1) : setOutputVal(0);
	if (summatedAP > axonHillockThreshold)
	{
		setOutputVal(1);
		axonHillockThreshold *= hillockIncrease;
	}
	else
	{
		setOutputVal(0);
		axonHillockThreshold *= hillockDecrease;
	}

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		calcHebbPlast(prevLayer, n);
	}

	summatedAP = 0;
}

void Neuron::calcHebbPlast(std::vector<Neuron>& prevLayer, unsigned neuronI)
{
	//when increase? both outputvals are 1
	if (prevLayer[neuronI].getOutputVal() == 1 && outputVal == 1)
	{
		double sW = prevLayer[neuronI].getOutputSynapses()[position[1]].getWeight();
		//1st is multiplication 2nd is addition. We`ll see what works
		//prevLayer[neuronI].getOutputSynapses()[position[1]].setWeight(sW * hebbIncrease);
		prevLayer[neuronI].getOutputSynapses()[position[1]].setWeight(sW + hebbIncrease);
	}
	prevLayer[neuronI].getOutputSynapses()[position[1]].setWeight(prevLayer[neuronI].getOutputSynapses()[position[1]].getWeight() * hebbDecrease);
}


void Neuron::normalize()
{
	magnitude = 0;
	for (unsigned s = 0; s < outputSynapses.size(); ++s)
	{
		magnitude += pow((outputSynapses[s].getWeight()), 2);
	}

	for (unsigned s = 0; s < outputSynapses.size(); ++s)
	{
		double thisWeight = outputSynapses[s].getWeight();

		outputSynapses[s].setWeight(thisWeight / sqrt(magnitude));
	}
}


void Neuron::setOutputVal(double val)
{
	outputVal = val;
}
double Neuron::getOutputVal()
{
	return outputVal;
}
std::vector<Synapse>& Neuron::getOutputSynapses()
{
	return outputSynapses;
}

void Neuron::addPsp(double val)
{
	summatedAP += val;
}