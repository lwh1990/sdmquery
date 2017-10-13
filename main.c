#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <pnetcdf.h>
#include "utility.h"
#include "generatemeta.h"

int main(int argc, char **argv)
{
    char filename[256];
    int i, j, rank, nprocs, err, ncid, varid, dimid[3];
    short *buf;
    double t1, t2;
    MPI_Offset len, global_nx, global_ny, global_nz, local_nx, local_ny, local_nz;
    MPI_Offset start[3], count[3];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    sprintf(filename, "/Users/liangweihao/Downloads/dataset/median.nc");
    err = ncmpi_open(MPI_COMM_WORLD, filename, NC_NOWRITE, MPI_INFO_NULL, &ncid);

    err = ncmpi_inq_dimid(ncid, "longitude", &dimid[2]);
    err = ncmpi_inq_dimid(ncid, "latitude", &dimid[1]);
    err = ncmpi_inq_dimid(ncid, "time", &dimid[0]);
    printf("dimensions ID: %d %d %d\n", dimid[0], dimid[1], dimid[2]);

    err = ncmpi_inq_dimlen(ncid, dimid[2], &global_nx);
    err = ncmpi_inq_dimlen(ncid, dimid[1], &global_ny);
    err = ncmpi_inq_dimlen(ncid, dimid[0], &global_nz);
    printf("dimensions lens: %d %d %d\n", global_nx, global_ny, global_nz);

    err = ncmpi_inq_varid(ncid, "t2m", &varid);
   
    float sum = 0.0;
    short out[5];int l, r, t[2]; float predict, actual;
    l = 30000, r = 32000;
    for(j = 0; j < global_nz; j++)
    {
    start[0] = j;
    start[1] = 0;
    start[2] = 0;
    count[0] = 1;
    count[1] = global_ny;
    count[2] = global_nx;

    buf = (short* )malloc(global_nx * global_ny * sizeof(short));
    
    err = ncmpi_get_vara_short_all(ncid, varid, start, count, buf);
    check_err(err);

    t1 = MPI_Wtime();
    calculate_5number(buf, global_nx * global_ny, out);
    t2 = MPI_Wtime();
    printf("build 5number time=%f\n", t2-t1);
    printf("%d %d %d %d %d\n", out[0], out[1], out[2], out[3], out[4]);
    //gen_rand_range(t, out[0], out[4]);
    //l = t[0]; r = t[1];
    //printf("random %d %d\n", l, r);
    predict = predict_hit(out, l, r);
    printf("predict ratio: %f\n", predict);

    int c = 0;
    for(i = 0; i < global_nx*global_ny; i++)
    {
        if(buf[i] < r && buf[i] > l) c++;
    }
    actual = c*1.0/(global_nx*global_ny);
    printf("actual ratio: %f\n", actual);
    printf("diff : %f\n", actual-predict);

    if(actual > predict)  sum += actual - predict;
    else sum += predict -actual;
    }
    printf("average diff: %f\n", sum / global_nz);

    err = ncmpi_close(ncid);
    MPI_Finalize();
    return 0;
}
