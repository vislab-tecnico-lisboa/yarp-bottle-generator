#ifndef YARPCODE_GENERATOR_HPP
#define YARPCODE_GENERATOR_HPP

class YarpCodeGenerator {
  public:
    YarpCodeGenerator();
    ~YarpCodeGenerator();

    virtual std::string generateCode() = 0;
};

#endif //YARPCODE_GENERATOR_HPP
