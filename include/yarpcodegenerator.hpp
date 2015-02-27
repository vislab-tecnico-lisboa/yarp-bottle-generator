#ifndef YARPCODE_GENERATOR_HPP
#define YARPCODE_GENERATOR_HPP

using namespace std;

class YarpCodeGenerator {
  public:
    YarpCodeGenerator();
    YarpCodeGenerator(string configData);
    ~YarpCodeGenerator();

    string getConfigData();

    bool hasConfigData();

    virtual string generateCode() = 0;
 
  private:
    string configData_;
};

#endif //YARPCODE_GENERATOR_HPP