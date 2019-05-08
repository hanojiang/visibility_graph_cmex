#include <iostream>
#include <vector>
#include "mex.h"
#include "matrix.h"
#include "math.h"
using namespace std;

bool isequalone(double value)
{
 double eps=1e-6;
 return abs(value-1.0)<eps ? 1:0;
}

void findlines(double * data, double * lines, int len)
{
    
//     for (int i = 0; i < len; i++) {
//         lines[i] = 0;
//     }

    int left = 0, right = 0;
    while (left<len) {
        int len_sub = 0;
        while (right<len && isequalone(data[left]) &&isequalone(data[right])) {
            len_sub += 1;
            right += 1;
        }
        if (len_sub) {
            lines[len_sub - 1] = lines[len_sub - 1] + 1;
        }
        left = right + 1;
        right = left;
    }
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int len = mxGetM(prhs[0]);
//     mexPrintf("%d", len);
    double *data = mxGetPr(prhs[0]);
    const mwSize * ms = mxGetDimensions(prhs[0]);
    plhs[0]  = mxCreateDoubleMatrix(ms[1],ms[0],mxREAL);

    double *lines;
    lines=mxGetPr(plhs[0]);

    findlines(data, lines, len);
}

// void findlines(int8_t * data, int8_t * lines, int len)
// {
//     
//     for (int i = 0; i < len; i++) {
//         lines[i] = 0;
//     }
// 
//     int left = 0, right = 0;
//     while (left<len) {
//         int len_sub = 0;
//         while (right<len && data[left]==1 && data[right]==1) {
//             len_sub += 1;
//             right += 1;
//         }
//         if (len_sub>0) {
//             lines[len_sub - 1] = lines[len_sub - 1] + 1;
//         }
//         left = right + 1;
//         right = left;
//     }
// }


// void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
// {
//     int len = mxGetM(prhs[0]);
// //     mexPrintf("%d", len);
//     int8_t *data = (int8_t *)mxGetData(prhs[0]);
//     const mwSize * ms = mxGetDimensions(prhs[0]);
//     plhs[0]  = mxCreateNumericArray (2, ms, mxINT8_CLASS, mxREAL);
// 
//     int8_t *lines;
//     lines=(int8_t *)mxGetData(plhs[0]);
// 
//     findlines(data, lines, len);
// 
// 
//     // double *data;
//     // int8_t * lines;
//     // data = mxGetPr(prhs[0]);
//     // plhs[0]  = mxCreateNumericArray (1, length, mxINT8_CLASS, mxREAL);
//     // lines=mxGetPr(plhs[0]);
//     // int8_t data_int[length];
//     // for (int i = 0; i < length; i++) {
//     //     data_int[i] = int8_t(data[i]);
//     // }
//     // vector<int8_t> vec_data(data_int, data_int + length);
//     // findlines(vec_data, lines);
// }


// int main(int argc, char const *argv[]) {
    
//     // int x[]={0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1 };
// // % y=[1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
//     int x[] = {0, 1, 0, 1, 0, 1};
//     const int length = 6;
//     vector<int> data(x, x + length);
//     int lines[length];
//     findlines(data, lines);
//     for (int i = 0; i < length; i++) {
//         cout << lines[i] << endl;
//     }
//     return 0;
// }