#include <iostream>
#include <string>
#include "dataconvertergenerator.hpp"

// Constructor and destructor
DataConverterGenerator::DataConverterGenerator(std::string function, bool verbose) : function_(function),
                                                                                   verbose_(verbose) {
  std::cout << "Creating DataConverterGenerator." << std::endl;
}

DataConverterGenerator::~DataConverterGenerator() {
  std::cout << "Deleting DataConverterGenerator." << std::endl;
}

std::string DataConverterGenerator::getFunction() {
  return function_;
}

bool DataConverterGenerator::getVerbose() {
  return verbose_;
}

std::string DataConverterGenerator::generateCode() {
  std::string code;

  code += "    for(int i = 0; i < mutex.size(); i++) {\n";
  code += functionToString();
  code += "    }\n\n";

  return code;
}

/****
 ** Returns the string containing the code of the converter function.
 ** One can add new functions to this method in order to expand the functionality of the converter,
 ** but try to document what kind of objects should the mutex result have.
 ** Example: the function deg_to_rad expects a mutex containing doubles.
 ****/
 std::string DataConverterGenerator::functionToString() { // >data[6] / (180/3.1415926));
  std::string functionCode;

  if(function_ == "deg_to_rad") {
    functionCode = "      mutex.get(i) = mutex.get(i).asDouble() / (180/3.1415926);\n";
    if(verbose_) {
      functionCode += "      std::cout << mutex.get(i).asDouble() << std::endl;\n";
    }
  }

  return functionCode;
 }