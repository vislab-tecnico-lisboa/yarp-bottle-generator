#ifndef COMMONBEGINNING_GENERATOR_HPP
#define COMMONBEGINNING_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

using namespace std;

class CommonBeginningGenerator : public YarpCodeGenerator {
  public:
    CommonBeginningGenerator();
    ~CommonBeginningGenerator();

    string generateCode();
};

#endif //COMMONBEGINNING_GENERATOR_HPP