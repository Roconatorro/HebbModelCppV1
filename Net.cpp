#include "Net.h"

Net::Net(const std::vector<unsigned>& layout, double aHThreshold, double hIncrease, double hDecrease, double iWeight)
{
    axonHillockThreshold = aHThreshold;
    hebbIncrease = hIncrease;
    hebbDecrease = hDecrease;
    inhibWeight = iWeight;

    m_layout = layout;

    unsigned numOfLayers = layout.size();

    for (unsigned layerI = 0; layerI < numOfLayers; ++layerI)
    {
        layers.push_back(std::vector<Neuron>()); //add layers
        inhibLayers.push_back(std::vector<NeuronInhibitory>()); //add inhibitory layers

        unsigned numOutputs = layerI == numOfLayers - 1 ? 0 : layout[layerI + 1];
        unsigned inhibNumOutputs = layout[layerI];

        for (unsigned neuronI = 0; neuronI < layout[layerI]; ++neuronI)
        {
            std::vector<unsigned> neuronPos = { layerI, neuronI };
            layers[layerI].push_back(Neuron(numOutputs, neuronPos, axonHillockThreshold, hebbIncrease, hebbDecrease));
            layers[layerI].back().normalize();

            inhibLayers[layerI].push_back(NeuronInhibitory(inhibNumOutputs, neuronPos, inhibWeight));
        }
    }
}

void Net::feedForward(std::vector<unsigned> inputVals)
{
    //stops program if false (need to be same number of inputVals as input Neurons)
    assert(inputVals.size() == layers[0].size());

    //assign input values to the outputs of input neurons
    for (unsigned i = 0; i < inputVals.size(); ++i) {
        layers[0][i].setOutputVal(inputVals[i]);
    }

    for (unsigned layerI = 1; layerI < layers.size(); ++layerI)
    {
        std::vector<Neuron>& prevLayer = layers[layerI - 1];

        for (unsigned neuronI = 0; neuronI < layers[layerI].size(); ++neuronI) {

            layers[layerI][neuronI].feedForward(prevLayer);

            if (layers[layerI][neuronI].getOutputVal() == 1)
            {
                inhibLayers[layerI][neuronI].feedForward(layers[layerI]);
            }
        }
    }

    //vectorNormalization
    for (unsigned layerI = 0; layerI < layers.size(); ++layerI)
    {
        for (unsigned neuronI = 0; neuronI < layers[layerI].size(); ++neuronI)
        {
            layers[layerI][neuronI].normalize();
        }
    }
}

void Net::displayNet()
{
    /*
    * Layer0
    * Neuron0: Output: 1
    * Synapse0: Weight: 1.5
    * Synapse1: Weight: 0.3
    * ...
    * Neuron1: Output: 0
    * Synapse0: Weight: 1.1
    * ...
    * Layer1
    */

    for (unsigned l = 0; l < layers.size(); ++l)
    {
        std::cout << "Layer" << l << '\n';

        for (unsigned n = 0; n < layers[l].size(); ++n)
        {
            std::cout << "-Neuron" << n << ": Output: " << layers[l][n].getOutputVal() << '\n';

            for (unsigned s = 0; s < layers[l][n].getOutputSynapses().size(); ++s)
            {
                double myWeight = layers[l][n].getOutputSynapses()[s].getWeight();
                std::cout << "--Synapse" << s << ": Weight: " << std::ceil(myWeight * 100.0) / 100.0 << '\n';
            }
        }
    }

    std::cout << "AxonHillockThreshold: " << axonHillockThreshold << '\n';
    std::cout << "HebbIncrease: " << hebbIncrease << '\n';
    std::cout << "HebbDecrease: " << hebbDecrease << '\n';
    std::cout << "InhibWeight: " << inhibWeight << '\n';
}

void Net::paintNet()
{
    Painter myPainter;

    myPainter.paintNet(m_layout, layers);

    p_allNeurons = myPainter.getAllNeurons();
    p_allSynapses = myPainter.getAllSynapses();

}

void Net::paintNet(sf::RenderWindow& window)
{
    Painter myPainter;
    myPainter.paintNet(m_layout, layers);

    p_allNeurons = myPainter.getAllNeurons();
    p_allSynapses = myPainter.getAllSynapses();

    window.clear();
    for (unsigned s = 0; s < p_allSynapses.size(); ++s)
    {
        window.draw(p_allSynapses[s]);
    }
    for (unsigned n = 0; n < p_allNeurons.size(); ++n)
    {
        window.draw(p_allNeurons[n]);
    }
    window.display();
}