#ifndef _VG_H__
#define _VG_H__
#include <stdlib.h>
#define DEBUGING 0
typedef int status;
// typedef struct Edge
// {
//     int node_left;
//     int node_right;
// }Edge;

typedef struct Stack
{
    // Edge* e;
    int * node_number;
    size_t top;
    size_t size;
}Stack;

status stack_push(Stack* s, const int node_number);
void stack_traverse(Stack *s);
int find_max_index(double* data, int left, int right);
void vg_rec(int left, int right, double *time_series, Stack *s);
void vg_fast(double *time_series, Stack *s, int length);
#endif	// _VG_H__