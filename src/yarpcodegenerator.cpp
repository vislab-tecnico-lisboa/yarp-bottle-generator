#include <iostream>
#include "yarpcodegenerator.hpp"

// Constructor and destructor
YarpCodeGenerator::YarpCodeGenerator() {
  std::cout << "Creating YarpCodeGenerator." << std::endl;
}

YarpCodeGenerator::~YarpCodeGenerator(/*string configData*/) {
  std::cout << "Deleting YarpCodeGenerator." << std::endl;
}