#ifndef DATACONVERTER_GENERATOR_HPP
#define DATACONVERTER_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

class DataConverterGenerator : public YarpCodeGenerator {
  public:
    DataConverterGenerator();
    ~DataConverterGenerator();

    std::string generateCode();
    
  private:
};

#endif //DATACONVERTER_GENERATOR_HPP