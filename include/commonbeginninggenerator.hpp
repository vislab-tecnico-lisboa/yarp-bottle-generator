#ifndef COMMONBEGINNING_GENERATOR_HPP
#define COMMONBEGINNING_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

class CommonBeginningGenerator : public YarpCodeGenerator {
  public:
    CommonBeginningGenerator();
    ~CommonBeginningGenerator();

    std::string generateCode();
};

#endif //COMMONBEGINNING_GENERATOR_HPP