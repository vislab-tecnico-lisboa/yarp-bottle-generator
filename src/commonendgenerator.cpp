#include <iostream>
#include "commonendgenerator.hpp"

// Constructor and destructor
CommonEndGenerator::CommonEndGenerator() {
    std::cout << "Creating CommonEndGenerator." << std::endl;
}

CommonEndGenerator::~CommonEndGenerator() {
    std::cout << "Deleting CommonEndGenerator." << std::endl;
}

std::string CommonEndGenerator::generateCode() {
  std::string code;

  //code += "    outputPort.write(bottleToSend);\n";
  code += "  }\n\n  return 0;\n}";

  return code;
}