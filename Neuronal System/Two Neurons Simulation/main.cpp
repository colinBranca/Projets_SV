#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

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
  std::vector<neuron*> neurons;
  int stopCurrentTime = totalTime/2;
  double i_ext = current;

  //initialise neurons
  neuron n1 = neuron();
  neuron n2 = neuron();

  //add n2 into n1's targets
  n1.addTarget(&n2);

  //put n1 and n2 into neurons
  neurons.push_back(&n1);
  neurons.push_back(&n2);

  //set a new current in n1
  n1.setCurrent(i_ext);

  int simTime = 0;

  while(simTime <= totalTime) {
    if(i_ext == current && simTime > stopCurrentTime) {
      i_ext = 0.0;
      n1.setCurrent(i_ext);
    }

    for(size_t i = 0; i < neurons.size(); i ++) {
      neuron* n = neurons[i];
      if(n->updateState(simTime)) {
        std::vector<neuron*> targets = n->getTargets();
        for(size_t tar = 0; tar < targets.size(); ++tar) {
          targets[tar]->receive(simTime);
        }
      }
    }
    simTime += TIME_STEP;
  }

  //print neurons behaviours into files
  ofstream outfile1("neuron1.txt");
  ofstream outfile2("neuron2.txt");

	outfile1 << "Spikes in Neuron 1 occured at times:\n";
	for (vector<double>::iterator i = n1.getTimesOfSpikes().begin(); i != n1.getTimesOfSpikes().end(); ++i) {
		outfile1 << *i;
    outfile1 << "\n";
	}

  outfile2 << "Spikes in Neuron 2 occured at times:\n";
	for (vector<double>::iterator i = n2.getTimesOfSpikes().begin(); i != n2.getTimesOfSpikes().end(); ++i) {
		outfile2 << *i;
    outfile2 << "\n";
	}

	outfile1.close();
  outfile2.close();

  return 0;
}
