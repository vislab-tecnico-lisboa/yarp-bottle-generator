#include <iostream>
#include <string>
#include "dataconvertergenerator.hpp"
#include <boost/lexical_cast.hpp>

/**
 * Implementation of the class that generates the code of the converter function for the elements of a hub
 */

DataConverterGenerator::DataConverterGenerator() {
  std::cout << "Creating DataConverterGenerator." << std::endl;
}

DataConverterGenerator::~DataConverterGenerator() {
  std::cout << "Deleting DataConverterGenerator." << std::endl;
}

std::vector<std::string> DataConverterGenerator::getFunction() {
  return function_;
}

std::vector<bool> DataConverterGenerator::getVerbose() {
  return verbose_;
}

void DataConverterGenerator::addConverterFunction(std::string function) {
  function_.push_back(function);
}

void DataConverterGenerator::addConverterVerbose(bool verbose) {
  verbose_.push_back(verbose);
}

std::string DataConverterGenerator::getConverterFunction(int converterIndex) {
  return function_.at(converterIndex);
}

bool DataConverterGenerator::getConverterVerbose(int converterIndex) {
  return verbose_.at(converterIndex);
}

std::string DataConverterGenerator::generateCode() {
  std::string code;

  for(int i = 0; i < function_.size(); i++) {
    std::string indexString = boost::lexical_cast<std::string>(i + 1);
    code += "    for(int i = 0; i < mux" + indexString + ".size(); i++) {\n";
    code += functionToString(i);
    code += "    }\n\n";
  }

  return code;
}

/**
 * Returns the string containing the code of the converter function.
 * One can add new functions to this method in order to expand the functionality of the converter,
 * but try to document what kind of objects should the mux result have.
 * Example: the function deg_to_rad expects a mutex containing doubles.
 * @param converterIndex identifier in the array of functions of this particular hub
 * @return std::string line(s) of code that performs the data conversion
*/
 std::string DataConverterGenerator::functionToString(int converterIndex) { // >data[6] / (180/3.1415926));
  std::string functionCode;
  std::string indexString = boost::lexical_cast<std::string>(converterIndex + 1);

  if(getConverterFunction(converterIndex) == "deg_to_rad") {
    functionCode = "      mux" + indexString + ".get(i) = mux" + indexString + ".get(i).asDouble() / (180/3.1415926);\n";
    if(getConverterVerbose(converterIndex)) {
      functionCode += "      std::cout << \"value on index \" << i << \": \" << mux" + indexString + ".get(i).asDouble() << std::endl;\n";
    }
  } else if(getConverterFunction(converterIndex) == "none_double") {
    functionCode = "      mux" + indexString + ".get(i) = mux" + indexString + ".get(i).asDouble();\n";
      if(getConverterVerbose(converterIndex)) {
        functionCode += "      std::cout << \"value on index \" << i << \": \" << mux" + indexString + ".get(i).asDouble() << std::endl;\n";
      }
    } else if(getConverterFunction(converterIndex) == "none") {
        // do nothing
        if(getConverterVerbose(converterIndex)) {
          functionCode += "      std::cout << \"Dummy break. Sorry for my laziness.\" << std::endl;\n";
        }
        functionCode += "      break;\n";
      }

  return functionCode;
 }
/**
@file dataconvertergenerator.cpp
*/
