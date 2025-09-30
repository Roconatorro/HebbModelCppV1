#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Neuron.h"


class Painter
{
public:
	void paintNet(std::vector<unsigned> layout, std::vector<std::vector<Neuron>>& layers);
	void render();

	std::vector<sf::CircleShape> getAllNeurons() { return allNeurons; }
	std::vector<sf::ConvexShape> getAllSynapses() { return allSynapses; }

private:
	std::vector<sf::CircleShape> allNeurons;
	std::vector<sf::ConvexShape> allSynapses;

	float x = 0.f;
	float y = 0.f;
	float neuronRadius = 20.f;
	float xSpacing = 100.f;
	float ySpacing = 50.f;

	sf::Color firingColor = sf::Color(250, 250, 250);
	sf::Color restingColor = sf::Color(50, 50, 50);

};