#/bin/bash

mpicc -c iorncmpibug.c -I/Users/liangweihao/Documents/workspace/cdo/parallel-netcdf-1.8.1/build/include

mpicc -o iorncmpibug iorncmpibug.o -L/Users/liangweihao/Documents/workspace/cdo/parallel-netcdf-1.8.1/build/lib -lpnetcdf

mpirun -n 4 ./iorncmpibug

rm iorncmpibug


