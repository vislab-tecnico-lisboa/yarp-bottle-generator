#ifndef COMMONEND_GENERATOR_HPP
#define COMMONEND_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

class CommonEndGenerator : public YarpCodeGenerator {
  public:
    CommonEndGenerator();
    ~CommonEndGenerator();

    std::string generateCode();
};

#endif //COMMONEND_GENERATOR_HPP