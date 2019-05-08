#include "matrix.h"
#include "mex.h"
#include "vg.h"

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
    mexPrintf("array length%d", M);
    int edge_node_number = deal_vg(prhs[0], M, &s);

    if (DEBUGING)
    {
        mexPrintf("edge node length is%d", edge_node_number);
    }
    //

    // plhs[0]=mxCreateDoubleMatrix(1,M,mxREAL);
    // double* count = mxGetPr(plhs[0]);

    plhs[0] = mxCreateNumericMatrix(edge_node_number, 1, mxUINT16_CLASS, 0);
    uint16_T *left_ptr = mxGetPr(plhs[0]);
    for (size_t i = 0; i < edge_node_number; i++)
    {
        left_ptr[i] = s.node_number[i] + 1;
    }
    free(s.node_number);
}
