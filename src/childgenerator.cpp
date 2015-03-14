#include <iostream>
#include <string>
#include "childgenerator.hpp"
#include <boost/lexical_cast.hpp>

// Constructor and destructor
ChildGenerator::ChildGenerator(int numFields) : numFields_(numFields),
                                                listIndex_(0) {
  std::cout << "Creating ChildGenerator." << std::endl;
}

ChildGenerator::~ChildGenerator() {
  std::cout << "Deleting ChildGenerator." << std::endl;
}

int ChildGenerator::getNumFields() {
  return numFields_;
}

std::vector<ChildGenerator> ChildGenerator::getChildren() {
  return children_;
}

std::vector<std::string> ChildGenerator::getFieldsType() {
  return fieldsType_;
}

std::vector<std::string> ChildGenerator::getFieldsMsg() {
  return fieldsMsg_;
}

std::vector<std::string> ChildGenerator::getFieldsMux() {
  return fieldsMux_;
}

void ChildGenerator::setParentName(std::string parentName) {
  parentName_ = parentName;
}

void ChildGenerator::addChild(ChildGenerator& child) {
  children_.push_back(child);
}

void ChildGenerator::addFieldType(std::string type) {
  fieldsType_.push_back(type);
}

void ChildGenerator::addFieldMsg(std::string msg) {
  fieldsMsg_.push_back(msg);
}

void ChildGenerator::addFieldMux(std::string mux) {
  fieldsMux_.push_back(mux);
}

void ChildGenerator::removeFirstChild() {
  children_.erase(children_.begin());
}

ChildGenerator& ChildGenerator::getFirstChild() {
  return children_.at(0);
}

std::string ChildGenerator::getFieldType(int fieldIndex) {
  return fieldsType_.at(fieldIndex);
}

std::string ChildGenerator::getFieldMsg(int fieldIndex) {
  return fieldsMsg_.at(fieldIndex);
}

std::string ChildGenerator::getFieldMux(int fieldIndex) {
  return fieldsMux_.at(fieldIndex);
}

std::string ChildGenerator::generateCode() {
  std::string code;

  for(int i = 0; i < numFields_; i++) {
    code += handleFieldGeneration(i);
  }

  return code;
}

std::string ChildGenerator::handleFieldGeneration(int fieldIndex) {
  std::string code;

  std::string listIndexString;

  std::string type = getFieldType(fieldIndex);

  if(type == "single_value") {
    code += "    " + parentName_ + ".add(" + getFieldMsg(fieldIndex) + ");\n\n";
  } else if(type == "list") {
      listIndex_++;
      listIndexString = boost::lexical_cast<std::string>(listIndex_);
      code += "    Bottle& " + parentName_ + "_" + listIndexString + " = " + parentName_ + ".addList();\n\n";
    } else if(type == "timestamp") {
        listIndex_++;
        listIndexString = boost::lexical_cast<std::string>(listIndex_);
        code += "    Bottle& " + parentName_ + "_" + listIndexString + " = " + parentName_ + ".addList();\n";
        code += "    " + parentName_ + "_" + listIndexString + ".add(timestamp);\n";
        code += "    " + parentName_ + "_" + listIndexString + ".add(100);\n\n";
      } else if(type == "counter") {
          code += "    " + parentName_ + ".add(counter);\n\n";
        } else if(type == "mux") {
            listIndex_++;
            listIndexString = boost::lexical_cast<std::string>(listIndex_);
            code += "    Bottle& " + parentName_ + "_" + listIndexString + " = " + parentName_ + ".addList();\n\n";
            code += "    for(int i = 0; i < " + getFieldMux(fieldIndex) + ".size(); i++) {\n";
            code += "      " + parentName_ + "_" + listIndexString + ".add(" + getFieldMux(fieldIndex) + ".get(i));\n";
            code += "    }\n\n";
          } else if(type == "msg") {
              listIndex_++;
              listIndexString = boost::lexical_cast<std::string>(listIndex_);
              code += "    Bottle& " + parentName_ + "_" + listIndexString + " = " + parentName_ + ".addList();\n\n";
              getFirstChild().setParentName(parentName_ + "_" + listIndexString);
              code += getFirstChild().generateCode();
              removeFirstChild();
            }

  return code;
}