#ifndef BOTTLECREATOR_GENERATOR_HPP
#define BOTTLECREATOR_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"
#include "childgenerator.hpp"
/**
  * Class that generates the code for building the message and sending it through the network (YARP port/ROS topic)
  * This class represents the top level of the message hierarchy
*/
class BottleCreatorGenerator : public YarpCodeGenerator {
  public:
    /**
      * Constructor
      * @param numFields Number of items (either simple types or messages) of the message
      * @param rate_ Rate at which the message will be sent (hz)
      * @param toRos Boolean flag to know the type of output (ROS message or YARP Bottle)
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

    /**
      * Generates the code that builds the message for all the items in the configuration file
      * @return String that contains the code for message building and sending, considering the frequency
    */
    std::string generateCode();

  private:
    int numFields_;/**< Number of items in the message */
    int listIndex_;
    bool toRos_;/**< Boolean flag to know the type of output */
    std::vector<ChildGenerator> children_;/**< Vector of ChildGenerator class, that handles built-in (primitive) messages and arrays of built-in messages */
    std::vector<std::string> fieldsType_;/**< Vector of std::string that contains all the message types at the top of the message hierarchy, read from the configuration file */
    std::vector<std::string> fieldsMsg_;/**< Vector of std::string that stores "single_value" or "list" if that is the type of the item*/
    std::vector<std::string> fieldsMux_;/**< Vector of std::string that stores "mux" if that is the type of the item*/
    double rate;
    double period;
    /**
      * Generates the code that builds the message for an item of the top of the hierarchy, considering all its children in the message tree
      * @param index at the ChildGenerator std::vector
      * @return String that contains the code for message building
    */
    std::string handleFieldGeneration(int fieldIndex);
};

#endif //BOTTLECREATOR_GENERATOR_HPP
