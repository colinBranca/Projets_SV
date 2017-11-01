/**
 * @file neuron.h
 * @brief neuron class
 *
 * @author Colin Branca
 * @date November 2017
 */

#include <vector>
#include <math.h>

class neuron {

private:
  //constant parameters
  static constexpr double membraneResistance = 20.0;
  static constexpr double conductivity = 1.0;
  static constexpr double tau = membraneResistance * conductivity;
  static constexpr int tauRef = 20;
  static constexpr double V_threshold = 20.0;
  static constexpr double V_reset = 0.0;
  static constexpr double step = 0.1;
  double potentialFactor = exp(-step/tau);
  double currentFactor = membraneResistance * (1.0 - potentialFactor);
  static constexpr double delay = 1.5;
  static constexpr int BUFFER_SIZE = 16; // delay/step + 1
  //variable parameters
  double membranePotential;
  int spikes;
  std::vector<double> timesOfSpikes;
  bool refractoring;
  double i_ext;
  int refractoryTime;
  std::vector<neuron*> targets;
  std::vector<double> buffer;
  int bufferIndex = 0;
  int local_clock = 0;

public:
  /**
  * @brief neuron constructor
  */
  neuron();
  /**
  * @brief get the membrane potential of the neuron
  * @return the membrane potential
  */
  double getMembranePotential();
  /**
  * @brief get the number of times the neuron spiked
  * @return number of spikes
  */
  int getSpikes();
  /**
  * @brief get times the neuron spiked
  * @return spike times
  */
  std::vector<double> getTimesOfSpikes();
  /**
  * @brief get the neuron's targets
  * @return targets
  */
  std::vector<neuron*> getTargets();
  /**
  * @brief update neuron's state
  * @param simTime simlutation time
  * @return true if the neuron spiked, false otherwise
  */
  bool updateState(int simTime);
  /**
  * @brief test if the neuron is refractoring
  * @return true if the neuron is refractoring, false otherwise
  */
  bool isRefractoring();
  /**
  * @brief update the refractory state of the neuron
  */
  void updateRefractoring();
  /**
  * @brief print the spike times
  */
  void printSpikeTimes();
  /**
  * @brief set I_ext current
  */
  void setCurrent(double i);
  /**
  * @brief receive spike from other neuron
  * @param simTime time the other neuron spiked
  * @param J current given by the spike
  */
  void receive(int simTime, double J);
  /**
  * @brief receive spike from external system
  * @param J current given by the spikes
  */
  void receiveFromExt(double J);
  /**
  * @brief add a target to the neuron
  * @param n target neuron
  */
  void addTarget(neuron* n);
  /**
  * @brief add a spike to the neuron
  * @param t spike time
  */
  void addSpike(int t);

};
