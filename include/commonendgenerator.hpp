#ifndef COMMONEND_GENERATOR_HPP
#define COMMONEND_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

class CommonEndGenerator : public YarpCodeGenerator {
  public:
    /**
      * Constructor
    */
    CommonEndGenerator();
    /**
      * Destructor
    */
    ~CommonEndGenerator();
    /**
      * Generates the closing bracelets and main return
      * @return String that contains the last lines of code
    */
    std::string generateCode();
};

#endif //COMMONEND_GENERATOR_HPP
