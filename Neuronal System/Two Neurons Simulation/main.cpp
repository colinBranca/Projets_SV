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

  if(argc < 5) {
    return 1;
  }

  double current = atof(argv[1]);
  int totalTime = atof(argv[2]);
  int startTime = atof(argv[3]);
  int stopTime = atof(argv[4]);
  double i_ext = 0.0;
  std::vector<neuron> neurons;

  //n2 has no targets
  std::vector<neuron> targets;
  neuron n2 = neuron(targets);
  //n1 has only one target: n2
  //we use only one vector to save memory
  targets.push_back(n2);
  neuron n1 = neuron(targets);

  neurons.push_back(n1);
  neurons.push_back(n2);

  n1.setCurrent(i_ext);

  for(int t = 0; t <= totalTime; t += TIME_STEP) {
    if(i_ext == 0.0 && t >= startTime && t <= stopTime) {
      i_ext = current;
      n1.setCurrent(i_ext);
    }
    else if(i_ext != 0.0 && (t < startTime || t > stopTime)) {
      i_ext = 0.0;
      n1.setCurrent(i_ext);
    }
    for(vector<neuron>::iterator n = neurons.begin(); n != neurons.end(); ++n) {
      if(n->updateState(t)) {
        std::vector<neuron> targets = n->getTargets();
        for(size_t tar = 0; tar < targets.size(); ++tar) {
          targets[tar].receive();
        }
      }
    }
  }

  //print neurons behaviours into files
  ofstream outfile1("neuron1.txt");
  ofstream outfile2("neuron2.txt");
	outfile1 << "Spikes in Neuron 1 occured at times:\n";
	for (vector<double>::const_iterator i = n1.getTimesOfSpikes().begin(); i != n1.getTimesOfSpikes().end(); ++i) {
		outfile1 << *i;
	}
  outfile1 << "Spikes in Neuron 2 occured at times:\n";
	for (vector<double>::const_iterator i = n2.getTimesOfSpikes().begin(); i != n2.getTimesOfSpikes().end(); ++i) {
		outfile2 << *i;
	}
	outfile1.close();
  outfile2.close();

  return 0;
}
