#ifndef PORTMUX_GENERATOR_HPP
#define PORTMUX_GENERATOR_HPP
#include "yarpcodegenerator.hpp"
#include <boost/lexical_cast.hpp>

using namespace std;

class PortMuxGenerator : public YarpCodeGenerator {
  public:
    PortMuxGenerator(int numPorts, string ports, string outputName);
    ~PortMuxGenerator();

    int getNumPorts();

    string getPorts();

    string getOutputName();

    string generateCode();

    string extractPortFromString(int index);
    
  private:
    int numPorts_;
    string ports_;
    string outputName_;
};

#endif //PORTMUX_GENERATOR_HPP