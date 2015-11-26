
#include <iostream>
#include "cmakefilegenerator.hpp"

// Constructor and destructor
CMakeFileGenerator::CMakeFileGenerator() {
    std::cout << "Creating CMakeFileGenerator." << std::endl;
}

CMakeFileGenerator::~CMakeFileGenerator() {
    std::cout << "Deleting CMakeFileGenerator." << std::endl;
}

std::string CMakeFileGenerator::generateCode() {
  std::string code;

  //code += "    outputPort.write(bottleToSend);\n";
  code += "cmake_minimum_required(VERSION 2.8.7)\n";
  code += "# find YARP\n";
  code += "find_package(YARP REQUIRED)\n";
  code += "\n";
  code += "# add YARP include directories\n";
  code += "include_directories(${YARP_INCLUDE_DIRS})\n";
  code += "include_directories(${CMAKE_CURRENT_SOURCE_DIR})\n";
  code += "\n";
  code += "# set up our program\n";
  code += "add_executable(" + cpp_file_name + " " + cpp_file_name + ".cpp)\n";
  code += "\n";
  code += "# link with YARP libraries\n";
  code += "target_link_libraries(" + cpp_file_name +" ${YARP_LIBRARIES})\n";
  return code;
}
