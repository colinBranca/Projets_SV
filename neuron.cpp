/**
 * @file neuron.cpp
 * @brief neuron class
 *
 * @author Colin Branca
 * @date November 2017
 */


#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

#include "neuron.h"


/**
* @brief neuron constructor
*/
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

/**
* @brief set I_ext current
*/
void neuron::setCurrent(double i) {
  i_ext = i;
}

/**
* @brief add a target to the neuron
* @param n target neuron
*/
void neuron::addTarget(neuron* n) {
  if(n == null) {
    throw "add no neuron!";
  }
  targets.push_back(n);
}

/**
* @brief get the membrane potential of the neuron
* @return the membrane potential
*/
double neuron::getMembranePotential() {
  return membranePotential;
}

/**
* @brief get the number of times the neuron spiked
* @return number of spikes
*/
int neuron::getSpikes() {
  return spikes;
}

/**
* @brief get times the neuron spiked
* @return spike times
*/
vector<double> neuron::getTimesOfSpikes() {
  return timesOfSpikes;
}

/**
* @brief get the neuron's targets
* @return targets
*/
std::vector<neuron*> neuron::getTargets() {
  return targets;
}

/**
* @brief update neuron's state
* @param simTime simlutation time
* @return true if the neuron spiked, false otherwise
*/
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

/**
* @brief test if the neuron is refractoring
* @return true if the neuron is refractoring, false otherwise
*/
bool neuron::isRefractoring() {
  return refractoring;
}

/**
* @brief update the refractory state of the neuron
*/
void neuron::updateRefractoring() {
  refractoryTime --;
  if(refractoryTime <= 0) {
    refractoring = false;
  }
}

/**
* @brief print the spike times
*/
void neuron::printSpikeTimes() {
  if(spikes == 0) {
    return;
  }
  for(int i=0; i < spikes; ++i) {
    std::cout << 0.1*timesOfSpikes[i] << "  ;  ";
  }
  std::cout << 0.1*timesOfSpikes[spikes - 1] << '\n';
}

/**
* @brief receive spike from other neuron
* @param simTime time the other neuron spiked
* @param J current given by the spike
*/
void neuron::receive(int simTime, double J) {
  if(simTime < local_clock) {
    throw "Simulation Time is not correct!";
  } else if(J < 0) {
    throw "Negative Current!";
  }
  int inputIndex = (local_clock - simTime + bufferIndex - 1) % BUFFER_SIZE;
  buffer[inputIndex] += J;
}

/**
* @brief receive spike from external system
* @param J current given by the spikes
*/
void neuron::receiveFromExt(double J) {
  if(J < 0) {
    throw "Negative Current!";
  }
  buffer[bufferIndex] += J;
}

/**
* @brief add a spike to the neuron
* @param t spike time
*/
void neuron::addSpike(int t) {
  membranePotential = V_reset;
  refractoring = true;
  refractoryTime = tauRef;
  double tmp = (double)(t) * step;
  timesOfSpikes.push_back(tmp);
  spikes ++;
}
