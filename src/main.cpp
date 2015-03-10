#include <iostream>
#include <fstream>
#include "commonbeginninggenerator.hpp"
#include "portmuxgenerator.hpp"
#include "dataconvertergenerator.hpp"
#include "commonendgenerator.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Please provide the path to the configuration file...";
    return 0;
  }

  std::string configPath = "../app/config.ini";

  boost::property_tree::ptree pt;
  boost::property_tree::ini_parser::read_ini(configPath, pt);
  int numPorts = pt.get<int>("mux.num_ports");
  std::string ports = pt.get<std::string>("mux.ports");
  std::string outputName = pt.get<std::string>("mux.output_name");
  std::string function = pt.get<std::string>("converter.function");
  bool verboseConverter = pt.get<bool>("converter.verbose");
  
  /*std::string exp = pt.get<std::string>("message.1");

  std::cout << "\n\nMESSAGE: " << exp << "\n" << std::endl;*/

  CommonBeginningGenerator commonBeginGen;
  std::string commonBeginCode = commonBeginGen.generateCode();
  PortMuxGenerator portMuxGen(numPorts, ports, outputName);
  std::string portMuxCode = portMuxGen.generateCode();
  std::cout << "numPorts_: " << portMuxGen.getNumPorts() << std::endl;
  std::cout << "ports_: " << portMuxGen.getPorts() << std::endl;
  std::cout << "outputName_: " << portMuxGen.getOutputName() << std::endl;
  DataConverterGenerator converterGen(function, verboseConverter);
  std::string converterCode = converterGen.generateCode();
  std::cout << "function_: " << converterGen.getFunction() << std::endl;
  std::cout << "verbose_: " << converterGen.getVerbose() << std::endl;
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