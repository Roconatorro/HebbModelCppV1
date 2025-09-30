#include "Synapse.h"

Synapse::Synapse(double upperLim, double iWeight)
{
	if (upperLim < 0)
	{
		inhibWeight = iWeight;
		weight = inhibWeight;
	}
	else
	{
		//set weight to random (between +1 and -1 -> EPSP or IPSP)
		weight = randomDouble(0.0, upperLim);

		//useless, change later
		inhibWeight = 0;
	}
}

double Synapse::getWeight()
{
	return weight;
}
void Synapse::setWeight(double val)
{
	weight = val;
}

double Synapse::randomDouble(double val1, double val2)
{
	return val1 + (val2 - val1) * (double)rand() / RAND_MAX;
}