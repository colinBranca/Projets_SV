/**
 * @file main.cpp
 * @brief neuronal system simulation
 *
 * @author Colin Branca
 * @date November 2017
 */

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
  if(argc < 2) {
    return 1;
  }

  //set arguments
  double current = atof(argv[1]); /**< current*/
  int totalTime = atof(argv[2]); /**< total simulation time */
  int stopCurrentTime = totalTime/2; /**< time the current is stoped*/
  double i_ext = current; /**< external current */
  int Ne = 10000; /**< number of excitatory neurons */
  int Ni = Ne/4; /**< number of inhibitory neurons */
  int epsilon = 10; /**< epsilon */
  int Ce = Ne/epsilon; /**< number of  connections to excitatory neurons */
  int Ci = Ni/epsilon; /**< number of connections to inhibitory neurons */
  double Je = 0.1; /**< current from excitatory neurons */
  double Ji = 0.5; /**< current from inhibitory neurons */

  ofstream outfile("neurons.csv"); /**< outfile where all spikes will be printed*/

  /**< initialise excitatory neurons */
  std::vector<neuron*> excitatoryNeurons;
  for(int i = 0; i < Ne; ++i) {
    neuron* n = new neuron();
    excitatoryNeurons.push_back(n);
  }

  /**< initialise inhibitory neurons */
  std::vector<neuron*> inhibitoryNeurons;
  for(int i = 0; i < Ni; ++i) {
    neuron* n = new neuron();
    inhibitoryNeurons.push_back(n);

  }

  /**<list of all neurons */
  std::vector<neuron*> neurons = excitatoryNeurons;
  neurons.insert(neurons.end(), inhibitoryNeurons.begin(), inhibitoryNeurons.end());

  /**<initialise neurons connections */
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

  std::default_random_engine gen; /**<random number generator */
  std::poisson_distribution<int> distribution(2); /**<poisson disrtibution */

  /**<simulation */
  while(simTime <= totalTime) {
    // if(i_ext == current && simTime > stopCurrentTime) {
    //   i_ext = 0.0;
    //   n1.setCurrent(i_ext);
    // }

    for(size_t i = 0; i < neurons.size(); ++i) {
      double J = (((int) i < Ne) ? Je : Ji);
      neuron* n = neurons[i];
      n->receiveFromExt(Je * (double)distribution(gen));
      if(n->updateState(simTime)) {
        outfile << i << "," << simTime << "\n";
        std::vector<neuron*> targets = n->getTargets();
        for(size_t tar = 0; tar < targets.size(); ++tar) {
          targets[tar]->receive(simTime, J);
        }
      }
    }
    simTime += TIME_STEP;
  }
  outfile.close();

  return 0;
}
