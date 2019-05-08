// #include <vector>
// #include <iostream>
// #include <algorithm>
// using namespace std;
// int main()
// {
//     double a[6] = {12,3,4,29,39,20};

//     vector<double> data(a, a+6);

//     int max_ind = max_element(a,a+6)-a;
//     cout<< data[0]<<endl<<max_ind;
//     return 0;
// }

#include <stdio.h>
#include "vg.h"
int main(int argc, char const *argv[])
{
    // Stack edge_stack;
    // edge_stack.size = 0;
    // edge_stack.top = 0;
    // edge_stack.e = NULL;
    // for (size_t i = 0; i < 30000; i++)
    // {
    //     Edge e;
    //     e.node_left=i+1;
    //     e.node_right=i+2;
    //     stack_push(&edge_stack, e);
    // }
    
    // printf("stack size %d,and top is %d\n", edge_stack.size, edge_stack.top);
    // printf("first edge is between node %d and %d", edge_stack.e[29999].node_left, edge_stack.e[29999].node_right);
    // free(edge_stack.e);

    double a[10] = {1, 2, 4, 1, 5, 7, 3, 7,3,5};
    // double a[10] = {10,	1,	2,	5,	6,	8,	10,	8,	2,	7};
    Stack s;
    vg_fast(a, &s, 10);
    // printf("first edge is between node %d and %d\n", s.e[0].node_left, s.e[0].node_right);

    printf("edge sum is %d\n", s.top/2);
    stack_traverse(&s);
    free(s.node_number);
    return 0;
}
