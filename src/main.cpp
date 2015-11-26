#include <iostream>
#include <fstream>
#include "commonbeginninggenerator.hpp"
#include "portmuxgenerator.hpp"
#include "dataconvertergenerator.hpp"
#include "bottlecreatorgenerator.hpp"
#include "cmakefilegenerator.hpp"
#include "commonendgenerator.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
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

void info()
{
	std::cout << "args:\n\t[0]: configuration file name" << std::endl;
	std::cout << "\t[1]: generated code file name" << std::endl;
}

int main(int argc, char* argv[])
{
  if(argc != 3) {
    info();
    return 0;
  }

  std::string fixedResultsPath = "/results/";
  std::string fixedConfigPath = "/app/";


  std::string configFileName=argv[1];
  std::string generatedFileDestination = argv[2];
  std::string outputFileLocation;

  int lastindex = generatedFileDestination.find_last_of(".");
  std::string resultsFileFolder = generatedFileDestination.substr(0, lastindex);
  std::cout << resultsFileFolder << std::endl;
  char* generatorDir = getenv("BOTTLE_GENERATOR_DIR");
  if(generatorDir == NULL) {
    std::cout << "The $BOTTLE_GENERATOR_DIR is not defined. Please export its value in order to proceed.\n";
    return 0;
  }


boost::filesystem::path dir(generatorDir +fixedResultsPath+ resultsFileFolder);
if (boost::filesystem::create_directory(dir))
    std::cout << "Success" << "\n";
  outputFileLocation = generatorDir +fixedResultsPath+ resultsFileFolder+"/"+ generatedFileDestination;
  std::string configPath = generatorDir + fixedConfigPath+configFileName;

  boost::property_tree::ptree pt;
  boost::property_tree::ini_parser::read_ini(configPath, pt);

  // common beginning code generation
  CommonBeginningGenerator commonBeginGen;
  std::string commonBeginCode = commonBeginGen.generateCode();

  // multiplexers code generation
  int numMuxes = pt.get<int>("general.num_mux");
  std::string outputName = pt.get<std::string>("general.output_name");
  bool toRos = pt.get<bool>("general.to_ros");
  bool fromRos = pt.get<bool>("general.from_ros_topics");
  double rate = pt.get<double>("general.rate");
  std::string rosMessageName("");
  if (toRos)
     rosMessageName = pt.get<std::string>("general.ros_msg_name");

  PortMuxGenerator portMuxGen(numMuxes, outputName, toRos, resultsFileFolder, rosMessageName, fromRos);
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
  std::cout << "toRos_: " << portMuxGen.getToRos() << std::endl;
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
  BottleCreatorGenerator bottleCreatorGen(numFields, rate);
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
  CMakeFileGenerator cmakeFileGen;
  cmakeFileGen.cpp_file_name = resultsFileFolder;
  std::string cmakeFileCode = cmakeFileGen.generateCode();
  std::ofstream cmakeGeneratedFile;
  std::string cmakelists_str = generatorDir +fixedResultsPath+ resultsFileFolder+"/CMakeLists.txt";
  cmakeGeneratedFile.open(cmakelists_str.c_str());
  cmakeGeneratedFile << cmakeFileCode;
  cmakeGeneratedFile.close();
  return 0;
}
