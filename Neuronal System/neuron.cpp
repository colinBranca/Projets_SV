#pragma once

#include <sstream>
#include <iostream>
#include <math.h>

using namespace std;

#include "neuron.h"

double refractoringTime = 0.0;

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

//update state of neuron
void neuron::updateState(double stopTime) {

  while(intern_clock <= stopTime) {

    updateRefractoring();

    if(membranePotential >= V_threshold) {
      membranePotential = V_reset;
      updateRefractoring();
      timesOfSpikes.push_back(intern_clock);
      spikes ++;
    }
    else if(refractoring) {
      membranePotential = V_reset;
    }
    else {
      membranePotential = potentialFactor * membranePotential + i_ext *  currentFactor;
    }
    intern_clock += step;
  }
}

//return if the neuron is refractoring and update refractoring value if needed
bool neuron::isRefractoring() {
  return refractoring;
}

//update refractoring state
void neuron::updateRefractoring() {
  if(!refractoring) {
    refractoring = true;
    refractoringTime = tauRef;
  }
  else {
    refractoringTime -= step;
    if(refractoringTime <= 0.0) {
      refractoring = false;
    }
  }
}

//print spike times
void neuron::printSpikeTimes() {
  for(size_t i=0; i < timesOfSpikes.size() - 1; i++) {
    std::cout << timesOfSpikes[i] << "  ;  ";
  }
  std::cout << timesOfSpikes[timesOfSpikes.size() - 1] << '\n';
}
