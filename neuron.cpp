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
  currentFactor = 0.0;
  time = 0.0;
  spikeThreshold = 0.0;
  refractoring = False;
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
  time = 0;
  spikeThreshold = st;
  refractoring = False;
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
  if(isRefractoring(t)) {
    membranePotential = 0.0;
  }
  else {
    double T = t - time;
    double n = T/step;
    time += t;
    double tmp_potentialFactor = pow(potentialFactor, n);

    membranePotential = tmp_potentialFactor * membranePotential + current *  membraneResistance * (1 - tmp_potentialFactor);

    if(membranePotential >= spikeThreshold) {
      membranePotential = 0.0;
      refractoring = True;
      timesOfSpikes.push_back(time);
      spikes ++;
    }
  }
}

//return if the neuron is refractoring and update refractoring value if needed
bool isRefractoring(double t) {
  if(t - time >= tauRef) {
    refractoring = False;
  }
  return refractoring;
}

//print spike times
void printSpikeTimes() {
  for(int i=0; i < timesOfSpikes.size(); i++) {
    std::cout << timesOfSpikes << '  ;  ';
  }
}
