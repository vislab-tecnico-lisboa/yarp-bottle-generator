#ifndef PORTMUX_GENERATOR_HPP
#define PORTMUX_GENERATOR_HPP
#include <vector>
#include "yarpcodegenerator.hpp"
/**
  * Class that generates the code for connecting and reading the values from the input YARP ports/ROS topics
*/
class PortMuxGenerator : public YarpCodeGenerator {
  public:
    /**
      * Constructor
      * @param numMuxes Number of hubs
      * @param outputName YARP port/ROS topic where the output will be send
      * @param toRos Boolean flag to know the type of output (ROS message or YARP Bottle)
      * @param output_port_name_ Folder name where the code will be copied
      * @param ros_message_name When writing to a ROS topic, this is the ROS message name
      * @param fromRos Boolean flag to know the type of inputs (ROS message or YARP Bottle)
    */
    PortMuxGenerator(int numMuxes, std::string outputName, bool toRos, std::string & output_port_name_, std::string & ros_message_name, bool fromRos);
    /**
      * Destructor
    */
    ~PortMuxGenerator();

    int getNumMuxes();


    std::string getOutputName();
    std::string getRosMessageName();

    bool getToRos();
    bool getFromRos();

    std::vector<int> getNumPorts();

    std::vector<std::string> getPorts();

    void addMuxNumPorts(int numPorts);

    /**
      * Adds the ports/topics string of a hub
      * @param ports String with comma separated ports/topics
    */
    void addMuxPorts(std::string ports);

    /**
      * Returns the number of ports read by the hub at muxIndex in the hub vector
      * @param muxIndex Hub index in the Hub vector
      * @return int Number of ports/topics read by the hub
    */
    int getMuxNumPorts(int muxIndex);

    /**
      * Returns the string that contains all the YARP ports/ROS topics for the hub muxIndex
      * @param muxIndex Hub index in the Hub vector
      * @return String that contains the YARP ports/ROS topics separated by commas
    */
    std::string getMuxPorts(int muxIndex);

    /**
      * Generates the code that connects to all the YARP ports/ROS topics
      * @return String that contains the code for YARP port creation, and connection to the input YARP ports/ROS topics
    */
    std::string generateCode();

  private:
    int numMuxes_;/**< Number of hubs */
    std::string outputName_;/**< YARP port/ROS topic where the output will be send */
    std::string rosMessageName_;/**< When writing to a ROS topic, this is the ROS message name */
    bool toRos_;/**< Boolean flag to know the type of output (ROS message or YARP Bottle) */
    bool fromRos_;/**< Boolean flag to know the type of inputs (ROS message or YARP Bottle) */
    std::vector<int> numPorts_;/**< Vector that contains the number of ports for all the hubs */
    std::vector<std::string> ports_;/**< Vector that contains the inputs (ports/topics) for all the hubs */
    std::string output_port_name;/**< Folder name where the code will be copied */
    std::string extractPortFromString(int muxIndex, int portIndex);
};

#endif //PORTMUX_GENERATOR_HPP
