#include <iostream>
#include <string>
#include "portmuxgenerator.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


// Constructor and destructor
PortMuxGenerator::PortMuxGenerator(int numMuxes, std::string outputName, bool toRos, std::string & output_port_name_, std::string & ros_message_name, bool fromRos) :  numMuxes_(numMuxes),
                                                                                        outputName_(outputName),
                                                                                        toRos_(toRos),
                                            output_port_name(output_port_name_),
                                            rosMessageName_(ros_message_name),
                                            fromRos_(fromRos)
{
  std::cout << "Creating PortMuxGenerator." << std::endl;
}

PortMuxGenerator::~PortMuxGenerator() {
  std::cout << "Deleting PortMuxGenerator." << std::endl;
}

int PortMuxGenerator::getNumMuxes() {
  return numMuxes_;
}

std::string PortMuxGenerator::getOutputName() {
  return outputName_;
}

std::string PortMuxGenerator::getRosMessageName() {
  return rosMessageName_;
}
bool PortMuxGenerator::getToRos() {
  return toRos_;
}
bool PortMuxGenerator::getFromRos() {
  return fromRos_;
}
std::vector<int> PortMuxGenerator::getNumPorts() {
  return numPorts_;
}

std::vector<std::string> PortMuxGenerator::getPorts() {
  return ports_;
}

void PortMuxGenerator::addMuxNumPorts(int numPorts) {
  numPorts_.push_back(numPorts);
}

void PortMuxGenerator::addMuxPorts(std::string ports) {
  ports_.push_back(ports);
}

int PortMuxGenerator::getMuxNumPorts(int muxIndex) {
  return numPorts_.at(muxIndex);
}

std::string PortMuxGenerator::getMuxPorts(int muxIndex) {
  return ports_.at(muxIndex);
}

std::string PortMuxGenerator::generateCode() {
  std::string code;

  for(int j = 1; j <= numMuxes_; j++) {
    std::string muxIndexString = boost::lexical_cast<std::string>(j);
    for(int i = 1; i <= getMuxNumPorts(j - 1); i++) {
      std::string partialCode;
      std::string indexString = boost::lexical_cast<std::string>(i);
      partialCode = "  BufferedPort<Bottle> receiverBuff" + indexString + "Mux" + muxIndexString + ";\n";
      if (getFromRos()){
        partialCode += "  receiverBuff" + indexString + "Mux" + muxIndexString + ".setReadOnly();\n";
        code += partialCode;
        partialCode = "  bool receiver" + indexString + "Mux" + muxIndexString + "Ok = receiverBuff" + indexString + "Mux" + muxIndexString + ".open(\""+extractPortFromString(j-1, i)+"@/mux" + muxIndexString + "/receiver" + indexString +"\");\n";
      }
      else {
          code += partialCode;
          partialCode = "  bool receiver" + indexString + "Mux" + muxIndexString + "Ok = receiverBuff" + indexString + "Mux" + muxIndexString + ".open(\"/"+output_port_name+"/mux" + muxIndexString + "/receiver" + indexString +"\");\n";
      }
      code += partialCode;
    }
    code += "\n";
  }

  code += "  Port outputPort;\n";
  if (toRos_) {
    code += "  outputPort.promiseType(Type::byNameOnWire(\"" + getRosMessageName() + "\"));\n";
  }
  code += "  outputPort.setWriteOnly();\n";
  if(toRos_)
    code += "  bool outputOk = outputPort.open(\"" + getOutputName() + "@/yarp/"+output_port_name+"\");\n\n";
  else
    code += "  bool outputOk = outputPort.open(\"/writeBuff \");\n\n";

  if (!fromRos_){
    code += "  bool allConnected = false;\n";
    code += "  std::vector<std::vector<bool> > portsConnected;\n";
    code += "  portsConnected.resize(" + boost::lexical_cast<std::string>(numMuxes_) + ");\n";
    code += "  int totalConnections=0;\n";
    for(int j = 0; j < numMuxes_; j++) {
        code += "    portsConnected[" + boost::lexical_cast<std::string>(j) + "].resize(" + boost::lexical_cast<std::string>(getMuxNumPorts(j)) + ");\n";
        code += "    portsConnected[" + boost::lexical_cast<std::string>(j) + "].assign(" + boost::lexical_cast<std::string>(getMuxNumPorts(j)) + ",false);\n";
        code += "    totalConnections += " + boost::lexical_cast<std::string>(getMuxNumPorts(j)) + ";\n";
    }

    code += "\n";
    code += "  while (!allConnected){\n";
    code += "    int connectedNumber=totalConnections;\n";
    for(int j = 1; j <= numMuxes_; j++) {
        std::string muxIndexString = boost::lexical_cast<std::string>(j);
        for(int i = 1; i <= getMuxNumPorts(j-1); i++) {
            std::string indexString = boost::lexical_cast<std::string>(i);
            code += "    if (!portsConnected[" + boost::lexical_cast<std::string>(j-1) +"][" + indexString + "]){\n";
            code += "      portsConnected[" + boost::lexical_cast<std::string>(j-1) +"][" + indexString + "] = yarp.connect(\"" + extractPortFromString(j-1, i) + "\", receiverBuff" + indexString + "Mux" + muxIndexString + ".getName());\n";
            code += "      if (!portsConnected[" + boost::lexical_cast<std::string>(j-1) +"][" + indexString + "])\n";
            code += "        connectedNumber--;\n";
            code += "    }";
        }
    }
    code += "    if (connectedNumber == totalConnections)\n";
    code += "      allConnected = true;\n";
    code += "    std::cout << \".\\n\";\n";
    code += "    Time::delay(1);\n";
    code += "  }";
  }

  if(getFromRos()) {
    code += "  std::cout << \"Waiting for output...\" << std::endl;\n";
    code += "  bool connectSuccess = false;\n";
    code += "  while(!connectSuccess) {\n";
    code += "    connectSuccess = yarp.connect(\" /writeBuff\", \"" + getOutputName() + "\");\n";
    code += "    Time::delay(1);\n";
    code += "    std::cout << \".\\n\";\n";
    code += "  }\n";
    code += "  std::cout << \"Connection successfuly established.\" << std::endl;\n\n";
  }

  code += "  int counter = 0;\n\n";

  code += "  while(true){\n";
  for(int j = 1; j <= numMuxes_; j++) {
    std::string muxIndexString = boost::lexical_cast<std::string>(j);
    for(int i = 1; i <= getMuxNumPorts(j - 1); i++) {
      std::string partialCode;
      std::string indexString = boost::lexical_cast<std::string>(i);
      partialCode = "    Bottle* reading" + indexString + "Mux" + muxIndexString + " = receiverBuff" + indexString + "Mux" + muxIndexString + ".read();\n";
      code += partialCode;
    }
    code += "\n";
  }

  for(int j = 1; j <= numMuxes_; j++) {
    std::string muxIndexString = boost::lexical_cast<std::string>(j);
    code += "    Bottle mux" + muxIndexString + ";\n";
  }
  code += "\n";

  for(int j = 1; j <= numMuxes_; j++) {
    std::string muxIndexString = boost::lexical_cast<std::string>(j);
    for(int i = 1; i <= getMuxNumPorts(j - 1); i++) {
      std::string partialCode;
      std::string indexString = boost::lexical_cast<std::string>(i);
      partialCode = "    for(int i = 0; i < reading" + indexString + "Mux" + muxIndexString + "->size(); i++) {\n";
      partialCode += "      mux" + muxIndexString + ".add(reading" + indexString + "Mux" + muxIndexString + "->get(i));\n";
      partialCode += "    }\n";
      code += partialCode;
    }
    code += "\n";
  }

  return code;
}

/**
 * Retrieve port/topic name from wrap of ports names.
 * Requires names separated by commas and no spaces between them.
 * @param muxIndex Hub's index in the vector of Hubs
 * @param portIndex Port's index in the ports string
 */
std::string PortMuxGenerator::extractPortFromString(int muxIndex, int portIndex) {
  std::string port;

  int commasCounter = 1;
  int stringBeginIndex = 0;
  if(portIndex == 1 && getMuxNumPorts(muxIndex) == 1) {
    port = getMuxPorts(muxIndex);
  } else if(portIndex == 1) {
    for(int i = 0; i < getMuxPorts(muxIndex).size(); i++) {
      if(getMuxPorts(muxIndex).at(i) == ',') {
        port = getMuxPorts(muxIndex).substr(0, i);
        break;
      }
    }
  } else if(portIndex == getMuxNumPorts(muxIndex)) {
    for(int i = 0; i < getMuxPorts(muxIndex).size(); i++) {
      if(getMuxPorts(muxIndex).at(i) == ',') {
        commasCounter++;
        stringBeginIndex = i;
        if(commasCounter == portIndex) {
          port = getMuxPorts(muxIndex).substr(i + 1, getMuxPorts(muxIndex).size());
          break;
        }
      }
    }
  } else {
    for(int i = 0; i < getMuxPorts(muxIndex).size(); i++) {
      if(getMuxPorts(muxIndex).at(i) == ',') {
        commasCounter++;
        if(commasCounter == (portIndex + 1)) {
          port = getMuxPorts(muxIndex).substr(stringBeginIndex, (i - stringBeginIndex));
          break;
        } else {
          stringBeginIndex = i + 1;
        }
      }
    }
  }

  boost::erase_all(port, " ");

  return port;
}
