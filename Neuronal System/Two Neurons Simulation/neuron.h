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
  static constexpr double J = 0.1;
  static constexpr int BUFFER_SIZE = 16; // delay/step + 1
  //variable parameters
  double membranePotential;
  int spikes;
  std::vector<double> timesOfSpikes;
  bool refractoring;
  double i_ext;
  int refractoryTime;
  std::vector<neuron*> targets;
  std::vector<int> buffer;
  int bufferIndex;
  int local_clock = 0;

public:
  //constructor
  neuron();
  neuron(std::vector<neuron> tar);
  //get functions
  double getMembranePotential();
  int getSpikes();
  std::vector<double> getTimesOfSpikes();
  std::vector<neuron*> getTargets();
  //update function
  bool updateState(int simTime);
  //return if the neuron is refractoring and update refractoring value if needed
  bool isRefractoring();
  //update refractoring
  void updateRefractoring();
  //print spike times
  void printSpikeTimes();
  //set i_ext
  void setCurrent(double i);
  //receive spike function
  void receive(int simTime);
  //add a target
  void addTarget(neuron* n);
  //add a spike
  void addSpike(int t);

};
