#ifndef PORTMUX_GENERATOR_HPP
#define PORTMUX_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

using namespace std;

class PortMuxGenerator : public YarpCodeGenerator {
  public:
    PortMuxGenerator(string ports);
    ~PortMuxGenerator();

    string generateCode();
};

#endif //PORTMUX_GENERATOR_HPP