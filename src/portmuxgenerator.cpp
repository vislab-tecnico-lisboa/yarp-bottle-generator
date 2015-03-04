#include <iostream>
#include <string>
#include "portmuxgenerator.hpp"
#include <boost/lexical_cast.hpp>

// Constructor and destructor
PortMuxGenerator::PortMuxGenerator(int numPorts, std::string ports, std::string outputName) : numPorts_(numPorts),
                                                                                              ports_(ports),
                                                                                              outputName_(outputName) {
  std::cout << "Creating PortMuxGenerator." << std::endl;
}

PortMuxGenerator::~PortMuxGenerator() {
  std::cout << "Deleting PortMuxGenerator." << std::endl;
}

int PortMuxGenerator::getNumPorts() {
  return numPorts_;
}

std::string PortMuxGenerator::getPorts() {
  return ports_;
}

std::string PortMuxGenerator::getOutputName() {
  return outputName_;
}

std::string PortMuxGenerator::generateCode() {
  std::string code;

  for(int i = 1; i <= numPorts_; i++) {
    std::string partialCode;
    std::string indexString = boost::lexical_cast<std::string>(i);
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
    std::string partialCode;
    std::string indexString = boost::lexical_cast<std::string>(i);
    partialCode = "  yarp.connect(\"" + extractPortFromString(i) + "\", receiverBuff" + indexString + ".getName());\n";
    code += partialCode;
  }
  code += "\n";

  code += "  std::cout << \"Waiting for output...\" << std::endl;\n";
  code += "  while(outputPort.getOutputCount() == 0) {\n";
  code += "    Time::delay(1);\n";
  code += "    std::cout << \".\\n\";\n";
  code += "  }\n";
  code += "  std::cout << \"Connection successfuly established.\" << std::endl;\n\n";

  code += "  while(true){\n";
  for(int i = 1; i <= numPorts_; i++) {
    std::string partialCode;
    std::string indexString = boost::lexical_cast<std::string>(i);
    partialCode = "    Bottle* reading" + indexString + " = receiverBuff" + indexString + ".read();\n";
    code += partialCode;
  }

  code += "\n";
  code += "    Bottle* mutex;\n\n";

  for(int i = 1; i <= numPorts_; i++) {
    std::string partialCode;
    std::string indexString = boost::lexical_cast<std::string>(i);
    partialCode = "    for(int i = 0; i < reading" + indexString + "->size(); i++) {\n";
    partialCode += "      mutex->add(reading" + indexString + "->get(i));\n";
    partialCode += "    }\n"; 
    code += partialCode;
  }

  code += "\n";
  return code;
}

/****
 ** Extract port name from wrap of ports names.
 ** Requires names separated by commas and no spaces between them.
 ****/
std::string PortMuxGenerator::extractPortFromString(int index) {
  std::string port;

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