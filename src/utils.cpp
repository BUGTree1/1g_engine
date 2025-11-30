#include "utils.h"

using namespace std;
using namespace glm;

// ---------------------
//  Logging
// \/-------------------

void error(string msg){
    cout << "ERROR: " << msg << endl;
    exit(1);
}

void warning(string msg){
    cout << "WARNING: " << msg << endl;
}

void todo(string msg){
    cout << "TODO: " << msg << endl;
    exit(1);
}