#include <iostream>
#include "commonendgenerator.hpp"

using namespace std;

// Constructor and destructor
CommonEndGenerator::CommonEndGenerator() {
    cout << "Creating CommonEndGenerator." << endl;
}

CommonEndGenerator::~CommonEndGenerator() {
    cout << "Deleting CommonEndGenerator." << endl;
}

string CommonEndGenerator::generateCode() {
  string code;

  code = "  return 0;\n}";

  return code;
}