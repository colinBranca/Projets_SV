#pragma once

#include <vector>

class neuron {

private:
  //constant parameters
  const double membraneResistance = 20.0;
  const double conductivity = 1.0;
  const double tau = 20;
  const double tauRef = 2.0;
  const double V_threshold = 20.0;
  const double V_reset = 0.0;
  const double step = 0.1;
  const double potentialFactor = exp(-step/tau);
  const double currentFactor = membraneResistance * (1.0 - potentialFactor);
  //variable parameters
  double membranePotential;
  int spikes;
  std::vector<double> timesOfSpikes;
  bool refractoring;
  double intern_clock;
  double i_ext;

public:
  //constructor
  neuron();
  //get functions
  double getMembranePotential();
  int getSpikes();
  std::vector<double> getTimesOfSpikes();
  //update function
  void updateState(double stopTime);
  //return if the neuron is refractoring and update refractoring value if needed
  bool isRefractoring();
  //update refractoring
  void updateRefractoring();
  //print spike times
  void printSpikeTimes();
  //set i_ext
  void setCurrent(double i);

};
