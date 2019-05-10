#include "vg.h"
#include "mex.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 256
status stack_push(Stack* s, const int left_node_value, const int right_node_value, const double edge_weight_value)
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
        int *left_temp = NULL;
        int *right_temp = NULL;
        double *weight = NULL;

        left_temp = (int *)realloc(s->left_node, sizeof(int) * s->size);
        right_temp = (int *)realloc(s->right_node, sizeof(int) * s->size);
        weight = realloc(s->edge_weight, sizeof(double) * s->size);
        if (!left_temp || !right_temp || !weight)
        {
            printf("stack malloc error!\n");
            free(s->left_node);
            free(s->right_node);
            free(s->edge_weight);
            return 1;
        }
        s->left_node = left_temp;
        s->right_node = right_temp;
        s->edge_weight = weight;
    }
    *(s->left_node + s->top) = left_node_value;
    *(s->right_node + s->top) = right_node_value;
    *(s->edge_weight + s->top) = edge_weight_value;
    s->top += 1;
    return 0;
}

void stack_traverse(Stack *s)
{
    for (size_t i = 0; i < s->top; i++)
    {
        // int node_left = s->e[i].node_left+1;
        // int node_right = s->e[i].node_right+1;
        int left_node_value = s->left_node[i];
        int right_node_value = s->right_node[i];
        double weight = s->edge_weight[i];
        printf("edge weight betweent node %d and node %d is %f\n", left_node_value, right_node_value, weight);
    }
}
void stack_init(Stack *s)
{
    s->left_node = NULL;
    s->right_node = NULL;
    s->edge_weight = NULL;
    s->size = 0;
    s->top = 0;
}
void stack_destroy(Stack* s)
{
    free(s->left_node);
    free(s->right_node);
    free(s->edge_weight);
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
    // stack_init(s);
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
                double weight = fabs(y_to - cut_value);//fabs 用于求浮点数的绝对值
                stack_push(s, max_cut+1, left_index+1, weight);
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
                double weight = fabs(y_to - cut_value);
                stack_push(s, max_cut+1, right_index+1, weight);
            }
        }

        vg_rec(left, max_cut - 1, time_series, s);
        vg_rec(max_cut + 1, right, time_series, s);
    }
}