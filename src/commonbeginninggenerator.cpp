#include <iostream>
#include "commonbeginninggenerator.hpp"

// Constructor and destructor
CommonBeginningGenerator::CommonBeginningGenerator() {
    std::cout << "Creating CommonBeginningGenerator." << std::endl;
}

CommonBeginningGenerator::~CommonBeginningGenerator() {
    std::cout << "Deleting CommonBeginningGenerator." << std::endl;
}

std::string CommonBeginningGenerator::generateCode() {
  std::string code;

  code += "#include <iostream>\n";
  code += "#include <yarp/os/all.h>\n";
  code += "#include <math.h>\n\n";
  code += "using namespace yarp::os;\n\n";
  code += "int main(int argc, char *argv[]) {\n";
  code += "  Network yarp;\n\n";

  return code;
}
