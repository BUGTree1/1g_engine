#include "common.h"

using namespace std;
using namespace glm;

namespace e1g {

// ---------------------
//  Logging
// \/-------------------

void error(string msg, int error_code){
    cout << "ERROR: " << msg << endl;
    exit(error_code);
}

void warning(string msg){
    cout << "WARNING: " << msg << endl;
}

void todo(string msg){
    cout << "TODO: " << msg << endl;
    exit(1);
}

}