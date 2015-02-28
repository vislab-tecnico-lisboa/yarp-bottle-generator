#include <iostream>
#include <string>
#include "portmuxgenerator.hpp"
#include <boost/lexical_cast.hpp>

using namespace std;

// Constructor and destructor
PortMuxGenerator::PortMuxGenerator(int numPorts, string ports) : numPorts_(numPorts), ports_(ports) {
  cout << "Creating PortMuxGenerator." << endl;
}

PortMuxGenerator::~PortMuxGenerator() {
  cout << "Deleting PortMuxGenerator." << endl;
}

int PortMuxGenerator::getNumPorts() {
  return numPorts_;
}

string PortMuxGenerator::getPorts() {
  return ports_;
}

string PortMuxGenerator::generateCode() {
  string code;

  for(int i = 1; i <= numPorts_; i++) {
    string buffPortCode;
    string indexString = boost::lexical_cast<std::string>(i);
    buffPortCode = "  BufferedPort<Bottle> receiverBuff" + indexString + ";\n";
    code += buffPortCode;
    buffPortCode = "  bool receiver" + indexString +  "Ok = receiverBuff" + indexString + ".open(\"/generatedCode/receiver" + indexString +"\");\n";
    code += buffPortCode;
  }
  code += "\n";

  return code;
}