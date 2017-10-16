#include "generatemeta.h"

int partition(short arr[], int low, int high){
    short key;
    key = arr[low];
    while(low<high){
        while(low <high && arr[high]>= key )
        high--;
        if(low<high)
        arr[low++] = arr[high];
        while( low<high && arr[low]<=key )
        low++;
        if(low<high)
        arr[high--] = arr[low];
    }
    arr[low] = key;
    return low;
}

void quick_sort(short arr[], int start, int end){
    int pos;
    if (start<end){
        pos = partition(arr, start, end);
        quick_sort(arr,start,pos-1);
        quick_sort(arr,pos+1,end);
    }
    return;
}


void calculate_5number(short *in, int len, short *out)
{
    short min, lquartile, median, uquartile, max;

    quick_sort(in, 0, len-1);
    
    out[0] = in[0];
    out[1] = in[(0+len/2)/2];
    out[2] = in[len/2];
    out[3] = in[(len/2+len)/2];
    out[4] = in[len-1];
}

float cal_pos(short *in , short cur)
{
    int i;

    if(cur <= in[0]) return 0.0;
    if(cur >= in[4]) return 4.0;

    for(i = 0; i <= 3; i++)
    {
        if(cur>in[i] && cur<in[i+1]) 
            break;
    }

    return (cur-in[i])*1.0/(in[i+1]-in[i])+i;
}

float predict_hit(short *in, short leftrange, short rightrange)
{
    if (leftrange >= in[4] || rightrange <= in[0])
        return 0.0; 

    printf("pos: %f %f\n", cal_pos(in,leftrange), cal_pos(in, rightrange));
    return (cal_pos(in, rightrange)-cal_pos(in, leftrange))/4;    
}
