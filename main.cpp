#pragma once

#include <sstream>
#include <iostream>
#include <math.h>

using namespace std;

#include "neuron.h"

int main() {
  double conductivity = 250.0;
  int tau = 10;
  double resistance = tau/conductivity;
  double h = 0.1;
  double current = 0.0;
  int tauRef = 2;
  double Vreset = -70.0;
  double Vthreshold = -55.0;
  double deltaTime = 0.0;

  std::cout << "insert current you want to apply:" << '\n';
  std::cin >> current;
  std::cout << "insert duration of the current application" << '\n';
  std::cin >> deltaTime;


  neuron n = neuron(resistance, conductivity, tauRef, h, Vreset, Vthreshold);

  for(double i = 0.0f; i <= deltaTime; i += h) {
    n.updateState(i, current);
  }

  std::cout << "Simulations generated " << n.getSpikes() << " spikes" << '\n';
  std::cout << "at times:" << '\t';
  n.printSpikeTimes();

  return 0;
}
