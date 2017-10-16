#include <vector>
#include <math.h>

class neuron {

private:
  //constant parameters
  static constexpr double membraneResistance = 20.0;
  static constexpr double conductivity = 1.0;
  static constexpr double tau = membraneResistance * conductivity;
  static constexpr double tauRef = 2.0;
  static constexpr double V_threshold = 20.0;
  static constexpr double V_reset = 0.0;
  static constexpr double step = 0.1;
  const double potentialFactor = exp(-step/tau);
  const double currentFactor = membraneResistance * (1.0 - potentialFactor);
  static constexpr double delay = 1.5;
  static constexpr double J = 0.1;
  static constexpr int BUFFER_SIZE = 16; // delay/step + 1
  //variable parameters
  double membranePotential;
  int spikes;
  std::vector<int> timesOfSpikes;
  bool refractoring;
  double i_ext;
  int refractoryTime;
  std::string membranePotentials;
  std::vector<neuron> targets;
  double buffer[BUFFER_SIZE] = {};
  int bufferIndex = 0;

public:
  //constructor
  neuron();
  neuron(std::vector<neuron> tar);
  //get functions
  std::string getMembranePotentials();
  int getSpikes();
  std::vector<int> getTimesOfSpikes();
  std::vector<neuron> getTargets();
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
  void receive();

};
