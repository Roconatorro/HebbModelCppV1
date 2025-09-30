#include "Painter.h"

void Painter::paintNet(std::vector<unsigned> layout, std::vector<std::vector<Neuron>>& layers)
{
    for (unsigned l = 0; l < layout.size(); ++l)
    {
        for (unsigned n = 0; n < layout[l]; ++n)
        {
            allNeurons.push_back(sf::CircleShape(neuronRadius));

            if (layers[l][n].getOutputVal() == 1)
            {
                allNeurons.back().setFillColor(firingColor);
            }
            else
            {
                allNeurons.back().setFillColor(restingColor);
            }

            allNeurons.back().setOutlineThickness(-0.25f * neuronRadius);
            allNeurons.back().setOutlineColor(sf::Color(0, 0, 250));

            float y = n * ySpacing;
            allNeurons.back().setPosition({ x, y });

            if (l == layout.size() - 1)
                continue;

            for (unsigned s = 0; s < layout[l + 1]; ++s)
            {
                allSynapses.push_back(sf::ConvexShape());

                allSynapses.back().setPointCount(3);

                allSynapses.back().setPoint(0, { x + neuronRadius , y + (0.8f * neuronRadius) });
                allSynapses.back().setPoint(1, { x + xSpacing, (s * ySpacing) + neuronRadius });
                allSynapses.back().setPoint(2, { x + neuronRadius , y + (1.2f * neuronRadius) });

                double synapseWeight = layers[l][n].getOutputSynapses()[s].getWeight();
                if (synapseWeight < 1)
                {
                    allSynapses.back().setFillColor(sf::Color(250 * synapseWeight, 250 * synapseWeight, 250 * synapseWeight));
                }
                else
                {
                    allSynapses.back().setFillColor(sf::Color(250, 250, 250));
                }

            }
        }
        x += xSpacing;
    }
}

void Painter::render()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Neuron window");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (event->is<sf::Event::Resized>())
            {
                //update view
                sf::View view(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(window.getSize())));
                window.setView(view);
            }
        }

        window.clear();

        for (unsigned s = 0; s < allSynapses.size(); ++s)
        {
            window.draw(allSynapses[s]);
        }
        for (unsigned n = 0; n < allNeurons.size(); ++n)
        {
            window.draw(allNeurons[n]);
        }

        window.display();
    }
}