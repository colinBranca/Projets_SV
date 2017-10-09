#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

#include "neuron.h"

int main(int argc, char* argv[]) {
  double current = atof(argv[2]);
  double totalTime = atof(argv[3]);
  double startTime = atof(argv[4]);
  double stopTime = atof(argv[5]);
  double i_ext = 0.0

  std::ofstream outfile("membranePotentials.txt", std::ios::out);
  outfile << "Simulation with current ext_i = " << current << " during " << totalTime << "ms" << '\n';

  neuron n = neuron();
  n.setCurrent(i_ext);

  for(double t = 0.0; t <= totalTime; ++t) {
    if(i_ext == 0.0 && t >= startTime && t <= stopTime) {
      i_ext = current;
      n.setCurrent(i_ext);
    }
    else if(i_ext =! 0.0 && (t < startTime || t > stopTime)) {
      i_ext = 0.0;
      n.setCurrent(i_ext);
    }
    n.update(t);

    double nV = n.getMembranePotential();
    outfile << t << " : "<< nV << '\n';
  }

  std::cout << "Simulations generated " << n.getSpikes() << " spikes" << '\n';
  std::cout << "at times:" << '\t';
  n.printSpikeTimes();

  outfile.close();
  return 0;
}
