#include <sstream>
#include <iostream>
#include <math.h>

using namespace std;

#include "neuron.h"

double refractoringTime = 0.0;
std::ostringstream oss;

//default constructor
neuron::neuron() {
  membranePotential = V_reset;
  refractoring = false;
  intern_clock = 0.0;
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
vector<double> neuron::getTimesOfSpikes() {
  return timesOfSpikes;
}

//update state of neuron
void neuron::updateState(double stopTime) {

  while(intern_clock <= stopTime) {

    updateRefractoring();

    if(membranePotential >= V_threshold) {
      membranePotential = V_reset;
      refractoring = true;
      refractoryTime = tauRef;
      timesOfSpikes.push_back(intern_clock);
      spikes ++;
    }
    else if(refractoring) {
      membranePotential = V_reset;
    }
    else {
      membranePotential = potentialFactor * membranePotential + i_ext *  currentFactor;
    }

    oss << intern_clock << " : " << membranePotential + '\n';

    intern_clock += step;
  }
  membranePotentials.append(oss.str());
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
    std::cout << timesOfSpikes[i] << "  ;  ";
  }
  std::cout << timesOfSpikes[spikes - 1] << '\n';
}
