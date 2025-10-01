# HebbModelC++V1

Requires SFML installed on your machine

Simple C++ implementation of Neural Network using Hebbian learning Rules. 
It gets stabilized by:
- hidden layers of inhibitory Neurons
- a variable Axonhillock Threshold
- vector Normalization

While neither powerfull, nor practical, this simple implementation serves as a sandbox. Adjust Variables in the source code to see their effect on the Network.

Once Running, the Console will ask you to "Select Input". This is where you decide which Input Neurons you want to activate. Inputting "1" would fire the first Neuron. "01" the second Neuron. "001" the third and "111" the first three. MIND: By default, the input layer only consists of 5 Neurons, so Input like "00000001" would be nonsenical.

After that, you select how many times you want to run the input, i.e. feed forward.
