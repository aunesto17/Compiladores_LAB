#include "helper.h"
#include <sstream>
#include <fstream>

string read_file(const char * path){
    ifstream s(path);
    stringstream buffer;
    buffer << s.rdbuf();
    return buffer.str();
}