#include <iostream>
#include <string>
#include "portmuxgenerator.hpp"

using namespace std;

// Constructor and destructor
PortMuxGenerator::PortMuxGenerator(int numPorts, string ports, string outputName) : numPorts_(numPorts),
                                                                                    ports_(ports),
                                                                                    outputName_(outputName) {
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

string PortMuxGenerator::getOutputName() {
  return outputName_;
}

string PortMuxGenerator::generateCode() {
  string code;

  for(int i = 1; i <= numPorts_; i++) {
    string partialCode;
    string indexString = boost::lexical_cast<std::string>(i);
    partialCode = "  BufferedPort<Bottle> receiverBuff" + indexString + ";\n";
    code += partialCode;
    partialCode = "  bool receiver" + indexString +  "Ok = receiverBuff" + indexString + ".open(\"/generatedCode/receiver" + indexString +"\");\n";
    code += partialCode;
  }
  code += "\n";

  code += "  Port outputPort;\n";
  code += "  outputPort.setWriteOnly();\n";
  code += "  bool outputOk = outputPort.open(\"" + getOutputName() + "@/yarp/generatedCode\");\n\n";

  for(int i = 1; i <= numPorts_; i++) {
    string partialCode;
    string indexString = boost::lexical_cast<std::string>(i);
    partialCode = "  yarp.connect(\"" + extractPortFromString(i) + "\", receiverBuff" + indexString + ".getName());\n";
    code += partialCode;
  }
  code += "\n";

  code += "  cout << \"Waiting for output...\" << endl;\n";
  code += "  while(outputPort.getOutputCount() == 0) {\n";
  code += "    Time::delay(1);\n";
  code += "    cout << \".\\n\";\n";
  code += "  }\n";
  code += "  cout << \"Connection successfuly established.\" << endl;\n\n";

  code += "  while(true){\n";
  for(int i = 1; i <= numPorts_; i++) {
    string partialCode;
    string indexString = boost::lexical_cast<std::string>(i);
    partialCode = "    Bottle* reading" + indexString + " = receiverBuff" + indexString + ".read();\n";
    code += partialCode;
  }

  code += "\n";
  return code;
}

/****
 ** Extract port name from wrap of ports names.
 ** Requires names separated by commas and no spaces between them.
 ****/
string PortMuxGenerator::extractPortFromString(int index) {
  string port;

  int commasCounter = 1;
  int stringBeginIndex = 0;
  if(index == 1) {
    for(int i = 0; i < ports_.size(); i++) {
      if(ports_.at(i) == ',') {
        port = ports_.substr(0, i);
        break;
      } 
    }
  } else if(index == numPorts_) {
    for(int i = 0; i < ports_.size(); i++) {
      if(ports_.at(i) == ',') {
        commasCounter++;
        stringBeginIndex = i;
        if(commasCounter == index) {
          port = ports_.substr(i + 1, ports_.size());
          break;
        }
      }
    }
  } else {
    for(int i = 0; i < ports_.size(); i++) {
      if(ports_.at(i) == ',') {
        commasCounter++;
        if(commasCounter == (index + 1)) {
          port = ports_.substr(stringBeginIndex, (i - stringBeginIndex));
          break;
        } else {
          stringBeginIndex = i + 1;
        }
      }
    }
  }

  return port;
}