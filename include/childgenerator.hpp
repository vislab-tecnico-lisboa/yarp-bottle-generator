#ifndef CHILD_GENERATOR_HPP
#define CHILD_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"

class ChildGenerator : public YarpCodeGenerator {
  public:
    ChildGenerator(int numFields, bool toRos);
    ~ChildGenerator();

    int getNumFields();

    std::vector<ChildGenerator> getChildren();

    std::vector<std::string> getFieldsType();

    std::vector<std::string> getFieldsMsg();

    std::vector<std::string> getFieldsMux();

    void setParentName(std::string parentName);

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
    bool toRos_;
    int listIndex_;
    std::string parentName_;
    std::vector<ChildGenerator> children_;
    std::vector<std::string> fieldsType_;
    std::vector<std::string> fieldsMsg_;
    std::vector<std::string> fieldsMux_;

    std::string handleFieldGeneration(int fieldIndex);
};

#endif //CHILD_GENERATOR_HPP
