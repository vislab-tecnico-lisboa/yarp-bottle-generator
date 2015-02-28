#ifndef PORTMUX_GENERATOR_HPP
#define PORTMUX_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

using namespace std;

class PortMuxGenerator : public YarpCodeGenerator {
  public:
    PortMuxGenerator(int numPorts, string ports);
    ~PortMuxGenerator();

    int getNumPorts();

    string getPorts();

    string generateCode();
  private:
    int numPorts_;
    string ports_;
};

#endif //PORTMUX_GENERATOR_HPP