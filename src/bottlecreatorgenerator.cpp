#include <iostream>
#include <string>
#include "bottlecreatorgenerator.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

// Constructor and destructor
BottleCreatorGenerator::BottleCreatorGenerator(int numFields, const double & rate_, bool toRos) :
    numFields_(numFields),
    rate(rate_),
    period(1/rate),
    listIndex_(0),
    toRos_(toRos) {
    std::cout << "Creating BottleCreatorGenerator." << std::endl;
}

BottleCreatorGenerator::~BottleCreatorGenerator() {
    std::cout << "Deleting BottleCreatorGenerator." << std::endl;
}

int BottleCreatorGenerator::getNumFields() {
    return numFields_;
}

std::vector<ChildGenerator> BottleCreatorGenerator::getChildren() {
    return children_;
}

std::vector<std::string> BottleCreatorGenerator::getFieldsType() {
    return fieldsType_;
}

std::vector<std::string> BottleCreatorGenerator::getFieldsMsg() {
    return fieldsMsg_;
}

std::vector<std::string> BottleCreatorGenerator::getFieldsMux() {
    return fieldsMux_;
}

void BottleCreatorGenerator::addChild(ChildGenerator& child) {
    children_.push_back(child);
}

void BottleCreatorGenerator::addFieldType(std::string type) {
    fieldsType_.push_back(type);
}

void BottleCreatorGenerator::addFieldMsg(std::string msg) {
    fieldsMsg_.push_back(msg);
}

void BottleCreatorGenerator::addFieldMux(std::string mux) {
    fieldsMux_.push_back(mux);
}

void BottleCreatorGenerator::removeFirstChild() {
    children_.erase(children_.begin());
}

ChildGenerator& BottleCreatorGenerator::getFirstChild() {
    return children_.at(0);
}

std::string BottleCreatorGenerator::getFieldType(int fieldIndex) {
    return fieldsType_.at(fieldIndex);
}

std::string BottleCreatorGenerator::getFieldMsg(int fieldIndex) {
    return fieldsMsg_.at(fieldIndex);
}

std::string BottleCreatorGenerator::getFieldMux(int fieldIndex) {
    return fieldsMux_.at(fieldIndex);
}

std::string BottleCreatorGenerator::generateCode() {
    std::string code;

    code += "    /* DO SOME COMPUTATION HERE */\n\n";

    code += "    double timestamp = (double) Time::now();\n\n";
    code += "    Bottle message = Bottle();\n\n";

    for(int i = 0; i < numFields_; i++) {
        code += handleFieldGeneration(i);
    }

    code += "    /* DO SOME COMPUTATION HERE */\n\n";

    code += "    outputPort.write(message);\n";

    code += "    counter++;\n";

    code += "    Time::delay("+boost::lexical_cast<std::string>(period)+");\n";

    return code;
}

std::string BottleCreatorGenerator::handleFieldGeneration(int fieldIndex) {
    std::string code;

    std::string listIndexString;

    std::string type = getFieldType(fieldIndex);

    if(type == "single_value") {
        code += "    message.add(" + getFieldMsg(fieldIndex) + ");\n\n";
    } else if(type == "list") {
        listIndex_++;
        listIndexString = boost::lexical_cast<std::string>(listIndex_);
        code += "    Bottle& list_" + listIndexString + " = message.addList();\n";
        int elementIndex = 0;
        std::string msgString = getFieldMsg(fieldIndex);
        for(int i = 0; i < msgString.size(); i++) {
            if(msgString.at(i) == ',' || i == (msgString.size() - 1)) {
                std::string elementString;
                if(i == (msgString.size() - 1))
                    elementString = msgString.substr(elementIndex, ((i - elementIndex) + 1));
                else
                    elementString = msgString.substr(elementIndex, (i - elementIndex));
                boost::erase_all(elementString, " ");
                code += "    list_" + listIndexString + ".add(" + elementString + ");\n";
                elementIndex = i + 1;
            }
        }
        code += "\n";
    } else if(type == "timestamp") {
        listIndex_++;
        listIndexString = boost::lexical_cast<std::string>(listIndex_);
        if (toRos_){
            code += "    double dummy;\n";
            code += "    double frac=modf(timestamp,&dummy);\n";
            code += "    Bottle& list_" + listIndexString + " = message.addList();\n";
            code += "    list_" + listIndexString + ".add((int)timestamp);\n";
            code += "    list_" + listIndexString + ".add((int)round(frac*pow(10,9)));\n\n";
        }
        else {
            code += "    Bottle& list_" + listIndexString + " = message.addList();\n";
            code += "    list_" + listIndexString + ".add(counter);\n";
            code += "    list_" + listIndexString + ".add(timestamp);\n";
        }

    } else if(type == "counter") {
        code += "    message.add(counter);\n\n";
    } else if(type == "mux") {
        listIndex_++;
        listIndexString = boost::lexical_cast<std::string>(listIndex_);
        if (toRos_){
            code += "    Bottle& list_" + listIndexString + " = message.addList();\n";
            code += "    for(int i = 0; i < " + getFieldMux(fieldIndex) + ".size(); i++) {\n";
            code += "      list_" + listIndexString + ".add(" + getFieldMux(fieldIndex) + ".get(i));\n";
            code += "    }\n\n";
        }
        else {
            code += "    for(int i = 0; i < " + getFieldMux(fieldIndex) + ".size(); i++) {\n";
            code += "       message.add(" + getFieldMux(fieldIndex) + ".get(i));\n";
            code += "    }\n\n";
        }

    } else if(type == "msg") {
        listIndex_++;
        listIndexString = boost::lexical_cast<std::string>(listIndex_);
        code += "    Bottle& list_" + listIndexString + " = message.addList();\n\n";
        getFirstChild().setParentName("list_" + listIndexString);
        code += getFirstChild().generateCode();
        removeFirstChild();
    }

    return code;
}
