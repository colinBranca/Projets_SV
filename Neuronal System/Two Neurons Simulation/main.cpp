#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <random>

using namespace std;

#include "neuron.h"

// in the main file we have time in int to take less memory
// to have "real time" we have to multiply by 0.1
// so TIME_STEP = 1 means TIME_STEP = 0.1ms
const int TIME_STEP = 1;

int main(int argc, char* argv[]) {
  if(argc < 3) {
    return 1;
  }

  //set arguments
  double current = atof(argv[1]);
  int totalTime = atof(argv[2]);
  int stopCurrentTime = totalTime/2;
  double i_ext = current;
  int Ne = 10000;
  int Ni = Ne/4;
  int epsilon = 10;
  int Ce = Ne/epsilon;
  int Ci = Ni/epsilon;
  double Je = 0.1;
  double Ji = 0.5;

  //initialise excitatory neurons
  std::vector<neuron*> excitatoryNeurons;
  for(int i = 0; i < Ne; ++i) {
    neuron n = neuron();
    excitatoryNeurons.push_back(&n);
  }

  //initialise inhibitory neurons
  std::vector<neuron*> inhibitoryNeurons;
  for(int i = 0; i < Ni; ++i) {
    neuron n = neuron();
    inhibitoryNeurons.push_back(&n);
  }

  //list of all neurons
  std::vector<neuron*> neurons = excitatoryNeurons;
  neurons.insert(neurons.end(), inhibitoryNeurons.begin(), inhibitoryNeurons.end());

  //initialise neurons connections
  for(size_t i = 0; i < neurons.size(); ++i) {
    for(int j = 0; j < Ce; ++j) {
      int connectionIndex = rand() % Ne;
      excitatoryNeurons[connectionIndex]->addTarget(neurons[i]);
    }
    for(int j = 0; j < Ci; ++j) {
      int connectionIndex = rand() % Ni;
      inhibitoryNeurons[connectionIndex]->addTarget(neurons[i]);
    }
  }

  int simTime = 0;

  std::default_random_engine gen;
  std::poisson_distribution<int> distribution(10);

  while(simTime <= totalTime) {
    // if(i_ext == current && simTime > stopCurrentTime) {
    //   i_ext = 0.0;
    //   n1.setCurrent(i_ext);
    // }

    for(size_t i = 0; i < neurons.size(); i ++) {
      double J = (((int) i < Ne) ? Je : Ji);
      neuron* n = neurons[i];
      n->receiveFromExt(Je * (double)distribution(gen));
      if(n->updateState(simTime)) {
        std::vector<neuron*> targets = n->getTargets();
        for(size_t tar = 0; tar < targets.size(); ++tar) {
          targets[tar]->receive(simTime, J);
        }
      }
    }
    simTime += TIME_STEP;
  }

  // //print neurons behaviours into files
  // ofstream outfile1("neuron1.txt");
  // ofstream outfile2("neuron2.txt");
  //
	// outfile1 << "Spikes in Neuron 1 occured at times:\n";
	// for (vector<double>::iterator i = n1.getTimesOfSpikes().begin(); i != n1.getTimesOfSpikes().end(); ++i) {
	// 	outfile1 << *i;
  //   outfile1 << "\n";
	// }
  //
  // outfile2 << "Spikes in Neuron 2 occured at times:\n";
	// for (vector<double>::iterator i = n2.getTimesOfSpikes().begin(); i != n2.getTimesOfSpikes().end(); ++i) {
	// 	outfile2 << *i;
  //   outfile2 << "\n";
	// }
  //
	// outfile1.close();
  // outfile2.close();

  return 0;
}
