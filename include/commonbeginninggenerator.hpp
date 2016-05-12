#ifndef COMMONBEGINNING_GENERATOR_HPP
#define COMMONBEGINNING_GENERATOR_HPP
#include "yarpcodegenerator.hpp"
/**
  * Class that generates the text of the include headers and the main function 
  * 
*/
class CommonBeginningGenerator : public YarpCodeGenerator {
  public:
    /**
      * Constructor
    */
    CommonBeginningGenerator();
    /**
      * Destructor
    */
    ~CommonBeginningGenerator();
    /**
      * @return String that contains the include headers and main function
    */
    std::string generateCode();
};

#endif //COMMONBEGINNING_GENERATOR_HPP
