#include <iostream>
#include "yarpcodegenerator.hpp"

using namespace std;

// Constructor and destructor
YarpCodeGenerator::YarpCodeGenerator() {
  cout << "Creating YarpCodeGenerator." << endl;
}

YarpCodeGenerator::~YarpCodeGenerator(/*string configData*/) {
  cout << "Deleting YarpCodeGenerator." << endl;
}