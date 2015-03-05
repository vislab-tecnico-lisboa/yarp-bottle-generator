#ifndef DATACONVERTER_GENERATOR_HPP
#define DATACONVERTER_GENERATOR_HPP
#include "yarpcodegenerator.hpp"

class DataConverterGenerator : public YarpCodeGenerator {
  public:
    DataConverterGenerator(std::string function, bool verbose);
    ~DataConverterGenerator();

    std::string getFunction();

    bool getVerbose();

    std::string generateCode();
    
  private:
    std::string function_;
    bool verbose_;

    std::string functionToString();
};

#endif //DATACONVERTER_GENERATOR_HPP