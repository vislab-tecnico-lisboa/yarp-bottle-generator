#include <iostream>
#include <fstream>
#include "commonbeginninggenerator.hpp"
#include "portmuxgenerator.hpp"
#include "commonendgenerator.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;

int main(int argc, char* argv[]) {
  if(argc != 2) {
    cout << "Please provide the path to the configuration file...";
    return 0;
  }

  string configPath = "../app/config.ini";

  boost::property_tree::ptree pt;
  boost::property_tree::ini_parser::read_ini(configPath, pt);
  string ports = pt.get<string>("mux.ports");
  string messageName = pt.get<string>("message.name");

  CommonBeginningGenerator commonBeginGen;
  string commonBeginCode = commonBeginGen.generateCode();
  CommonEndGenerator commonEndGen;
  string commonEndCode = commonEndGen.generateCode();

  ofstream generatedFile;
  generatedFile.open ("../results/generatedCode.cpp");

  generatedFile << commonBeginCode;
  generatedFile << commonEndCode;

  generatedFile.close();

  return 0;
}