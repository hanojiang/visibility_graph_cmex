#include "vg.h"
#include "mex.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 256
status stack_push(Stack *s, const int node_number)
{
    if (s->top + 1 >= s->size)
    {
        if (s->size == 0)
            s->size = STACK_INIT_SIZE;
        else
        {
            s->size += s->size >> 1;
        }

        // Edge *e_temp = NULL;
        // e_temp = (Edge*)realloc(s->e, sizeof(Edge)*s->size);//注意分配内存空间的大小如何计算
        int *node_array_temp = NULL;
        node_array_temp = (int *)realloc(s->node_number, sizeof(int) * s->size);
        if (!node_array_temp)
        {
            printf("stack malloc error!\n");
            free(s->node_number);
            return 1;
        }
        s->node_number = node_array_temp;
    }
    *(s->node_number + s->top) = node_number;
    s->top += 1;
    return 0;
}

void stack_traverse(Stack *s)
{
    for (size_t i = 0; i < s->top; i++)
    {
        // int node_left = s->e[i].node_left+1;
        // int node_right = s->e[i].node_right+1;
        int node = s->node_number[i];
        printf("edge betweent %d\n", node);
    }
}
void stack_init(Stack *s)
{
    s->node_number = NULL;
    s->size = 0;
    s->top = 0;
}
int find_max_index(double *data, int left, int right)
{
    double max_value = *(data + left);
    int max_index = left;
    for (int index = left + 1; index <= right; index++)
    {
        if (*(data + index) > max_value)
        {
            max_value = *(data + index);
            max_index = index;
        }
    }
    return max_index;
}

void vg_fast(double *time_series, Stack *s, int length)
{
    stack_init(s);
    vg_rec(0, length - 1, time_series, s);
}

void vg_rec(int left, int right, double *time_series, Stack *s)
{

    if (left < right)
    {
        int max_cut = find_max_index(time_series, left, right);
        double cut_value = time_series[max_cut];
        double min_slop_left = DBL_MAX;
        double max_slop_right = -DBL_MAX;

        for (int left_index = max_cut - 1; left_index >= left; left_index--)
        {
            double y_to = time_series[left_index];
            double slop = (y_to - cut_value) / (left_index - max_cut);
            if (DEBUGING)
            {
                mexPrintf("cut point is %d, left other point is %d, slop is %f\n", max_cut + 1, left_index + 1, slop);
            }
            if (slop < min_slop_left)
            {
                min_slop_left = slop;
                if (DEBUGING)
                {
                    mexPrintf("min slop left is %f\n", min_slop_left);
                }
                stack_push(s, max_cut);
                stack_push(s, left_index);
            }
        }

        for (int right_index = max_cut + 1; right_index <= right; right_index++)
        {
            double y_to = time_series[right_index];
            double slop = (y_to - cut_value) / (right_index - max_cut);
            if (DEBUGING)
            {
                mexPrintf("cut point is %d, right other point is %d, slop is %f\n", max_cut + 1, right_index + 1, slop);
            }
            if (slop > max_slop_right)
            {
                max_slop_right = slop;
                if (DEBUGING)
                {
                    mexPrintf("max slop right is %f\n", max_slop_right);
                }
                // Edge e = {max_cut, right_index};
                stack_push(s, max_cut);
                stack_push(s, right_index);
            }
        }

        vg_rec(left, max_cut - 1, time_series, s);
        vg_rec(max_cut + 1, right, time_series, s);
    }
}