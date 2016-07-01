#ifndef DATACONVERTER_GENERATOR_HPP
#define DATACONVERTER_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"
/**
 * Header of the class that generates the code of the converter function for the elements of a hub
 */
class DataConverterGenerator : public YarpCodeGenerator {
  public:
    /**
      * Constructor
    */
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
    std::vector<std::string> function_; /**< converter function name */
    std::vector<bool> verbose_;/**< Verbose flag */

    std::string functionToString(int converterIndex);
};

#endif //DATACONVERTER_GENERATOR_HPP
