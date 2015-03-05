#ifndef PORTMUX_GENERATOR_HPP
#define PORTMUX_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

class PortMuxGenerator : public YarpCodeGenerator {
  public:
    PortMuxGenerator(int numPorts, std::string ports, std::string outputName);
    ~PortMuxGenerator();

    int getNumPorts();

    std::string getPorts();

    std::string getOutputName();

    std::string generateCode();
    
  private:
    int numPorts_;
    std::string ports_;
    std::string outputName_;

    std::string extractPortFromString(int index);
};

#endif //PORTMUX_GENERATOR_HPP