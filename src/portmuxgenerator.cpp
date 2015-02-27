#include <iostream>
#include "portmuxgenerator.hpp"

using namespace std;

// Constructor and destructor
PortMuxGenerator::PortMuxGenerator(string ports) : YarpCodeGenerator::YarpCodeGenerator(ports) {
    cout << "Creating PortMuxGenerator." << endl;
}

PortMuxGenerator::~PortMuxGenerator() {
    cout << "Deleting PortMuxGenerator." << endl;
}

string PortMuxGenerator::generateCode() {
  return "+++ lots of code for port mux +++";
}