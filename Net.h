#pragma once
#include <iostream>
#include <vector>
#include <assert.h>

#include <SFML/Graphics.hpp>

#include "Neuron.h"
#include "NeuronInhibitory.h"
#include "Painter.h"

class Net
{
public:
	Net(const std::vector<unsigned>& layout, double aHThreshold, double hIncrease, double hDecrease, double iWeight);

	void feedForward(std::vector<unsigned> inputVals);

	void displayNet();
	void paintNet();
	void paintNet(sf::RenderWindow& window);

	std::vector<std::vector<Neuron>> layers;
	std::vector<std::vector<NeuronInhibitory>> inhibLayers;

	double getAxonHillockThreshold() { return axonHillockThreshold; }
	double getHebbIncrease() { return hebbIncrease; }
	double getHebbDecrease() { return hebbDecrease; }
	double getInhibWeight() { return inhibWeight; }

	std::vector<sf::CircleShape> getAllNeurons() { return p_allNeurons; }
	std::vector<sf::ConvexShape> getAllSynapses() { return p_allSynapses; }

	std::vector<unsigned> getLayout() { return m_layout; }

private:
	double axonHillockThreshold;
	double hebbIncrease;
	double hebbDecrease;
	double inhibWeight;

	std::vector<unsigned> m_layout;

	std::vector<sf::CircleShape> p_allNeurons;
	std::vector<sf::ConvexShape> p_allSynapses;
};

