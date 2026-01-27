#ifndef LOGISTIC_MAP
#define LOGISTIC_MAP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

typedef vector<double> VD;
typedef vector<int> VI;
typedef vector<vector<double>> VDD;


/* Set xvals to be the first max_iter iterates of the logistic map */
void logisticMap(VD &xvals, double R, double x0, int start_iter, int max_iter); 

/* Set xvals, yvals to be the first max_iter iterates of the Henon map */ 
void HenonMap(VD &xvals, VD &yvals, double a, double b, double x0, double y0, int start_iter, int max_iter);

/* Update a matrix of doubles representing the logistic map results for each R value
 * bifurcation_data[i][j] returns the jth iterate at the ith R value */
void getBifurcationData(VDD &bifurcation_data, VD &Rvals, double x0, int start_iter, int max_iter);

inline VD extendVec(VD xvals, double R) { 
    double last = xvals.back();
    double extend = last * R * (1 - last);

    VD plusOneT = xvals;
    std::rotate(plusOneT.begin(), plusOneT.begin() + 1, plusOneT.end());
    plusOneT.back() = extend;

    return plusOneT;
}

/* Print the contents of a vector in five-column format. */
inline void printVec(VD &vec) {
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        cout << vec[i] << " ";
        if (i % 5 == 4) {
            cout << "\n";
        }
    }
}
inline void printMat(VDD &mat) {
    int ncols = mat.size();
    int nrows = mat[0].size();

    for (int i = 0; i < ncols; ++i) {
        for (int j = 0; j < nrows; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}



#endif // !LOGISTIC_MAP
