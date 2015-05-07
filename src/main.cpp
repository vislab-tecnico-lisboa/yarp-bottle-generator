#include <iostream>
#include <fstream>
#include "commonbeginninggenerator.hpp"
#include "portmuxgenerator.hpp"
#include "dataconvertergenerator.hpp"
#include "bottlecreatorgenerator.hpp"
#include "commonendgenerator.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lexical_cast.hpp>

void handleMessageChild(ChildGenerator& childGen, boost::property_tree::ptree& pt, std::string messageName) {
  int numFields = childGen.getNumFields();

  for(int i = 1; i <= numFields; i++) {
    std::string indexString = boost::lexical_cast<std::string>(i);
    std::string type = pt.get<std::string>(messageName + "." + indexString + "_type");
    childGen.addFieldType(type);
    std::string msg;
    std::string mux;
    if(type == "msg") {
      std::string childMessageName = pt.get<std::string>(messageName + "." + indexString + "_msg");
      int numChildFields = pt.get<int>(childMessageName + ".num_fields");
      ChildGenerator newChildGen(numChildFields);
      handleMessageChild(newChildGen, pt, childMessageName);
      childGen.addChild(newChildGen);
    } else {
        if(type == "single_value" ||
           type == "list") {
          msg = pt.get<std::string>(messageName + "." + indexString + "_msg");
        }
        if(type == "mux") {
          mux = pt.get<std::string>(messageName + "." + indexString + "_mux");
        }
      }
    childGen.addFieldMsg(msg);
    childGen.addFieldMux(mux);
  }
  std::cout << "numFields_: " << childGen.getNumFields() << std::endl;
  for(int i = 1; i <= numFields; i++) {
    std::cout << "[field number " << i << "] type_: " << childGen.getFieldType(i - 1) << std::endl;
    std::cout << "[field number " << i << "] msg_: " << childGen.getFieldMsg(i - 1) << std::endl;
    std::cout << "[field number " << i << "] mux_: " << childGen.getFieldMux(i - 1) << std::endl;
  }
}

void handleMessageFields(BottleCreatorGenerator& bottleCreatorGen, boost::property_tree::ptree& pt) {
  int numFields = bottleCreatorGen.getNumFields();

  for(int i = 1; i <= numFields; i++) {
    std::string indexString = boost::lexical_cast<std::string>(i);
    std::string type = pt.get<std::string>("message." + indexString + "_type");
    bottleCreatorGen.addFieldType(type);
    std::string msg;
    std::string mux;
    if(type == "msg") {
      std::string childMessageName = pt.get<std::string>("message." + indexString + "_msg");
      int numChildFields = pt.get<int>(childMessageName + ".num_fields");
      ChildGenerator childGen(numChildFields);
      handleMessageChild(childGen, pt, childMessageName);
      bottleCreatorGen.addChild(childGen);
    } else {
        if(type == "single_value" ||
           type == "list") {
          msg = pt.get<std::string>("message." + indexString + "_msg");
        }
        if(type == "mux") {
          mux = pt.get<std::string>("message." + indexString + "_mux");
        }
      }
    bottleCreatorGen.addFieldMsg(msg);
    bottleCreatorGen.addFieldMux(mux);
  }
  std::cout << "numFields_: " << bottleCreatorGen.getNumFields() << std::endl;
  for(int i = 1; i <= numFields; i++) {
    std::cout << "[field number " << i << "] type_: " << bottleCreatorGen.getFieldType(i - 1) << std::endl;
    std::cout << "[field number " << i << "] msg_: " << bottleCreatorGen.getFieldMsg(i - 1) << std::endl;
    std::cout << "[field number " << i << "] mux_: " << bottleCreatorGen.getFieldMux(i - 1) << std::endl;
  }
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Please provide the path to the configuration file...\n";
    return 0;
  }

  std::string fixedConfigPath = "/app/config.ini";
  std::string configPath;
  std::string generatedFileDestination = "/results/generatedCode.cpp";
  std::string outputFileLocation;
  
  char* generatorDir = getenv("BOTTLE_GENERATOR_DIR");
  if(generatorDir == NULL) {
    std::cout << "The $BOTTLE_GENERATOR_DIR is not defined. Please export its value in order to proceed.\n";
    return 0;
  }

  outputFileLocation = generatorDir + generatedFileDestination;
  configPath = generatorDir + fixedConfigPath;

  boost::property_tree::ptree pt;
  boost::property_tree::ini_parser::read_ini(configPath, pt);

  // common beginning code generation
  CommonBeginningGenerator commonBeginGen;
  std::string commonBeginCode = commonBeginGen.generateCode();

  // multiplexers code generation
  int numMuxes = pt.get<int>("general.num_mux");
  std::string outputName = pt.get<std::string>("general.output_name");
  PortMuxGenerator portMuxGen(numMuxes, outputName);
  DataConverterGenerator converterGen;
  for(int i = 1; i <= numMuxes; i++) {
    std::string indexString = boost::lexical_cast<std::string>(i);
    int numPorts = pt.get<int>("mux" + indexString + ".num_ports");
    std::string ports = pt.get<std::string>("mux" + indexString + ".ports");
    std::string function = pt.get<std::string>("mux" + indexString + ".function");
    bool verboseConverter = pt.get<bool>("mux" + indexString + ".verbose");
    portMuxGen.addMuxNumPorts(numPorts);
    portMuxGen.addMuxPorts(ports);
    converterGen.addConverterFunction(function);
    converterGen.addConverterVerbose(verboseConverter);
  }
  std::cout << "numMuxes_: " << portMuxGen.getNumMuxes() << std::endl;
  std::cout << "outputName_: " << portMuxGen.getOutputName() << std::endl;
  for(int i = 1; i <= numMuxes; i++) {
    std::cout << "[mux" << i << "] numPorts_: " << portMuxGen.getMuxNumPorts(i - 1) << std::endl;
    std::cout << "[mux" << i << "] ports_: " << portMuxGen.getMuxPorts(i - 1) << std::endl;
    std::cout << "[converter" << i << "] function_: " << converterGen.getConverterFunction(i - 1) << std::endl;
    std::cout << "[converter" << i << "] verbose_: " << converterGen.getConverterVerbose(i - 1) << std::endl;
  }
  std::string portMuxCode = portMuxGen.generateCode();
  std::string converterCode = converterGen.generateCode();

  // bottle creator code generation
  int numFields = pt.get<int>("message.num_fields");
  BottleCreatorGenerator bottleCreatorGen(numFields);
  handleMessageFields(bottleCreatorGen, pt);  
  std::string bottleCreatorCode = bottleCreatorGen.generateCode();

  // common ending code generation 
  CommonEndGenerator commonEndGen;
  std::string commonEndCode = commonEndGen.generateCode();

  std::ofstream generatedFile;
  generatedFile.open(outputFileLocation.c_str());

  generatedFile << commonBeginCode;
  generatedFile << portMuxCode;
  generatedFile << converterCode;
  generatedFile << bottleCreatorCode;
  generatedFile << commonEndCode;

  generatedFile.close();

  return 0;
}