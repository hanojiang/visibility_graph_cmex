#include "matrix.h"
#include "mex.h"
#include "vg.h"
#include <stdlib.h>
int deal_vg(const mxArray *data, int length, Stack *s)
{
    double *time_series = mxGetPr(data);
    // for (size_t i = 0; i < length; i++)
    // {
    //     mexPrintf("data %d is %f\n", i, time_series[i]);
    // }

    vg_fast(time_series, s, length);
    // int edge_node_number = s->top;
    return s->top;
    // stack_traverse(&s);
    // mexPrintf("data length is %d,edge number is %d", length, s.top >> 1);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    int M = (int)mxGetM(prhs[0]);

    Stack s;
    stack_init(&s);
    // mexPrintf("array length%d", M);
    int edge_node_number = deal_vg(prhs[0], M, &s);

    if (DEBUGING)
    {
        mexPrintf("edge node length is%d", edge_node_number);
    }
    //

    // plhs[0]=mxCreateDoubleMatrix(1,M,mxREAL);
    // double* count = mxGetPr(plhs[0]);

    plhs[0] = mxCreateNumericMatrix(edge_node_number, 1, mxINT32_CLASS, 0);
    plhs[1] = mxCreateNumericMatrix(edge_node_number, 1, mxINT32_CLASS, 0);
    plhs[2] = mxCreateNumericMatrix(edge_node_number, 1, mxDOUBLE_CLASS, 0);
    int32_T *left_ptr = mxGetPr(plhs[0]);
    int32_T *right_ptr = mxGetPr(plhs[1]);
    double *weight = mxGetPr(plhs[2]);
    // for (size_t i = 0; i < edge_node_number; i++)
    // {
    //     left_ptr[i] = s.node_number[i] + 1;
    // }

    memcpy(left_ptr, s.left_node, sizeof(int32_T) * edge_node_number);
    memcpy(right_ptr, s.right_node, sizeof(int32_T) * edge_node_number);
    memcpy(weight, s.edge_weight, sizeof(double) * edge_node_number);
    stack_destroy(&s);
}
