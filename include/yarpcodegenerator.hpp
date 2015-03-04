#ifndef YARPCODE_GENERATOR_HPP
#define YARPCODE_GENERATOR_HPP

using namespace std;

class YarpCodeGenerator {
  public:
    YarpCodeGenerator();
    ~YarpCodeGenerator();

    virtual string generateCode() = 0;
};

#endif //YARPCODE_GENERATOR_HPP