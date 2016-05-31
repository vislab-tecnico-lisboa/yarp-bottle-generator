#ifndef CHILD_GENERATOR_HPP
#define CHILD_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"
/**
  * Class that generates the code for building the message and sending it through the network (YARP port/ROS topic)
  * This class represents the any leaf of the message hierarchy (not the root of the tree)
*/
class ChildGenerator : public YarpCodeGenerator {
  public:
    /**
      * Constructor
      * @param numFields Number of items (either simple types or messages) of the message
      * @param toRos Boolean flag to know the type of output (ROS message or YARP Bottle)
    */
    ChildGenerator(int numFields, bool toRos);
    /**
      * Destructor
    */
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
    
    /**
      * Generates the code that builds the message for the current node in the message hierarchy and all its leaves
      * @return String that contains the code for message building and sending
    */
    std::string generateCode();

  private:
    int numFields_;/**< Number of items in the current node */
    bool toRos_;/**< Boolean flag to know the type of output */
    int listIndex_;
    std::string parentName_;
    std::vector<ChildGenerator> children_;/**< Vector of ChildGenerator class, that handles built-in (primitive) messages and arrays of built-in messages */
    std::vector<std::string> fieldsType_;/**< Vector of std::string that contains all the message types at the current node in the message hierarchy, read from the configuration file */
    std::vector<std::string> fieldsMsg_;/**< Vector of std::string that stores "single_value" or "list" if that is the type of the item*/
    std::vector<std::string> fieldsMux_;/**< Vector of std::string that stores "mux" if that is the type of the item*/
    /**
      * Generates the code that builds the message for the current node in the hierarchy, considering all its children in the tree
      * @param index at the ChildGenerator std::vector
      * @return String that contains the code for message building
    */
    std::string handleFieldGeneration(int fieldIndex);
};

#endif //CHILD_GENERATOR_HPP
