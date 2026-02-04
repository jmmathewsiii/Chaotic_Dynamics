#ifndef FRACTAL
#define FRACTAL

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

typedef vector<double> VD;
typedef vector<int> VI;
typedef vector<vector<double>> VDD;

void fractal(VD &data, char prev_dir, double x0, double y0, double l_angle, double r_angle, double llen=0.6, double rlen=0.6, double l_ratio=0.6, double r_ratio = 0.6, int iter=1);

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

#endif // FRACTAL
