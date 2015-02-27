#include <iostream>
#include "yarpcodegenerator.hpp"

using namespace std;

// Constructor and destructor
YarpCodeGenerator::YarpCodeGenerator() : configData_("nodata") {
  cout << "Creating YarpCodeGenerator." << endl;

  if(YarpCodeGenerator::hasConfigData()) {
    cout << "configData_ is empty." << endl;
  } else {
    cout << "configData_ is: " << YarpCodeGenerator::getConfigData() << "." << endl;
  }
}

YarpCodeGenerator::YarpCodeGenerator(string configData) : configData_(configData) {
  cout << "Creating YarpCodeGenerator." << endl;

  if(YarpCodeGenerator::hasConfigData()) {
    cout << "configData_ is empty." << endl;
  } else {
    cout << "configData_ is: " << YarpCodeGenerator::getConfigData() << "." << endl;
  }
}

YarpCodeGenerator::~YarpCodeGenerator(/*string configData*/) {
  cout << "Deleting YarpCodeGenerator." << endl;
}

string YarpCodeGenerator::getConfigData() {
  return configData_;
}

bool YarpCodeGenerator::hasConfigData() {
  return configData_.empty();
}