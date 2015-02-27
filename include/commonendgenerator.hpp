#ifndef COMMONEND_GENERATOR_HPP
#define COMMONEND_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

using namespace std;

class CommonEndGenerator : public YarpCodeGenerator {
  public:
    CommonEndGenerator();
    ~CommonEndGenerator();

    string generateCode();
};

#endif //COMMONEND_GENERATOR_HPP