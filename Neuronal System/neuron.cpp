#pragma once

#include <sstream>
#include <iostream>
#include <math.h>

using namespace std;

#include "neuron.h"

//default constructor
neuron::neuron() {
  membranePotential = 0.0;
  spikes = 0;
  membraneResistance = 0.0;
  conductivity = 0.0;
  tau = 0;
  tauRef = 0;
  step = 0.0;
  potentialFactor = 0.0;
  spikeTime = 0.0;
  spikeThreshold = 0.0;
  refractoring = false;
}

//constructor
neuron::neuron(double r, double c, int tr, double h, double v, double st) {
  membranePotential = v;
  spikes = 0;
  membraneResistance = r;
  conductivity = c;
  tau = (int) r * c;
  tauRef = tr;
  step = h;
  potentialFactor = exp(-step / tau);
  spikeTime = 0;
  spikeThreshold = st;
  refractoring = false;
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
void neuron::updateState(double t, double current) {

  if(membranePotential >= spikeThreshold) {
    membranePotential = 0.0;
    refractoring = true;
    spikeTime = t;
    timesOfSpikes.push_back(t);
    spikes ++;
  }
  else if(isRefractoring(t)) {
    membranePotential = 0.0;
  }
  else {
    // double T = t - currentTime;
    // double n = T/step;
    // double tmp_potentialFactor = pow(potentialFactor, n);

    // membranePotential = tmp_potentialFactor * membranePotential + current *  membraneResistance * (1 - tmp_potentialFactor);
    membranePotential = potentialFactor * membranePotential + current *  membraneResistance * (1 - potentialFactor);

  }
}

//return if the neuron is refractoring and update refractoring value if needed
bool neuron::isRefractoring(double t) {
  if(t - spikeTime >= tauRef) {
    refractoring = false;
  }
  return refractoring;
}

//print spike times
void neuron::printSpikeTimes() {
  for(size_t i=0; i < timesOfSpikes.size() - 1; i++) {
    std::cout << timesOfSpikes[i] << "  ;  ";
  }
  std::cout << timesOfSpikes[timesOfSpikes.size() - 1] << '\n';
}
