#include <sstream>
using namespace std;

#include "Complex.hpp"

Complex Complex::parse(const char *arg) {
    istringstream coords_stringstream(arg);
    string re_string;
    string im_string;
    getline(coords_stringstream, re_string, ',');
    getline(coords_stringstream, im_string, ',');
    return Complex{stod(re_string), stod(im_string)};
}
