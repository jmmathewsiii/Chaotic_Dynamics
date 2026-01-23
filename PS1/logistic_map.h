#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

typedef vector<double> VD;
typedef vector<int> VI;


/* Print the contents of a vector in five-column format. */

void logisticMap(VD &xvals, double R, double x0, int max_iter); 

void printVec(VD &vec);
