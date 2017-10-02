#pragma once

class neuron {

private:
  double membranePotential;
  int spikes;
  std::vector<double> timesOfSpikes;
  double membraneResistance;
  double conductivity;
  int tau;
  int tauRef;
  double step;
  double time;
  double potentialFactor;
  double spikeThreshold;
  bool refractoring;

public:
  //constructors
  neuron();
  neuron(double r, double c, int tr, double h, double v, double st);
  //get functions
  double getMembranePotential();
  int getSpikes();
  std::vector<double> getTimesOfSpikes();
  //update function
  void updateState(double t, double current);
  //return if the neuron is refractoring and update refractoring value if needed
  bool isRefractoring(double t);
  //print spike times
  void printSpikeTimes();

};
