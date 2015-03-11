#ifndef DATACONVERTER_GENERATOR_HPP
#define DATACONVERTER_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"

class DataConverterGenerator : public YarpCodeGenerator {
  public:
    DataConverterGenerator();
    ~DataConverterGenerator();

    std::vector<std::string> getFunction();

    std::vector<bool> getVerbose();

    void addConverterFunction(std::string function);

    void addConverterVerbose(bool verbose);

    std::string getConverterFunction(int converterIndex);

    bool getConverterVerbose(int converterIndex);

    std::string generateCode();
    
  private:
    std::vector<std::string> function_;
    std::vector<bool> verbose_;

    std::string functionToString(int converterIndex);
};

#endif //DATACONVERTER_GENERATOR_HPP