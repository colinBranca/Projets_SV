#include <sstream>
#include <iostream>

using namespace std;

#include "neuron.h"

refractoringTime = 0;

//default constructor
neuron::neuron() {
  membranePotential = V_reset;
  refractoring = false;
}

//constructor
neuron::neuron(std::vector<neuron> tar) {
  membranePotential = V_reset;
  refractoring = false;
  targets.push_back(tar);
}

//set i_ext
void neuron::setCurrent(double i) {
  i_ext = i;
}

//return membrane potential
std::string neuron::getMembranePotentials() {
  return membranePotentials;
}

//return number of spikes
int neuron::getSpikes() {
  return spikes;
}

//return times of spikes
vector<int> neuron::getTimesOfSpikes() {
  return timesOfSpikes;
}

//return all neuron's targets
std::vector<neuron> neuron::getTargets() {
  return targets;
}

//update state of neuron
bool neuron::updateState(int simTime) {
  bool spike = false;

  updateRefractoring();

  if(membranePotential >= V_threshold) {
    membranePotential = V_reset;
    refractoring = true;
    refractoryTime = tauRef;
    timesOfSpikes.push_back(simTime);
    spikes ++;
    spike = true;
  }
  else if(refractoring) {
    membranePotential = V_reset;
  }
  else {
    membranePotential = potentialFactor * membranePotential + i_ext *  currentFactor + J * buffer[bufferIndex];
  }

  buffer[bufferIndex] = 0;
  bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;

  return spike;
}

//return if the neuron is refractoring and update refractoring value if needed
bool neuron::isRefractoring() {
  return refractoring;
}

//update refractoring state
void neuron::updateRefractoring() {
  refractoryTime -= step;
  if(refractoryTime <= 0.0) {
    refractoring = false;
  }
}

//print spike times
void neuron::printSpikeTimes() {
  if(spikes == 0) {
    return;
  }
  for(int i=0; i < spikes; ++i) {
    std::cout << 0.1*timesOfSpikes[i] << "  ;  ";
  }
  std::cout << 0.1*timesOfSpikes[spikes - 1] << '\n';
}

//receive spike function
void neuron::receive() {
  int inputIndex = (bufferIndex - 1) % BUFFER_SIZE;
  buffer[inputIndex] ++ ;
}
