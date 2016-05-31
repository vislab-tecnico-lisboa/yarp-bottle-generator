
#ifndef CMAKEFILE_GENERATOR_HPP
#define CMAKEFILE_GENERATOR_HPP
#include "yarpcodegenerator.hpp"
/**
  * Class that generates the text of the CMakeLists.txt file 
  * 
*/
class CMakeFileGenerator : public YarpCodeGenerator {
  public:
    /**
      * Constructor
    */
    CMakeFileGenerator();
    /**
      * Destructor
    */
    ~CMakeFileGenerator();
    /**
      * Generates the CMakeLists.txt
      * @return String that contains the cmake script
    */
    std::string generateCode();
    std::string cpp_file_name;
};

#endif //COMMONEND_GENERATOR_HPP
