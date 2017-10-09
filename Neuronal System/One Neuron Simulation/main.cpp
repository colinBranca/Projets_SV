#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

#include "neuron.h"

int main(int argc, char* argv[]) {

  if(argc < 5) {
    return 1;
  }

  double current = atof(argv[1]);
  double totalTime = atof(argv[2]);
  double startTime = atof(argv[3]);
  double stopTime = atof(argv[4]);
  double i_ext = 0.0;

  std::ofstream outfile("membranePotentials.txt", std::ios::out);
  outfile << "Simulation with current ext_i = " << current << " during " << totalTime << "ms" << '\n';

  neuron n = neuron();
  n.setCurrent(i_ext);

  for(double t = 0.0; t <= totalTime; ++t) {
    if(i_ext == 0.0 && t >= startTime && t <= stopTime) {
      i_ext = current;
      n.setCurrent(i_ext);
    }
    else if(i_ext != 0.0 && (t < startTime || t > stopTime)) {
      i_ext = 0.0;
      n.setCurrent(i_ext);
    }
    n.updateState(t);

    outfile << n.getMembranePotentials() << '\n';
  }

  std::cout << "Simulations generated " << n.getSpikes() << " spikes" << '\n';
  std::cout << "at times:" << '\n';
  n.printSpikeTimes();

  outfile.close();
  return 0;
}
