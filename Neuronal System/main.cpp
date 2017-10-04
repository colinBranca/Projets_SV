#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

#include "neuron.h"

int main(int argc, char* argv[]) {
  double conductivity = 1.0;
  int tau = 20;
  double resistance = tau/conductivity;
  double h = 0.1;
  double ext_i = atof(argv[1]);
  int tauRef = 2;
  double Vreset = 0.0;
  double Vthreshold = 20.0;
  double deltaTime = atof(argv[2]);

  std::ofstream outfile("membranePotentials.txt", std::ios::out);
  outfile << "Simulation with current ext_i = " << ext_i << " during " << 2*deltaTime << "ms" << '\n';

  neuron n = neuron(resistance, conductivity, tauRef, h, Vreset, Vthreshold);

  for(double i = 0.0f; i <= 2.0*deltaTime; i += h) {
    if(i >= deltaTime/2.0 && i<= 3.0*deltaTime/2.0) {
      n.updateState(i, ext_i);
    }
    else {
        n.updateState(i, 0.0);
    }
    double nV = n.getMembranePotential();
    outfile << i << " : "<< nV << '\n';
  }

  std::cout << "Simulations generated " << n.getSpikes() << " spikes" << '\n';
  std::cout << "at times:" << '\t';
  n.printSpikeTimes();

  outfile.close();
  return 0;
}
