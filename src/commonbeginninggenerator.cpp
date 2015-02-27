#include <iostream>
#include "commonbeginninggenerator.hpp"

using namespace std;

// Constructor and destructor
CommonBeginningGenerator::CommonBeginningGenerator() {
    cout << "Creating CommonBeginningGenerator." << endl;
}

CommonBeginningGenerator::~CommonBeginningGenerator() {
    cout << "Deleting CommonBeginningGenerator." << endl;
}

string CommonBeginningGenerator::generateCode() {
  string code;

  code = "#include <yarp/os/all.h>\n\nusing namespace yarp::os;\n\nint main(int argc, char *argv[]) {\n  Network yarp;\n\n";

  return code;
}