#include "utility.h"

void check_err(int err)
{
    if(err != NC_NOERR)
    {
        printf("Error at line %d in %s: $s\n",
                __LINE__, __FILE__, ncmpi_strerror(err));
        exit(1);
    }
}

void gen_rand_range(int in[], int min, int max)
{
    int a,b;
    a = rand() % (max - min);
    b = rand() % (max - min);
    in[0] = (a > b ? b : a) + min;
    in[1] = (b > a ? b : a) + min;
    //printf("%d %d\n", a,b);
}
