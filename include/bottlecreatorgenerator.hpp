#ifndef BOTTLECREATOR_GENERATOR_HPP
#define BOTTLECREATOR_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"
#include "childgenerator.hpp"

/**
  * A constructor.
  * A more elaborate description of the constructor.
*/
class BottleCreatorGenerator : public YarpCodeGenerator {
  public:
    /**
      * A constructor.
      * A more elaborate description of the constructor.
    */
    BottleCreatorGenerator(int numFields, const double & rate_, bool toRos);
    ~BottleCreatorGenerator();

    int getNumFields();

    std::vector<ChildGenerator> getChildren();

    std::vector<std::string> getFieldsType();

    std::vector<std::string> getFieldsMsg();

    std::vector<std::string> getFieldsMux();

    void addChild(ChildGenerator& child);

    void addFieldType(std::string type);

    void addFieldMsg(std::string msg);

    void addFieldMux(std::string mux);

    void removeFirstChild();

    ChildGenerator& getFirstChild();

    std::string getFieldType(int fieldIndex);

    std::string getFieldMsg(int fieldIndex);

    std::string getFieldMux(int fieldIndex);

    std::string generateCode();

  private:
    int numFields_;
    int listIndex_;
    bool toRos_;
    std::vector<ChildGenerator> children_;
    std::vector<std::string> fieldsType_;
    std::vector<std::string> fieldsMsg_;
    std::vector<std::string> fieldsMux_;
    double rate;
    double period;

    std::string handleFieldGeneration(int fieldIndex);
};

#endif //BOTTLECREATOR_GENERATOR_HPP
