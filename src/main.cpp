#include <iostream>
#include <fstream>
#include "commonbeginninggenerator.hpp"
#include "portmuxgenerator.hpp"
#include "dataconvertergenerator.hpp"
#include "commonendgenerator.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Please provide the path to the configuration file...";
    return 0;
  }

  std::string configPath = "../app/config.ini";

  boost::property_tree::ptree pt;
  boost::property_tree::ini_parser::read_ini(configPath, pt);

  // common beginning code generation
  CommonBeginningGenerator commonBeginGen;
  std::string commonBeginCode = commonBeginGen.generateCode();

  // multiplexers code generation
  int numMuxes = pt.get<int>("mux_general.num_mux");
  std::string outputName = pt.get<std::string>("mux_general.output_name");
  PortMuxGenerator portMuxGen(numMuxes, outputName);
  for(int i = 1; i <= numMuxes; i++) {
    std::string indexString = boost::lexical_cast<std::string>(i);
    int numPorts = pt.get<int>("mux" + indexString + ".num_ports");
    std::string ports = pt.get<std::string>("mux" + indexString + ".ports");
    portMuxGen.addMuxNumPorts(numPorts);
    portMuxGen.addMuxPorts(ports);
  }
  std::cout << "numMuxes_: " << portMuxGen.getNumMuxes() << std::endl;
  std::cout << "outputName_: " << portMuxGen.getOutputName() << std::endl;
  for(int i = 1; i <= numMuxes; i++) {
    std::cout << "[mux" << i << "] numPorts_: " << portMuxGen.getMuxNumPorts(i - 1) << std::endl;
    std::cout << "[mux" << i << "] ports_: " << portMuxGen.getMuxPorts(i - 1) << std::endl;
  }
  std::string portMuxCode = portMuxGen.generateCode();

  // converters code generation
  DataConverterGenerator converterGen;
  for(int i = 1; i <= numMuxes; i++) {
    std::string indexString = boost::lexical_cast<std::string>(i);
    std::string function = pt.get<std::string>("converter" + indexString + ".function");
    bool verboseConverter = pt.get<bool>("converter" + indexString + ".verbose");
    converterGen.addConverterFunction(function);
    converterGen.addConverterVerbose(verboseConverter);
  }
  for(int i = 1; i <= numMuxes; i++) {
    std::cout << "[converter" << i << "] function_: " << converterGen.getConverterFunction(i - 1) << std::endl;
    std::cout << "[converter" << i << "] verbose_: " << converterGen.getConverterVerbose(i - 1) << std::endl;
  }
  std::string converterCode = converterGen.generateCode();

  // common ending code generation 
  CommonEndGenerator commonEndGen;
  std::string commonEndCode = commonEndGen.generateCode();

  std::ofstream generatedFile;
  generatedFile.open ("../results/generatedCode.cpp");

  generatedFile << commonBeginCode;
  generatedFile << portMuxCode;
  generatedFile << converterCode;
  generatedFile << commonEndCode;

  generatedFile.close();

  return 0;
}