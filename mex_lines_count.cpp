#include <iostream>
#include <vector>
#include "mex.h"
#include "matrix.h"
#include "math.h"
using namespace std;

#define matrix_in(row,col) matrix_in[col*matrix_size+row]
bool isequalone(double value)
{
    double eps=1e-6;
    return abs(value-1.0)<eps ? 1:0;
}
void mydiag(const mxArray* matrix1,  int position, double* matrix_out, int matrix_size)
{
//     mexPrintf("%d",position);
//     int M = (int)mxGetM(matrix1);
//     mexPrintf("%d",M);
    double *matrix_in;
    
    matrix_in = mxGetPr(matrix1);
    
    int positive, negative;
    if (position>0) {
        positive=position;
        negative=0;
    } else {
        positive=0;
        negative=position;
    }
//     const int out_length = matrix_size - abs(position);
//     mexPrintf("%d",out_length);
    // for (int i = 1 - negative - 1, j = 1 + positive - 1,k=0; i < (M - positive);++i,++j,++k)
    for (int i = -negative, j = positive,k=0; i < (matrix_size - positive);++i,++j,++k)
    {
        matrix_out[k] = matrix_in(i, j);
//         mexPrintf("%f",matrix_out[k]);
    }
}

void findlines(const double * data, double * lines, int len)
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

void lines_count(const mxArray * matrix,double* count, int matrix_size,const mxArray* mx_issyms)
{
    int comp_max;
    mxLogical* issyms=mxGetLogicals(mx_issyms);
    
    if(*issyms)
    {
        comp_max=0;
    }else
    {
        comp_max=matrix_size;
        
    }
    for(int i=-(matrix_size-1);i<comp_max;++i)
    {
        int diag_length=matrix_size-abs(i);
        double   *p_diag_line=new   double[diag_length];
        double   *p_lines=new   double[diag_length];
        for(int jj=0;jj<diag_length;++jj)
        {
            p_lines[jj]=0;
        }
        mydiag(matrix,  i,p_diag_line,matrix_size);
        
        findlines(p_diag_line,p_lines, diag_length);
        
        for(int j=0;j<diag_length;++j)
        {
            count[j]+=p_lines[j];
        }
        delete[] p_diag_line;
        delete[] p_lines;
    }
    if(*issyms)
    {
//         mexPrintf("matrix is sysm");
        for(int j=0;j<matrix_size;++j)
        {
            if(count[j])
                count[j]*=2;
        }
        count[matrix_size-1]=1;
    }
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int M = (int)mxGetM(prhs[0]);
    
    plhs[0]=mxCreateDoubleMatrix(1,M,mxREAL);
    double* count = mxGetPr(plhs[0]);
    lines_count(prhs[0],count,M,prhs[1]);
    
}