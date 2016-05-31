#ifndef YARPCODE_GENERATOR_HPP
#define YARPCODE_GENERATOR_HPP
/**
  * Interface that represents which will be implemented by all the code generating classes
*/
class YarpCodeGenerator {
  public:
    YarpCodeGenerator();
    ~YarpCodeGenerator();
    /**
      * Method that implements the code generation
      * @return String that contains the code
    */
    virtual std::string generateCode() = 0;
};

#endif //YARPCODE_GENERATOR_HPP
