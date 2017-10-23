#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

#include "neuron.h"


//default constructor
neuron::neuron() {
  membranePotential = V_reset;
  refractoring = false;
  spikes = 0;
  timesOfSpikes = {};
  refractoryTime = 0;
  targets = {};
  buffer.assign(BUFFER_SIZE, 0);
  i_ext = 0.0;
}

//set i_ext
void neuron::setCurrent(double i) {
  i_ext = i;
}

//add a target
void neuron::addTarget(neuron* n) {
  targets.push_back(n);
}

//return membrane potential
double neuron::getMembranePotential() {
  return membranePotential;
}

//return number of spikes
int neuron::getSpikes() {
  return spikes;
}

//return times of spikes
vector<double> neuron::getTimesOfSpikes() {
  return timesOfSpikes;
}

//return all neuron's targets
std::vector<neuron*> neuron::getTargets() {
  return targets;
}

//update state of neuron
bool neuron::updateState(int simTime) {
  bool spike = false;

  if(refractoring) {
    membranePotential = V_reset;
    updateRefractoring();
  }
  else if(membranePotential >= V_threshold) {
    addSpike(simTime);
    spike = true;
  }
  else {
    membranePotential = potentialFactor * membranePotential + i_ext *  currentFactor + buffer[bufferIndex];
  }
  buffer[bufferIndex] = 0;
  bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
  local_clock ++;
  return spike;
}

//return if the neuron is refractoring and update refractoring value if needed
bool neuron::isRefractoring() {
  return refractoring;
}

//update refractoring state
void neuron::updateRefractoring() {
  refractoryTime --;
  if(refractoryTime <= 0) {
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
void neuron::receive(int simTime, double J) {
  int inputIndex = (local_clock - simTime + bufferIndex - 1) % BUFFER_SIZE;
  buffer[inputIndex] += J;
}

//receive spike from external system
void neuron::receiveFromExt(double J) {
  buffer[bufferIndex] += J;
}

//add a spike
void neuron::addSpike(int t) {
  membranePotential = V_reset;
  refractoring = true;
  refractoryTime = tauRef;
  double tmp = (double)(t) * step;
  timesOfSpikes.push_back(tmp);
  spikes ++;
}
