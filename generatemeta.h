#include <stdio.h>
#include <stdlib.h>

int partition(short arr[], int low, int high);

void quick_sort(short arr[], int start, int end);

void calculate_5number(short *in, int len, short *out);

float cal_pos(short *in , short cur);

float predict_hit(short *in, short leftrange, short rightrange);
