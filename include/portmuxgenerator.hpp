#ifndef PORTMUX_GENERATOR_HPP
#define PORTMUX_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"

class PortMuxGenerator : public YarpCodeGenerator {
  public:
    PortMuxGenerator(int numMuxes, std::string outputName);
    ~PortMuxGenerator();

    int getNumMuxes();

    std::string getOutputName();

    std::vector<int> getNumPorts();

    std::vector<std::string> getPorts();

    void addMuxNumPorts(int numPorts);

    void addMuxPorts(std::string ports);

    int getMuxNumPorts(int muxIndex);

    std::string getMuxPorts(int muxIndex);

    std::string generateCode();
    
  private:
    int numMuxes_;
    std::string outputName_;
    std::vector<int> numPorts_;
    std::vector<std::string> ports_;

    std::string extractPortFromString(int muxIndex, int portIndex);
};

#endif //PORTMUX_GENERATOR_HPP