#pragma once

#include <iostream>
#include <cstdlib>
#include <cmath>

#include <ctime>


class Synapse
{
public:
	Synapse(double upperLim, double iWeight);

	double getWeight();
	void setWeight(double val);

private:
	double weight = 1.0;

	double randomDouble(double val1, double val2);

	double inhibWeight;
};