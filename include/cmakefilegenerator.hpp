
#ifndef CMAKEFILE_GENERATOR_HPP
#define CMAKEFILE_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

class CMakeFileGenerator : public YarpCodeGenerator {
  public:
    CMakeFileGenerator();
    ~CMakeFileGenerator();

    std::string generateCode();
    std::string cpp_file_name;
};

#endif //COMMONEND_GENERATOR_HPP
